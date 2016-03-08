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
from cvxopt.base import exp

def eval(obj):
    return cvxopt.base.log(sum(exp(obj)))

class functionalform(function, convex, increasing):
    """Understands lse(x)."""
    def __init__(self, arg):
        self.arg = arg
        self.rows = 1
        self.cols = 1

class _stdform1(object):
    # inherit from something, later? jem. include NotImplementedError errors and a
    # test() function or so.
    """An F() standard form for lse(x) - t <= 0."""
    def __init__(self, x, t):
        # jem some nasty hardcoding here.
        self.rows = 1
        self.cols = 1
        self.optvars = set((x, t))
        self.x = x
        self.t = t

    def indomain(self):
        return True

    def setindomain(self):
        self.x.value = ones(size(self.x))
        self.t.value = 1

    def value(self):
        return eval(value(self.x)) - value(self.t)

    def jacobian(self, var):
        # not *quite* the jacobian, but nearly.
        if var is self.x:
            # each x_i: exp(x_i) / sum(exp(x)).
            x = value(self.x)
            return transpose(exp(x))/sum(exp(x))
        elif var is self.t:
            return -eye(rows(self.t))
        else:
            raise OptimizationError('illegal jacobian')

    def hessianz(self, firstvar, secondvar, z):
        if firstvar is secondvar is self.x:
            # Want diag(e^x)/sum(e^x) - e^x/sum(e^x)*transpose(e^x/sum(e^x)).
            x = value(self.x)
            a = sum(exp(x))
            return z*(diag(exp(x))/a - exp(x)/a*transpose(exp(x))/a)
        elif firstvar is secondvar is self.t:
            return zeros(rows(self.t))
        elif firstvar is self.x and secondvar is self.t:
            return zeros(rows(self.x), rows(self.t))
        elif firstvar is self.t and secondvar is self.x:
            return zeros(rows(self.t), rows(self.x))
        else:
            raise OptimizationError('illegal hessian')

applystdform = stdconvex(functionalform, _stdform1)
