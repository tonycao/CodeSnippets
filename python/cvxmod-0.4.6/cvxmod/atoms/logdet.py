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
from cvxopt import cholmod

def eval(obj):
    try:
        s = cholmod.options['supernodal']
    except KeyError:
        s = 2 # set to default.
    cholmod.options['supernodal'] = 0
    A = cvxopt.base.sparse(obj)
    F = cholmod.symbolic(A)
    cholmod.numeric(A, F)
    Di = matrix(1.0, (4,1))
    cholmod.solve(F, Di, sys=6)
    # Reset state.
    cholmod.options['supernodal'] = s
    return -sum(cvxopt.base.log(Di))


class functionalform(function, concave):
    """Understands logdet(X)."""
    def __init__(self, arg):
        self.arg = arg
        self.rows = 1
        self.cols = 1

class _stdform1(object):
    # inherit from something, later? jem. include NotImplementedError errors and a
    # test() function or so.
    """An F() standard form for -logdet(X) + t <= 0."""
    def __init__(self, X, t):
        # jem some nasty hardcoding here.
        self.rows = 1
        self.cols = 1
        self.optvars = set((X, t))
        self.X = X
        self.t = t

    def indomain(self):
        if value(self.X |gt| 0): # jem. this *must* be a variable.
            return True
        else:
            return False

    def setindomain(self):
        self.X.value = 2*eye(rows(self.X))
        self.t.value = -1

    def getdomain(self):
        return [self.X |gt| 0]

    def value(self):
        return -eval(value(self.X)) + value(self.t)

    def jacobian(self, var):
        # not *quite* the jacobian, but nearly.
        if var is self.X:
            return -value(self.X)**-1
        elif var is self.t:
            return eye(1)
        else:
            raise OptimizationError('illegal jacobian')

    def hessianz(self, firstvar, secondvar, z):
        X = value(self.X)
        t = value(self.t)
        if firstvar is secondvar is self.X:
            Xinv = value(self.X)**-1
            x = vec(Xinv)
            return -z*x*transpose(x)
        elif firstvar is secondvar is self.t:
            return zeros(rows(t))
        elif firstvar is self.X and secondvar is self.t:
            return zeros(rows(X)*cols(X), rows(t))
        elif firstvar is self.t and secondvar is self.X:
            return zeros(rows(t), rows(X)*cols(X))
        else:
            raise OptimizationError('illegal hessian')

applystdform = stdconcave(functionalform, _stdform1)
