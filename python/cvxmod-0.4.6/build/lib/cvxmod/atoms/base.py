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

# import this for standard atom functionality.

import cvxmod
from cvxmod import *

__all__ = ["stdconcave", "stdconvex", "matrix", "spmatrix"]
__all__ += cvxmod.base.__all__

class stdconvex(object):
    def __init__(self, f, stdform):
        self.f = f
        self.stdform = stdform

    def __call__(self, c):
        # detects f(x) - t or -t + f(x) form.
        # could add general try / except for AttributeErrors.
        vs = getoptvars(c)
        if len(vs) != 2:
            raise StdFormError

        # try and detect f(x) - t.
        if isoptvar(-c.rhs):
            vs.remove(-c.rhs)
            a = c.lhs
            if a.arg is vs.pop() and a.func.functionalform is self.f:
                if hasattr(self.stdform, 'getdomain'):
                    s = self.stdform(a.arg, -c.rhs)
                    return (s, s.getdomain())
                else:
                    return (self.stdform(a.arg, -c.rhs), [])

        # try and detect -t + f(x).
        if isoptvar(-c.lhs):
            vs.remove(-c.lhs)
            a = c.rhs
            if a.arg is vs.pop() and a.func.functionalform is self.f:
                if hasattr(self.stdform, 'getdomain'):
                    s = self.stdform(a.arg, -c.lhs)
                    return (s, s.getdomain())
                else:
                    return (self.stdform(a.arg, -c.lhs), [])

        raise StdFormError

class stdconcave(object):
    def __init__(self, f, stdform):
        self.f = f
        self.stdform = stdform

    def __call__(self, c):
        # detects -f(x) + t or t - f(x) form.
        # could add general try / except for AttributeErrors.
        vs = getoptvars(c)
        if len(vs) != 2:
            raise StdFormError

        # try and detect -f(x) + t.
        if isoptvar(c.rhs):
            vs.remove(c.rhs)
            a = -c.lhs
            if a.arg is vs.pop() and a.func.functionalform is self.f:
                if hasattr(self.stdform, 'getdomain'):
                    s = self.stdform(a.arg, c.rhs)
                    return (s, s.getdomain())
                else:
                    return (self.stdform(a.arg, c.rhs), [])

        # try and detect t - f(x).
        if isoptvar(c.lhs):
            vs.remove(c.lhs)
            a = -c.rhs
            if a.arg is vs.pop() and a.func.functionalform is self.f:
                if hasattr(self.stdform, 'getdomain'):
                    s = self.stdform(a.arg, c.lhs)
                    return (s, s.getdomain())
                else:
                    return (self.stdform(a.arg, c.lhs), [])

        raise StdFormError
