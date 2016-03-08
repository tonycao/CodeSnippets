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

def eval(*args):
    x = args[0]
    if len(args) == 2:
        M = args[1]
    else:
        M = 1

    x = matrix(x, tc='d')
    out = matrix(zeros(size(x)), tc='d')
    for i in range(len(x)):
        if abs(x[i]) <= M:
            out[i] = x[i]**2
        else:
            out[i] = 2*M*abs(x[i]) - M**2
    return out

class functionalform(function, multiarg, elementwise, convex, positive):
    """Understands huber(x, M)."""
    def __init__(self, *args):
        x = args[0]
        if len(args) == 2:
            M = args[1]
        else:
            M = 1
        self.x = x
        self.M = M
        self.rows = rows(x)
        self.cols = cols(x)
        self.args = args # jem to make display function work.

    def _getincfn(self):
        return ispos(self.x)
    incfn = property(_getincfn)

    def _getdecfn(self):
        return isneg(self.x)
    decfn = property(_getdecfn)

    def _getvalue(self):
        return eval(value(self.x), value(self.M))
    value = property(_getvalue)

class stdformhuber(object):
    # inherit from something, later? jem. include NotImplementedError errors and a
    # test() function or so.
    """An F() standard form for huber(x) - t <= 0."""
    def __init__(self, x, M, t):
        self.rows = rows(x)
        self.cols = cols(x)
        self.optvars = set((x, t))
        self.x = x
        if value(M <= 0): # jem. move this test.
            raise OptimizationError('M must be positive for huber')
        else:
            self.M = M
        self.t = t
    
    def indomain(self):
        return True

    def setindomain(self):
        self.x.value = 0.05*value(self.M)*ones(size(self.x))
        self.t.value = ones(size(self.t))

    def value(self):
        return eval(value(self.x), value(self.M)) - value(self.t)

    def jacobian(self, var):
        # not *quite* the jacobian, but nearly.
        if var is self.x:
            M = value(self.M)
            x = matrix(value(self.x), tc='d')
            out = matrix(zeros(size(x)), tc='d')
            for i in range(len(x)):
                if x[i] < -M:
                    out[i] = -2*M
                elif x[i] > M:
                    out[i] = 2*M
                else:
                    out[i] = 2*x[i]
            return diag(out)
        elif var is self.t:
            return -eye(rows(self.t))
        else:
            raise OptimizationError('illegal jacobian')

    def hessianz(self, firstvar, secondvar, z):
        if firstvar is secondvar is self.x:
            M = value(self.M)
            x = matrix(value(self.x), tc='d')
            out = matrix(zeros(size(x)), tc='d')
            for i in range(len(x)):
                if abs(x[i]) <= M:
                    out[i] = 2 # otherwise leave at 0.
            return diag(diag(out)*z)
        elif firstvar is secondvar is self.t:
            return zeros(rows(self.t))
        elif firstvar is self.x and secondvar is self.t:
            return zeros(rows(self.x), rows(self.t))
        elif firstvar is self.t and secondvar is self.x:
            return zeros(rows(self.t), rows(self.x))
        else:
            raise OptimizationError('illegal hessian')

def stdhuber(c):
    vs = set(getoptvars(c))
    if len(vs) != 2:
        raise StdFormError

    # try and detect huber(x, M) - t.
    if isoptvar(-c.rhs):
        vs.remove(-c.rhs)
        a = c.lhs
        if a.x is vs.pop() and a.func.functionalform is functionalform:
            return (stdformhuber(a.x, a.M, -c.rhs), [])

    # try and detect -t + huber(x, M).
    if isoptvar(-c.lhs):
        vs.remove(-c.lhs)
        a = c.rhs
        if a.x is vs.pop() and a.func.functionalform is functionalform:
            return (stdformhuber(a.x, a.M, -c.lhs), [])

def checkargs(args):
    if len(args) < 1 or len(args) > 2:
        raise AtomArgsError('incorrect number of arguments')
    elif len(args) == 2 and getoptvars(args[1]):
        raise AtomArgsError('M must not contain an optvar')
    elif len(args) == 2 and not is1x1(args[1]):
        raise AtomArgsError('M must be a 1x1 scalar')

applystdform = stdhuber
