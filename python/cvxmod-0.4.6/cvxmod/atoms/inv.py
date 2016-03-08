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
import cvxopt.base

def eval(obj):
    return obj**-1

class functionalform(function, elementwise):
    """Understands inv(x)."""
    def __init__(self, arg):
        self.arg = arg
        self.rows = rows(arg)
        self.cols = cols(arg)

    def _getposfn(self):
        return ispos(obj.arg)
    posfn = property(_getposfn)

    def _getnegfn(self):
        return isneg(obj.arg)
    negfn = property(_getnegfn)

    def _getincfn(self):
        return ispos(self.arg)
    incfn = property(_getincfn)

    def _getdecfn(self):
        return isneg(self.arg)
    decfn = property(_getdecfn)

    def _getconvexfn(self):
        return ispos(self.arg)
    convex = property(_getconvexfn)
    
    def _getconcavefn(self):
        return isneg(self.arg)
    concave = property(_getconcavefn)

class _stdforminvconvex(object):
    # inherit from something, later? jem. include NotImplementedError errors and a
    # test() function or so.
    """An F() standard form for inv(x) - t <= 0."""
    def __init__(self, x, t):
        self.rows = rows(x)
        self.cols = cols(x)
        self.optvars = set((x, t))
        self.x = x
        self.t = t

    def indomain(self):
        return value(self.x >= 0)

    # jem: is the following nececssary?
    def getdomain(self):
        return [self.x >= 0]

    def setindomain(self):
        self.x.value = ones(size(self.x))
        self.t.value = 2*ones(size(self.t))

    def value(self):
        return eval(value(self.x)**-1) - value(self.t)

    def jacobian(self, var):
        # not *quite* the jacobian, but nearly.
        if var is self.x:
            return -diag(value(self.x)**-2)
        elif var is self.t:
            return -eye(rows(self.t))
        else:
            raise OptimizationError('illegal jacobian')

    def hessianz(self, firstvar, secondvar, z):
        if firstvar is secondvar is self.x:
            return diag(2*diag(value(self.x)**-2)*z)
        elif firstvar is secondvar is self.t:
            return zeros(rows(self.t))
        elif firstvar is self.x and secondvar is self.t:
            return zeros(rows(self.x), rows(self.t))
        elif firstvar is self.t and secondvar is self.x:
            return zeros(rows(self.t), rows(self.x))
        else:
            raise OptimizationError('illegal hessian')

class _stdforminvconcave(object):
    # inherit from something, later? jem. include NotImplementedError errors and a
    # test() function or so.
    """An F() standard form for -inv(x) + t <= 0."""
    def __init__(self, x, t):
        self.rows = rows(x)
        self.cols = cols(x)
        self.optvars = set((x, t))
        self.x = x
        self.t = t

    def indomain(self):
        return value(self.x <= 0)

    # jem: is the following nececssary?
    def getdomain(self):
        return [self.x <= 0]

    def setindomain(self):
        self.x.value = -ones(size(self.x))
        self.t.value = 0.5*ones(size(self.t))

    def value(self):
        return -eval(value(self.x)**-1) + value(self.t)

    def jacobian(self, var):
        # not *quite* the jacobian, but nearly.
        if var is self.x:
            return diag(value(self.x)**-2)
        elif var is self.t:
            return eye(rows(self.t))
        else:
            raise OptimizationError('illegal jacobian')

    def hessianz(self, firstvar, secondvar, z):
        if firstvar is secondvar is self.x:
            return diag(-2*diag(value(self.x)**-2)*z)
        elif firstvar is secondvar is self.t:
            return zeros(rows(self.t))
        elif firstvar is self.x and secondvar is self.t:
            return zeros(rows(self.x), rows(self.t))
        elif firstvar is self.t and secondvar is self.x:
            return zeros(rows(self.t), rows(self.x))
        else:
            raise OptimizationError('illegal hessian')

def stdinv(c):
    vs = set(getoptvars(c))
    if len(vs) != 2:
        raise StdFormError

    # try and detect inv(x) - t.
    if isoptvar(-c.rhs):
        vs.remove(-c.rhs)
        a = c.lhs
        if a.arg is vs.pop() and a.func.functionalform is functionalform:
            if isconvex(a):
                return (_stdforminvconvex(a.arg, -c.rhs), [])
            else:
                raise StdFormError

    # try and detect -t + inv(x).
    if isoptvar(-c.lhs):
        vs.remove(-c.lhs)
        a = c.rhs
        if a.arg is vs.pop() and a.func.functionalform is functionalform:
            if isconvex(a):
                return (_stdforminvconvex(a.arg, -c.lhs), [])
            else:
                raise StdFormError

    # try and detect -inv(x) + t.
    if isoptvar(c.rhs):
        vs.remove(c.rhs)
        a = -c.lhs
        if a.arg is vs.pop() and a.func.functionalform is functionalform:
            if isconcave(a):
                return (_stdforminvconcave(a.arg, c.rhs), [])
            else:
                raise StdFormError

    # try and detect t - inv(x).
    if isoptvar(c.lhs):
        vs.remove(c.lhs)
        a = -c.rhs
        if a.arg is vs.pop() and a.func.functionalform is functionalform:
            if isconcave(a):
                return (_stdforminvconcave(a.arg, c.lhs), [])
            else:
                raise StdFormError

def earlyexit(args):
    if isinstance(args[0], functionalform):
        return args[0].arg

applystdform = stdinv
