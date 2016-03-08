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

# jem. this function needs very careful verification.

# user imports
import cvxopt.base

def eval(u, v):
    u = matrix(u, tc='d')
    v = matrix(v, tc='d')
    return sum(cvxopt.base.mul(u, cvxopt.base.log(cvxopt.base.mul(u, v**-1))))

# jem. monotonicity?
class functionalform(function, convex):
    """Understands kl(u, v)."""
    def __init__(self, u, v):
        self.u = u
        self.v = v
        self.args = (u, v)
        self.rows = 1
        self.cols = 1

    def _getvalue(self):
        return eval(value(self.u), value(self.v))
    value = property(_getvalue)

class stdformkl(object):
    # inherit from something, later? jem. include NotImplementedError errors and a
    # test() function or so.
    """An F() standard form for kl(u, v) - t <= 0."""
    def __init__(self, u, v, t):
        # jem some nasty hardcoding here.
        self.rows = 1
        self.cols = 1
        self.optvars = set((u, v, t))
        self.u = u
        self.v = v
        self.t = t

    def indomain(self):
        if value(self.u >= 0) and value(self.v >= 0):
            return True
        else:
            return False

    def getdomain(self):
        return [self.u >= 0, self.v >= 0]

    def setindomain(self):
        self.u.value = ones(size(self.u))
        self.v.value = ones(size(self.v))
        self.t.value = 1

    def value(self):
        return eval(value(self.u), value(self.v)) - value(self.t)

    def jacobian(self, var):
        u = matrix(value(self.u), tc='d') # hard coding to make cvxopt.base.mul work.
        v = matrix(value(self.v), tc='d')
        t = value(self.t)
        if var is self.u:
            # log(u/v) + 1.
            return transpose(cvxopt.base.log(cvxopt.base.mul(u, v**-1))) + 1
        elif var is self.v:
            # -u/v.
            return transpose(cvxopt.base.mul(-u, v**-1))
        elif var is self.t:
            return -eye(rows(self.t))
        else:
            raise OptimizationError('illegal jacobian')

    def hessianz(self, firstvar, secondvar, z):
        u = matrix(value(self.u), tc='d')
        v = matrix(value(self.v), tc='d')
        t = value(self.t)

        if firstvar is secondvar is self.u:
            # 1/u
            return z*diag(u**-1)
        elif firstvar is secondvar is self.v:
            # u/(v**2)
            return z*diag(cvxopt.base.mul(u, v**-2))
        elif firstvar is secondvar is self.t:
            return zeros(rows(self.t))
        elif firstvar is self.u and secondvar is self.v:
            # -1/v
            return z*diag(-v**-1)
        elif firstvar is self.v and secondvar is self.u:
            # -1/v
            return z*diag(-v**-1)
        elif firstvar is self.t and secondvar in set((self.u, self.v)):
            return zeros(rows(firstvar), rows(secondvar))
        elif firstvar in set((self.u, self.v)) and secondvar is self.t:
            return zeros(rows(firstvar), rows(secondvar))
        else:
            raise OptimizationError('illegal hessian')

def stdkl(c):
    vs = set(getoptvars(c))
    if len(vs) != 3:
        raise StdFormError

    # try and detect kl(u, v) - t.
    if isoptvar(-c.rhs):
        vs.remove(-c.rhs)
        a = c.lhs
        if set(a.args) == vs and a.func.functionalform is functionalform:
            s = stdformkl(a.args[0], a.args[1], -c.rhs)
            return (s, s.getdomain())

    # try and detect -t + kl(u, v).
    if isoptvar(-c.lhs):
        vs.remove(-c.lhs)
        a = c.rhs
        if set(a.args) == vs and a.func.functionalform is functionalform:
            s = stdformkl(a.args[0], a.args[1], -c.lhs)
            return (s, s.getdomain())

def checkargs(args):
    if len(args) != 2:
        raise AtomArgsError('incorrect number of arguments')

applystdform = stdkl
