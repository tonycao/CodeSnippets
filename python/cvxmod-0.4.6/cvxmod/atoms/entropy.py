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

# base e.

# user imports
import cvxopt.base

def eval(obj):
    # jem add support of 0 to this.
    if isinstance(obj, (int, float)):
        obj = matrix(obj, tc='d')

    return -sum(cvxopt.base.mul(obj, cvxopt.base.log(obj)))

class functionalform(function, concave):
    """Understands entropy(x)."""
    name = 'entropy'
    def __init__(self, arg):
        self.arg = arg
        self.rows = 1
        self.cols = 1

class _stdform1(object):
    # inherit from something, later? jem. include NotImplementedError errors and a
    # test() function or so.
    """An F() standard form for -entropy(x) + t <= 0."""
    def __init__(self, x, t):
        # jem some nasty hardcoding here.
        self.rows = 1
        self.cols = 1
        self.optvars = set((x, t))
        self.x = x
        self.t = t

    def indomain(self):
        if value(self.x > 0):
            return True
        else:
            return False

    def getdomain(self):
        return [self.x > 0]

    def setindomain(self):
        self.x.value = ones(size(self.x))
        self.t.value = 2

    def value(self):
        return -eval(value(self.x)) + value(self.t)

    def jacobian(self, var):
        # not *quite* the jacobian, but nearly.
        if var is self.x:
            return transpose(cvxopt.base.log(value(self.x))) + 1
        elif var is self.t:
            return 1
        else:
            raise OptimizationError('illegal jacobian')

    def hessianz(self, firstvar, secondvar, z):
        x = value(self.x)
        t = value(self.t)
        if firstvar is secondvar is self.x:
            return z*diag(x**-1)
        elif firstvar is secondvar is self.t:
            return 0
        elif firstvar is self.x and secondvar is self.t:
            return zeros(rows(x), rows(t))
        elif firstvar is self.t and secondvar is self.x:
            return zeros(rows(t), rows(x))
        else:
            raise OptimizationError('illegal hessian')

applystdform = stdconcave(functionalform, _stdform1)
