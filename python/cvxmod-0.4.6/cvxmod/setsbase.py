"""
Convex optimization modeling for cvxopt.

"""

# Copyright (C) 2006-2008 Jacob Mattingley and Stephen Boyd.
#
# This file is part of CVXMOD.
#
# CVXMOD is free software; you can redistribute it and/or modify it under the
# terms of the GNU General Public License as published by the Free Software
# Foundation; either version 3 of the License, or (at your option) any later
# version.
#
# CVXMOD is distributed in the hope that it will be useful, but WITHOUT ANY
# WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
# A PARTICULAR PURPOSE. See the GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along with
# this program. If not, see <http://www.gnu.org/licenses/>.

import cvxmod
from cvxmod.base import *
from cvxmod.base import lhsrhs
from cvxmod.errors import *
# Next imports are used when testing values of inequalities.
from cvxmod.base import eps, _maxeignum, _mineignum

__all__ = ["cvxmodset", "lt", "gt", "In"]
LT = '|lt|'
GT = '|gt|'

class setrelation(object):
    # jem. lousy name?
    def __init__(self, expr, js):
        if not equiv(size(expr), size(js)):
            raise DimError
        self.expr = expr
        self.js = js

    def __repr__(self):
        # jem. mention the size? set relation in R^{x,y}?
        return '<set relation %s |In| %s; optvars: %s>' % \
                (str(self.expr), str(self.js),
                 stroptvars(getoptvars(self)))

    def split(self):
        return self.js.constrform(self.expr)

    # jem. bad method for determining convexity?
    def _getconvex(self):
        # jem: is this the whole deal?
        return isaffine(self.expr)
    convex = property(_getconvex)

    def getoptvars(self):
        return getoptvars(self.expr)

    def getassertions(self):
        return getassertions(self.expr)

    def _getvalue(self):
        return value(self.split())
    value = property(_getvalue)

    def __nonzero__(self):
        raise OptimizationError("wrap value() around set relations if comparing values")

class exprIncombination(object):
    def __init__(self, expr):
        self.expr = expr

    def __or__(self, other):
        if isinstance(other, cvxmodset):
            return setrelation(self.expr, other)
        else:
            raise TypeError('invalid type for half setrelation')

    def __repr__(self):
        return '<half of a setrelation>'

class Incvxmodsetcombination(object):
    def __init__(self, js):
        self.js = js

    def __or__(self, other):
        if isinstance(other, (function, symbol)):
            return setrelation(other, self.js)

    def __repr__(self):
        return '<half of a setrelation>'

class cvxmodset(object):
    pass

class Intype(object):
    def __or__(self, other):
        if isinstance(other, (function, symbol)):
            return exprIncombination(other)
        elif isinstance(other, cvxmodset):
            return Incvxmodsetcombination(other)
        else:
            raise TypeError('invalid type for |In| pseudo-operator')

    def __ror__(self, other):
        if isinstance(other, cvxmodset):
            return Incvxmodsetcombination(other)
        else:
            return exprIncombination(other)

    def __repr__(self):
        return '<pseudo-operator for set membership>'

In = Intype()
class genineq(lhsrhs):
    def __init__(self, lhs, rhs, sign):
        if is1x1(lhs) or is1x1(rhs) or equiv(size(lhs), size(rhs)):
            self.lhs = lhs
            self.rhs = rhs
            self.sign = sign
            if is1x1(lhs):
                self.rows = rows(rhs)
                self.cols = cols(rhs)
            else:
                self.rows = rows(lhs)
                self.cols = cols(lhs)
        else:
            raise DimError

    def __repr__(self):
        return "<%sx%s generalized inequality %s %s %s; optvars: %s>" % \
            (str(rows(self)), str(cols(self)), str(self.lhs), self.sign,
            str(self.rhs), stroptvars(self))

    def __str__(self):
        return "%s %s %s" % (str(self.lhs), self.sign, str(self.rhs))

    def stdlhs(self):
        if self.sign is LT:
            return self.lhs - self.rhs
        elif self.sign is GT:
            return self.rhs - self.lhs
        else:
            raise NotImplementedError("cannot find stdlhs for this genineq")

    def _getconvex(self):
        return isaffine(self.stdlhs())
    convex = property(_getconvex)

    def split(self):
        stdlhs = self.stdlhs()
        if not issymm(stdlhs):
            xs = dummyvar(size(stdlhs), symm=True)
            s = (xs == stdlhs).split()
            s += (xs |lt| 0).split()
            return s
        else:
            return stdstruct(psdcone=[stdlhs |lt| 0])

    def _getvalue(self):
        return _maxeignum(value(self.stdlhs())) <= eps
    value = property(_getvalue)

    def cvx(self):
        return "%s == semidefinite(%s)" % (str(-self.stdlhs()),
                                           str(rows(self.stdlhs())))

class genineqlhs(object):
    def __init__(self, lhs, sign):
        self.lhs = lhs
        self.sign = sign

    def __or__(self, other):
        # jem: need to test if we have a cvxmod object.
        return genineq(self.lhs, other, self.sign)

    def __repr__(self):
        return '<left-hand side of a generalized inequality>'

class genineqrhs(object):
    def __init__(self, rhs, sign):
        self.rhs = rhs
        self.sign = sign

    def __or__(self, other):
        if isinstance(other, (function, symbol)):
            return genineq(other, self.rhs, self.sign)

    def __repr__(self):
        return '<right-hand side of a generalized inequality>'

class ltrel(object):
    pass

class lttype(object):
    def __or__(self, other):
        if isaffine(other):
            return genineqrhs(other, LT)
        else:
            raise TypeError('invalid type for |lt|: must be affine')

    def __ror__(self, other):
        if isaffine(other):
            return genineqlhs(other, LT)
        else:
            raise TypeError('invalid type for |lt|: must be affine')

    def __repr__(self):
        return '<pseudo-operator for PSD cones>'
lt = lttype()
class gttype(object):
    def __or__(self, other):
        if isaffine(other):
            return genineqrhs(other, GT)
        else:
            raise TypeError('invalid type for |gt|: must be affine')

    def __ror__(self, other):
        if isaffine(other):
            return genineqlhs(other, GT)
        else:
            raise TypeError('invalid type for |gt|: must be affine')

    def __repr__(self):
        return '<pseudo-operator for PSD cones>'
gt = gttype()
