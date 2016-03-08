"""
Simple sets for CVXMOD.

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

from cvxmod.base import *
from cvxmod.atoms import square, norm1, norm2, norminf

__all__ = ["norm2ball", "norm1ball", "norminfball", "probsimp",
           "posorth", "negorth", "reals", "psdcone", "nsdcone"]

class norm2ball(cvxmodset):
    def __init__(self, n):
        if isinstance(n, int):
            pass
        elif isinstance(n, symbol) and n.role == 'param':
            pass
        else:
            raise TypeError('ball dimension must be int or param')

        if not is1x1(n):
            raise TypeError('ball dimension must be a scalar')

        self.n = n
        self.rows = n # acceptable rows of argument.
        self.cols = 1 # acceptable cols of argument.

    def __repr__(self):
        return '<norm2 ball in R^%s>' % str(self.n)

    def __str__(self):
        return 'norm2ball(%s)' % str(self.n)

    def constrform(self, expr):
        return (norm2(expr) <= 1).split()

class norm1ball(cvxmodset):
    def __init__(self, n):
        if isinstance(n, int):
            pass
        elif isinstance(n, symbol) and n.role == 'param':
            pass
        else:
            raise TypeError('ball dimension must be int or param')

        self.n = n
        self.rows = n # acceptable rows of argument.
        self.cols = 1 # acceptable cols of argument.

    def __repr__(self):
        return '<norm1 ball in R^%s>' % str(self.n)

    def __str__(self):
        return 'norm1ball(%s)' % str(self.n)

    def constrform(self, expr):
        return (norm1(expr) <= 1).split()

class norminfball(cvxmodset):
    def __init__(self, n):
        if isinstance(n, int):
            pass
        elif isinstance(n, symbol) and n.role == 'param':
            pass
        else:
            raise TypeError('ball dimension must be int or param')

        self.n = n
        self.rows = n # acceptable rows of argument.
        self.cols = 1 # acceptable cols of argument.

    def __repr__(self):
        return '<norminf ball in R^%s>' % str(self.n)

    def __str__(self):
        return 'norminfball(%s)' % str(self.n)

    def constrform(self, expr):
        return [norminf(expr) <= 1]

class probsimp(cvxmodset):
    def __init__(self, n):
        if isinstance(n, int):
            pass
        elif isinstance(n, symbol) and n.role == 'param':
            pass
        else:
            raise TypeError('simplex dimension must be int or param')

        self.n = n
        self.rows = n # acceptable rows of argument.
        self.cols = 1 # acceptable cols of argument.

    def __repr__(self):
        return '<probability simplex in R^%s>' % str(self.n)

    def __str__(self):
        return 'probsimp(%s)' % str(self.n)

    def constrform(self, expr):
        s = (sum(expr) == 1).split()
        s += (expr >= 0).split()
        return s

class posorth(cvxmodset):
    def __init__(self, n):
        if isinstance(n, int):
            pass
        elif isinstance(n, symbol) and n.role == 'param':
            pass
        else:
            raise TypeError('simplex dimension must be int or param')

        self.n = n
        self.rows = n # acceptable rows of argument.
        self.cols = 1 # acceptable cols of argument.

    def __repr__(self):
        return '<positive orthant in R^%s>' % str(self.n)

    def __str__(self):
        return 'posorth(%s)' % str(self.n)

    def constrform(self, expr):
        return (expr >= 0).split()

class negorth(cvxmodset):
    def __init__(self, n):
        if isinstance(n, int):
            pass
        elif isinstance(n, symbol) and n.role == 'param':
            pass
        else:
            raise TypeError('simplex dimension must be int or param')

        self.n = n
        self.rows = n # acceptable rows of argument.
        self.cols = 1 # acceptable cols of argument.

    def __repr__(self):
        return '<negative orthant in R^%s>' % str(self.n)

    def __str__(self):
        return 'negorth(%s)' % str(self.n)

    def constrform(self, expr):
        return (expr <= 0).split()

class reals(cvxmodset):
    def __init__(self, n):
        if isinstance(n, int):
            pass
        elif isinstance(n, symbol) and n.role == 'param':
            pass
        else:
            raise TypeError('simplex dimension must be int or param')

        self.n = n
        self.rows = n # acceptable rows of argument.
        self.cols = 1 # acceptable cols of argument.

    def __repr__(self):
        return '<R^%s>' % str(self.n)

    def __str__(self):
        return 'reals(%s)' % str(self.n)

    def constrform(self, expr):
        return stdstruct()

class psdcone(cvxmodset):
    def __init__(self, n):
        if isinstance(n, int):
            pass
        elif isinstance(n, symbol) and n.role == 'param':
            pass
        else:
            raise TypeError('semidefinite cone dimension must be int or param')

        self.n = n
        self.rows = n # acceptable rows of argument.
        self.cols = n # acceptable cols of argument.

    def __repr__(self):
        return '<psd cone S+^%s>' % str(self.n)

    def __str__(self):
        return 'psdcone(%s)' % str(self.n)

    def constrform(self, expr):
        return stdstruct(psdcone=[expr |gt| 0])

class nsdcone(cvxmodset):
    def __init__(self, n):
        if isinstance(n, int):
            pass
        elif isinstance(n, symbol) and n.role == 'param':
            pass
        else:
            raise TypeError('semidefinite cone dimension must be int or param')

        self.n = n
        self.rows = n # acceptable rows of argument.
        self.cols = n # acceptable cols of argument.

    def __repr__(self):
        return '<nsd cone S+^%s>' % str(self.n)

    def __str__(self):
        return 'nsdcone(%s)' % str(self.n)

    def constrform(self, expr):
        return stdstruct(nsdcone=[expr |lt| 0])
