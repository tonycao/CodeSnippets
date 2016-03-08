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

from base import *

# user imports
import cvxopt.blas

# naming conventions here are a bit off. stdformquad and stdquadform?!? jem.

def eval(*args):
    x = matrix(args[0])
    if len(args) == 2:
        Q = args[1]
    else:
        Q = eye(rows(x))

    return (transpose(x)*Q*x)[0] # extract value from matrix.

class functionalform(function, multiarg):
    """Understands quadform(x, Q)."""
    def __init__(self, *args):
        x = args[0]
        if len(args) == 2:
            M = args[1]
        else:
            Q = eye(rows(x), True)

        if len(args) == 2:
            Q = args[1]
        else:
            Q = eye(rows(x), True)

        if getoptvars(Q):
            raise AtomArgsError('Q must not contain a variable')

        if ispos(Q):
            self.conv = True
            self.conc = False

        if isneg(Q):
            self.conv = False
            self.conc = True

        self.x = x # x, called x for stdconvex/stdconcave.
        self.Q = Q
        self.rows = 1
        self.cols = 1
        self.args = args

    def _getpositive(self):
        return ispos(self.Q)
    positive = property(_getpositive)

    def _getnegative(self):
        return isnsd(self.Q)
    negative = property(_getnegative)

    def _getconvex(self):
        return ispsd(self.Q)
    convex = property(_getconvex)

    def _getconcave(self):
        return isnsd(self.Q)
    concave = property(_getconcave)

    def _getincfn(self):
        # jem check.
        return (ispos(self.Q) and ispos(self.x)) or \
                (isneg(self.Q) and isneg(self.x))
    incfn = property(_getincfn)

    def _getdecfn(self):
        # jem check.
        return (isneg(self.Q) and ispos(self.x)) or \
                (ispos(self.Q) and isneg(self.x))
    decfn = property(_getdecfn)

    def _getvalue(self):
        return eval(value(self.x), value(self.Q))
    value = property(_getvalue)

    def cvx(self):
        if isinstance(self.Q, eyesymbol):
            return 'quad_form(%s)' % self.x
        else:
            return 'quad_form(%s, %s)' % (self.x, self.Q)

class _stdformquadconvex(object):
    # inherit from something, later? jem. include NotImplementedError errors and a
    # test() function or so.
    """An F() standard form for quadform(x, Q) - t <= 0."""
    def __init__(self, x, Q, t):
        self.rows = 1
        self.cols = 1
        self.optvars = set((x, t))
        self.x = x
        self.Q = Q
        self.t = t
    
    def indomain(self):
        return True

    def setindomain(self):
        self.x.value = ones(size(self.x))
        self.t.value = rows(self.x)

    def value(self):
        return eval(value(self.x), value(self.Q)) - value(self.t)

    def jacobian(self, var):
        # not *quite* the jacobian, but nearly.
        x = value(self.x)
        Q = value(self.Q)
        if var is self.x:
            return transpose(2*Q*x)
        elif var is self.t:
            return -1
        else:
            raise OptimizationError('illegal jacobian')

    def hessianz(self, firstvar, secondvar, z):
        x = value(self.x)
        t = value(self.t)
        Q = value(self.Q)
        if not is1x1(z):
            raise OptimizationError('illegal z for hessianz call')
        if firstvar is secondvar is self.x:
            return 2*z*Q
        elif firstvar is secondvar is self.t:
            return zeros(rows(t))
        elif firstvar is self.x and secondvar is self.t:
            return zeros(rows(x), value(rows(t)))
        elif firstvar is self.t and secondvar is self.x:
            return zeros(rows(t), rows(x))
        else:
            raise OptimizationError('illegal hessian')

# jem try and combine the two?
class _stdformquadconcave(object):
    # inherit from something, later? jem. include NotImplementedError errors and a
    # test() function or so.
    """An F() standard form for -quadform(x, Q) + t <= 0."""
    def __init__(self, x, Q, t):
        self.rows = 1
        self.cols = 1
        self.optvars = set((x, t))
        self.x = x
        self.Q = Q
        self.t = t
    
    def indomain(self):
        return True

    def setindomain(self):
        self.x.value = ones(size(self.x))
        self.t.value = rows(self.x)

    def value(self):
        return -eval(value(self.x), value(self.Q)) + value(self.t)

    def jacobian(self, var):
        # not *quite* the jacobian, but nearly.
        x = value(self.x)
        Q = value(self.Q)
        if var is self.x:
            return transpose(-2*Q*x)
        elif var is self.t:
            return 1
        else:
            raise OptimizationError('illegal jacobian')

    def hessianz(self, firstvar, secondvar, z):
        x = value(self.x)
        t = value(self.t)
        Q = value(self.Q)
        if not is1x1(z):
            raise OptimizationError('illegal z for hessianz call')
        if firstvar is secondvar is self.x:
            return -2*z*Q
        elif firstvar is secondvar is self.t:
            return zeros(rows(t))
        elif firstvar is self.x and secondvar is self.t:
            return zeros(rows(x), value(rows(t)))
        elif firstvar is self.t and secondvar is self.x:
            return zeros(rows(t), rows(x))
        else:
            raise OptimizationError('illegal hessian')

def stdquadform(c):
    vs = set(getoptvars(c))
    if len(vs) != 2:
        raise StdFormError

    # try and detect quadform(x, Q) - t.
    if isoptvar(-c.rhs):
        vs.remove(-c.rhs)
        a = c.lhs
        if a.x is vs.pop() and a.func.functionalform is functionalform:
            if ispsd(a.Q):
                return (_stdformquadconvex(a.x, a.Q, -c.rhs), [])
            else:
                raise StdFormError

    # try and detect -t + quadform(x, Q).
    if isoptvar(-c.lhs):
        vs.remove(-c.lhs)
        a = c.rhs
        if a.x is vs.pop() and a.func.functionalform is functionalform:
            if ispsd(a.Q):
                return (_stdformquadconvex(a.x, a.Q, -c.lhs), [])
            else:
                raise StdFormError

    # try and detect -quadform(x, Q) + t.
    if isoptvar(c.rhs):
        vs.remove(c.rhs)
        a = -c.lhs
        if a.x is vs.pop() and a.func.functionalform is functionalform:
            if isnsd(a.Q):
                return (_stdformquadconcave(a.x, a.Q, c.rhs), [])
            else:
                raise StdFormError

    # try and detect t - quadform(x, Q).
    if isoptvar(c.lhs):
        vs.remove(c.lhs)
        a = -c.rhs
        if a.x is vs.pop() and a.func.functionalform is functionalform:
            if isnsd(a.Q):
                return (_stdformquadconcave(a.x, a.Q, c.lhs), [])
            else:
                raise StdFormError

def checkargs(args):
    if len(args) < 1 or len(args) > 2:
        raise AtomArgsError('incorrect number of arguments')
    elif len(args) == 2 and getoptvars(args[1]):
        raise AtomArgsError('Q must not contain a variable')
    elif len(args) == 2 and not equiv(rows(args[1]), cols(args[1])):
        raise AtomArgsError('Q must be square')

applystdform = stdquadform
