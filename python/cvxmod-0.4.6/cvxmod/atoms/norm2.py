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
import __builtin__

def eval(obj):
    return cvxopt.blas.nrm2(matrix(obj, tc='d'))

class functionalform(function, convex, positive):
    """Understands norm2(x)."""
    def __init__(self, arg):
        self.arg = arg
        self.rows = 1
        self.cols = 1
        self.norm2 = True

    def _getincreasing(self):
        return ispos(self.arg)
    increasing = property(_getincreasing)

    def _getdecreasing(self):
        return isneg(self.arg)
    decreasing = property(_getdecreasing)

    def cvx(self):
        return 'norm(%s)' % str(self.arg)

class _stdform1(object):
    # inherit from something, later? jem. include NotImplementedError errors and a
    # test() function or so.
    """An F() standard form for norm2(x) - t <= 0."""
    def __init__(self, x, t):
        self.rows = 1
        self.cols = 1
        self.optvars = set((x, t))
        self.x = x
        self.t = t

    def indomain(self):
        return True

    def setindomain(self):
        self.x.value = ones(size(self.x))
        self.t.value = rows(self.x)

    def value(self):
        x = value(self.x)
        t = value(self.t)
        return transpose(x)*x/t - t

    def jacobian(self, var):
        # not *quite* the jacobian, but nearly.
        x = value(self.x)
        t = value(self.t)
        if var is self.x:
            return 2*transpose(x)*(1.0/t)
        elif var is self.t:
            return -transpose(x)*x*(1.0/t**2) - 1
        else:
            raise OptimizationError('illegal jacobian')

    def hessianz(self, firstvar, secondvar, z):
        x = value(self.x)
        t = value(self.t)
        if not is1x1(z):
            raise OptimizationError('illegal z for hessianz call')
        if firstvar is secondvar is self.x:
            return z*2*(1.0/t)*eye(rows(x))
        elif firstvar is secondvar is self.t:
            return z*2*transpose(x)*x*(1.0/t**3)
        elif firstvar is self.x and secondvar is self.t:
            return z*-2*x*(1.0/t**2)
        elif firstvar is self.t and secondvar is self.x:
            return z*-2*transpose(x)*(1.0/t**2)
        else:
            raise OptimizationError('illegal hessian')

applystdform = stdconvex(functionalform, _stdform1)
