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

def iseven(obj):
    return isinstance(obj, int) and (obj % 2 == 0)

def eval(*args):
    return args[0]**args[1]

class functionalform(function, multiarg, elementwise, convex):
    """Understands power(x, p)."""
    def __init__(self, *args):
        arg = args[0]
        p = args[1]

        self.arg = arg
        self.p = p # p must be positive, ensured by checkargs.
        self.rows = rows(arg)
        self.cols = cols(arg)
        self.args = args # jem to make display function work.

    def _getincfn(self):
        if isinstance(self.p, (int, float)) and self.p <= 1:
            return ispos(self.arg)
        else:
            return ispos(self.arg)
    incfn = property(_getincfn)

    def _getdecfn(self):
        return isneg(self.arg) and iseven(self.p)
    decfn = property(_getdecfn)

    def _getconvfn(self):
        if isinstance(self.p, (int, float)) and self.p >= 1 and ispos(self.arg):
            return True
        else:
            return iseven(self.p)
    convfn = property(_getconvfn)

    def _getconcfn(self):
        return isinstance(self.p, (int, float)) and self.p <= 1 and \
                ispos(self.arg)
    concfn = property(_getconcfn)

    def _getposfn(self):
        return iseven(self.p) or ispos(self.arg)
    posfn = property(_getposfn)

    def _getvalue(self):
        return eval(value(self.arg), value(self.p))
    value = property(_getvalue)

class _stdformpowerconvex(object):
    # inherit from something, later? jem. include NotImplementedError errors and a
    # test() function or so.
    """An F() standard form for power(x, p) - t <= 0."""
    def __init__(self, x, p, t):
        self.rows = rows(x)
        self.cols = cols(x)
        self.optvars = set((x, t))
        self.x = x
        if value(p <= 0): # jem. move this test.
            raise OptimizationError('p must be positive for powers')
        else:
            self.p = p
        self.t = t
    
    def indomain(self):
        return True

    def setindomain(self):
        self.x.value = ones(size(self.x))
        self.t.value = ones(size(self.t))

    def value(self):
        return eval(value(self.x), value(self.p)) - value(self.t)

    def jacobian(self, var):
        # not *quite* the jacobian, but nearly.
        if var is self.x:
            p = value(self.p)
            x = matrix(value(self.x), tc='d')
            return p*diag(x**(p-1))
        elif var is self.t:
            return -eye(rows(self.t))
        else:
            raise OptimizationError('illegal jacobian')

    def hessianz(self, firstvar, secondvar, z):
        if firstvar is secondvar is self.x:
            p = value(self.p)
            x = matrix(value(self.x), tc='d')
            return p*(p-1)*diag(x**(p-2))
        elif firstvar is secondvar is self.t:
            return zeros(rows(self.t))
        elif firstvar is self.x and secondvar is self.t:
            return zeros(rows(self.x), rows(self.t))
        elif firstvar is self.t and secondvar is self.x:
            return zeros(rows(self.t), rows(self.x))
        else:
            raise OptimizationError('illegal hessian')

class _stdformpowerconcave(object):
    # inherit from something, later? jem. include NotImplementedError errors and a
    # test() function or so.
    """An F() standard form for -power(x, p) + t <= 0."""
    def __init__(self, x, p, t):
        self.rows = rows(x)
        self.cols = cols(x)
        self.optvars = set((x, t))
        self.x = x
        if value(p <= 0): # jem. move this test.
            raise OptimizationError('p must be positive for powers')
        else:
            self.p = p
        self.t = t
    
    def indomain(self):
        return True

    def setindomain(self):
        self.x.value = ones(size(self.x))
        self.t.value = ones(size(self.t))

    def value(self):
        return -eval(value(self.x), value(self.p)) + value(self.t)

    def jacobian(self, var):
        # not *quite* the jacobian, but nearly.
        if var is self.x:
            p = value(self.p)
            x = matrix(value(self.x), tc='d')
            return -p*diag(x**(p-1))
        elif var is self.t:
            return eye(rows(self.t))
        else:
            raise OptimizationError('illegal jacobian')

    def hessianz(self, firstvar, secondvar, z):
        if firstvar is secondvar is self.x:
            p = value(self.p)
            x = matrix(value(self.x), tc='d')
            return -p*(p-1)*diag(x**(p-2))
        elif firstvar is secondvar is self.t:
            return zeros(rows(self.t))
        elif firstvar is self.x and secondvar is self.t:
            return zeros(rows(self.x), rows(self.t))
        elif firstvar is self.t and secondvar is self.x:
            return zeros(rows(self.t), rows(self.x))
        else:
            raise OptimizationError('illegal hessian')

def stdpower(c):
    vs = set(getoptvars(c))
    if len(vs) != 2:
        raise StdFormError

    # try and detect power(x, p) - t.
    if isoptvar(-c.rhs):
        vs.remove(-c.rhs)
        a = c.lhs
        if a.arg is vs.pop() and a.func.functionalform is functionalform:
            if isconvex(a):
                return (_stdformpowerconvex(a.arg, a.p, -c.rhs), [])
            else:
                raise StdFormError

    # try and detect -t + power(x, p).
    if isoptvar(-c.lhs):
        vs.remove(-c.lhs)
        a = c.rhs
        if a.arg is vs.pop() and a.func.functionalform is functionalform:
            if isconvex(a):
                return (_stdformpowerconvex(a.arg, a.p, -c.lhs), [])
            else:
                raise StdFormError

    # try and detect -power(x, p) + t.
    if isoptvar(c.rhs):
        vs.remove(c.rhs)
        a = -c.lhs
        if a.arg is vs.pop() and a.func.functionalform is functionalform:
            if isconcave(a):
                return (_stdformpowerconcave(a.arg, a.p, c.rhs), [])
            else:
                raise StdFormError

    # try and detect t - power(x, p).
    if isoptvar(c.lhs):
        vs.remove(c.lhs)
        a = -c.rhs
        if a.arg is vs.pop() and a.func.functionalform is functionalform:
            if isconcave(a):
                return (_stdformpowerconcave(a.arg, a.p, c.lhs), [])
            else:
                raise StdFormError

def checkargs(args):
    if len(args) != 2:
        raise AtomArgsError('incorrect number of arguments')
    elif getoptvars(args[1]):
        raise AtomArgsError('p must not contain a variable')
    elif not is1x1(args[1]):
        raise AtomArgsError('p must be a 1x1 scalar')
    elif getoptvars(args[0]) and isneg(args[1]):
        # (allow negative powers of matrices.)
        raise NotImplementedError('p must not be negative')

def earlyexit(args):
    if args[1] is 1 or args[1] is 1.0:
        return args[0]

applystdform = stdpower
