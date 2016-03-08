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


# Basic atoms to go with jo.py: convex optimization modelling for cvxopt.

# these functions are put here because they have epiorhypos rather than derivatives.

import __builtin__
from cvxmod.base import *
from cvxmod.base import _maxeignum, _mineignum
from cvxmod.setsbase import *
from cvxmod.symbolic import *
from cvxmod.util import iterable

__all__ = ["sum", "min", "max", "norm1", "pos", "neg", "abs", "norminf",
           "maxeig", "mineig"]

class sumfunction(multfunction):
    """The sum of vector elements, or the column sums of a matrix."""
    name = 'sum'
    def __init__(self, arg):
        self.arg = arg
        if equiv(cols(arg), 1) or equiv(rows(arg), 1):
            self.rows = 1
            self.cols = 1
        else:
            self.rows = 1
            self.cols = cols(arg)
        
        if equiv(rows(arg), 1):
            self._lhs = arg
        else:
            self._rhs = arg
    
    def __str__(self):
        return 'sum(%s)' % str(self.arg)

    def _getlhs(self):
        try:
            return self._lhs
        except AttributeError:
            return ones(1, rows(self._rhs), True)
    lhs = property(_getlhs)

    def _getrhs(self):
        try:
            return self._rhs
        except AttributeError:
            return ones(cols(self._lhs), 1, True)
    rhs = property(_getrhs)

    # Next two functions to override multfunction functions.
    def expandtr(self):
        return self

    def getoptvars(self):
        return getoptvars(self.arg)

    def getassertions(self):
        return getassertions(self.arg)

    def getimplicit(self):
        return getimplicit(self.arg)

    def _getconvex(self):
        return isconvex(self.arg)
    convex = property(_getconvex)

    def _getconcave(self):
        return isconcave(self.arg)
    concave = property(_getconcave)

    def _getincreasing(self):
        return isincreasing(self.arg)
    increasing = property(_getincreasing)

    def _getdecreasing(self):
        return isdecreasing(self.arg)
    decreasing = property(_getdecreasing)

    def cvx(self):
        return "sum(%s)" % cvx(self.arg)

    def _getpos(self):
        return ispos(self.arg)
    pos = property(_getpos)

    def _getneg(self):
        return isneg(self.arg)
    neg = property(_getneg)

def sum(obj):
    """Sum of vector elements."""
    # matrix behaviour somewhat undefined.
    # jem. possibly needs revision to reduce behaviour it's overriding. Can't
    # use __builtin__.sum because it does too much.
    if is1x1(obj):
        return obj
    elif isinstance(obj, (matrix, spmatrix)):
        return __builtin__.sum(obj)
    else:
        if isinstance(obj, multfunction) and equiv(obj.lhs, -1):
            # jem experimental. may provide unexpected (and thus unhelpful)
            # simplification at times.
            return -1*sumfunction(-1*obj)
        else:
            return sumfunction(obj)

class absfunction(function, elementwise, convex, positive):
    name = 'abs'
    def __init__(self, arg):
        self.arg = arg
        self.rows = rows(arg)
        self.cols = cols(arg)

    def _getvalue(self):
        return abs(value(self.arg))
    value = property(_getvalue)

    def epiorhypo(self):
        # handles matrices, too, for elementwise. is this a good idea? jem.
        t = dummyvar(size(self.arg))
        s = stdstruct()
        s += (self.arg <= t).split()
        s += (-self.arg <= t).split()
        return (t, s)

def abs(obj):
    """Overloads the built-in abs function for convex optimization."""
    try:
        return __builtin__.abs(obj)
    except TypeError:
        if ispos(obj):
            return obj
        elif isneg(obj):
            return -obj
        else:
            return absfunction(obj)

class singleargmaxfunction(function, convex, increasing):
    """The maximum element of a single argument."""
    name = 'max'
    def __init__(self, arg):
        self.arg = arg
        self.rows = 1
        self.cols = 1

    def getparams(self):
        return getparams(self.arg)

    def epiorhypo(self):
        t = dummyvar(1, 1)
        s = stdstruct()
        s += (self.arg <= ones(size(self.arg), symb=True)*t).split()
        return (t, s)

    def _getvalue(self):
        return max(value(self.arg))
    value = property(_getvalue)

class multiargmaxfunction(function, convex, increasing):
    # jem. the convex here actually doesn't do anything.
    # scalar mutates to appropriate size.
    def __init__(self, args):
        r = 1
        c = 1
        for x in args:
            if is1x1(x) or equiv(size(x), (r, c)) or equiv((r, c), (1, 1)):
                if equiv((r, c), (1, 1)):
                    r = rows(x)
                    c = cols(x)
                    continue
                elif equiv(r, 1) and (equiv(cols(x), 1) or equiv(cols(x), c)):
                    r = rows(x)
                    continue
                elif (equiv(rows(x), 1) or equiv(rows(x), r)) and equiv(c, 1):
                    c = cols(x)
                    continue
            else:
                raise AtomArgsError('incompatibly sized max arguments')

        self.args = args
        self.rows = r
        self.cols = c
        self.name = 'max'

    def getparams(self):
        return getparams(self.args)

    def epiorhypo(self):
        # doesn't handle matrices at the moment.
        t = dummyvar(size(self))
        
        s = stdstruct()
        for x in self.args:
            if equiv(size(x), size(self)):
                s += (x <= ones(size(x))*t).split()
            else:
                # jem: look into whether this is quite what we want?
                s += (x*ones(size(self)) <= ones(size(x))*t).split()

        return (t, s)

    def _getvalue(self):
        return max(*value(self.args))
    value = property(_getvalue)

    def _getnegative(self):
        for x in self.args:
            if not ispos(x):
                return False
        else:
            return True
    negative = property(_getnegative)

    def _getpositive(self):
        for x in self.args:
            if ispos(x):
                return True
        else:
            return False
    positive = property(_getpositive)

    def _getconvex(self):
        for x in self.args:
            if not isconvex(x):
                return False
        else:
            return True
    convex = property(_getconvex)

    def _getincreasing(self):
        for x in self.args:
            if not isincreasing(x):
                return False
        else:
            return True
    increasing = property(_getincreasing)

    def _getdecreasing(self):
        for x in self.args:
            if not isdecreasing(x):
                break
        else:
            return True
    decreasing = property(_getdecreasing)

def max(*args):
    #"""Maximum element of a vector."""
    # need to upgrade this to handle things like max(matrix((1,2)), matrix((2,3))).
    if len(args) > 1:
        if not getoptvars(args) and not getparams(args):
            r = __builtin__.max([rows(x) for x in args])
            c = __builtin__.max([cols(x) for x in args])

            if (r,c) == (1,1):
                return __builtin__.max(args)

            args = list(args)
            for i in xrange(len(args)):
                if size(args[i]) == (1,1):
                    args[i] = args[i]*matrix(ones(r,c))
                elif size(args[i]) != (r,c):
                    raise AtomArgsError('incompatible arguments to max')

            z = zeros(r, c)
            for i in range(r*c):
                z[i] = __builtin__.max([x[i] for x in args])

            return z
        else:
            return multiargmaxfunction(args)
    else:
        arg = args[0]
        if iterable(arg):
            return max(*arg)
        elif isinstance(arg, (int, float)):
            return arg
        elif not getoptvars(arg) and not getparams(arg):
            return __builtin__.max(arg)
        elif is1x1(arg):
            return arg
        else:
            return singleargmaxfunction(arg)
        
class singleargminfunction(function, concave, increasing):
    """The minimum element of a single argument."""
    name = 'min'
    def __init__(self, arg):
        self.arg = arg
        self.rows = 1
        self.cols = 1
    
    def getparams(self):
        return getparams(self.arg)

    def epiorhypo(self):
        t = dummyvar(1, 1)
        s = stdstruct()
        s += (ones(size(self.arg))*t <= self.arg).split()
        return (t, s)

    def _getvalue(self):
        return min(value(self.arg))
    value = property(_getvalue)

class multiargminfunction(function, concave, increasing):
    # jem. the convex here actually doesn't do anything.
    # scalar mutates to appropriate size.
    name = 'min'
    def __init__(self, args):
        r = 1
        c = 1
        for x in args:
            if is1x1(x) or equiv(size(x), (r, c)) or equiv((r, c), (1, 1)):
                if equiv((r, c), (1, 1)):
                    r = rows(x)
                    c = cols(x)
                    continue
                elif equiv(r, 1) and (equiv(cols(x), 1) or equiv(cols(x), c)):
                    r = rows(x)
                    continue
                elif (equiv(rows(x), 1) or equiv(rows(x), r)) and equiv(c, 1):
                    c = cols(x)
                    continue
            else:
                raise AtomArgsError('incompatibly sized min arguments')

        self.args = args
        self.rows = r
        self.cols = c

    def getparams(self):
        return getparams(self.args)

    def epiorhypo(self):
        # doesn't handle matrices at the moment.
        t = dummyvar(size(self))
        
        s = stdstruct()
        for x in self.args:
            if equiv(size(x), size(self)):
                s += (x >= ones(size(x))*t).split()
            else:
                # jem: look into whether this is quite what we want?
                s += (x*ones(size(self)) >= ones(size(x))*t).split()

        return (t, s)

    def _getvalue(self):
        return min(*value(self.args))
    value = property(_getvalue)

    def _getnegative(self):
        for x in self.args:
            if ispos(x):
                return True
        else:
            return False
    negative = property(_getnegative)

    def _getpositive(self):
        for x in self.args:
            if not ispos(x):
                return True
        else:
            return False
    positive = property(_getpositive)

    def _getconcave(self):
        for x in self.args:
            if not isconcave(x):
                return False
        else:
            return True
    concave = property(_getconcave)

    def _getincreasing(self):
        for x in self.args:
            if not isincreasing(x):
                return False
        else:
            return True
    increasing = property(_getincreasing)

    def _getdecreasing(self):
        for x in self.args:
            if not isdecreasing(x):
                break
        else:
            return True
    decreasing = property(_getdecreasing)

def min(*args):
    #"""Maximum element of a vector."""
    # need to upgrade this to handle things like min(matrix((1,2)), matrix((2,3))).
    if len(args) > 1:
        if not getoptvars(args) and not getparams(args):
            r = __builtin__.min([rows(x) for x in args])
            c = __builtin__.min([cols(x) for x in args])

            if (r,c) == (1,1):
                return __builtin__.min(args)

            args = list(args)
            for i in xrange(len(args)):
                if size(args[i]) == (1,1):
                    args[i] = args[i]*matrix(ones(r,c))
                elif size(args[i]) != (r,c):
                    raise AtomArgsError('incompatible arguments to min')

            z = zeros(r, c)
            for i in range(r*c):
                z[i] = __builtin__.min([x[i] for x in args])

            return z
        else:
            return multiargminfunction(args)
    else:
        arg = args[0]
        if iterable(arg):
            return min(*arg)
        elif isinstance(arg, (int, float)):
            return arg
        elif not getoptvars(arg) and not getparams(arg):
            return __builtin__.min(arg)
        elif is1x1(arg):
            return arg
        else:
            return singleargminfunction(arg)
        
class norm1function(function, convex, positive):
    name = 'norm1'
    def __init__(self, arg):
        self.arg = arg
        self.rows = 1
        self.cols = 1

    def _getvalue(self):
        return sum(abs(value(self.arg)))
    value = property(_getvalue)

    def epiorhypo(self):
        t = dummyvar(1, 1)
        (t2, s) = abs(self.arg).epiorhypo()
        s += (t == sum(t2)).split()
        return (t, s)

    def _getinc(obj):
        if ispos(obj.arg): # function is inc.
            return isincreasing(obj.arg)
        elif isneg(obj.arg): # function is dec.
            return isdecreasing(obj.arg)
        else:
            return False
    inc = property(_getinc)

    def _getdec(obj):
        if ispos(obj.arg): # function is inc.
            return isdecreasing(obj.arg)
        elif isneg(obj.arg): # function is dec.
            return isincreasing(obj.arg)
        else:
            return False
    dec = property(_getdec)

    def cvx(self):
        return 'norm(%s, 1)' % str(self.arg)

def norm1(obj):
    if isinstance(obj, (int, float, matrix, spmatrix)):
        return sum(abs(obj))
    else:
        # jem. this (and possibly other situations) will be problematic with
        # params. need some kind of conditional comparison / put on stack
        # for later assertion.
        if cols(obj) > 1:
            raise DimError('norm1 arg must be a column vector')
        else:
            return norm1function(obj)

class norminffunction(function, convex, positive):
    name = 'norminf'
    def __init__(self, arg):
        self.arg = arg
        self.rows = 1
        self.cols = 1

    def _getvalue(self):
        return max(abs(value(self.arg)))
    value = property(_getvalue)

    def epiorhypo(self):
        t = dummyvar(1, 1)
        (abst, s) = abs(self.arg).epiorhypo()
        (maxt, s2) = max(abst).epiorhypo()
        s += s2
        s += (t >= maxt).split()
        return (t, s)

    def _getinc(obj):
        if ispos(obj.arg): # function is inc.
            return isincreasing(obj.arg)
        elif isneg(obj.arg): # function is dec.
            return isdecreasing(obj.arg)
        else:
            return False
    inc = property(_getinc)

    def _getdec(obj):
        if ispos(obj.arg): # function is inc.
            return isdecreasing(obj.arg)
        elif isneg(obj.arg): # function is dec.
            return isincreasing(obj.arg)
        else:
            return False
    dec = property(_getdec)

    def cvx(self):
        return 'norm(%s, inf)' % str(self.arg)

def norminf(obj):
    if isinstance(obj, (int, float, matrix, spmatrix)):
        return max(abs(obj))
    else:
        # jem. this (and possibly other situations) will be problematic with
        # params. need some kind of conditional comparison / put on stack
        # for later assertion.
        if cols(obj) > 1:
            raise DimError('norminf arg must be a column vector')
        else:
            return norminffunction(obj)

class posfunction(function, elementwise, convex, increasing, positive):
    """The positive component of an argument."""
    name ='pos'
    def __init__(self, arg):
        self.arg = arg
        self.rows = rows(arg)
        self.cols = cols(arg)

    def getparams(self):
        return getparams(self.arg)

    def epiorhypo(self):
        # doesn't handle matrices at the moment.
        t = dummyvar(size(self.arg))
        s = stdstruct()
        s += (t >= 0).split()
        s += (t >= self.arg).split()
        return (t, s)

    def _getvalue(self):
        return pos(value(self.arg))
    value = property(_getvalue)

def pos(obj):
    if isinstance(obj, (int, float)):
        return __builtin__.max(obj, 0)
    elif isinstance(obj, (matrix, spmatrix)):
        (r, c) = size(obj)
        z = zeros(r, c, full=True)
        for i in xrange(r*c):
            z[i] = __builtin__.max(obj[i], 0)
        return z
    elif isneg(obj):
        return zeros(size(obj))
    elif ispos(obj):
        return obj
    else:
        return posfunction(obj)

class negfunction(function, elementwise, concave, increasing, negative):
    """The negative component of an argument."""
    name ='neg'
    def __init__(self, arg):
        self.arg = arg
        self.rows = rows(arg)
        self.cols = cols(arg)

    def epiorhypo(self):
        # doesn't handle matrices at the moment.
        t = dummyvar(size(self.arg))
        s = stdstruct()
        s += (t <= 0).split()
        s += (t <= self.arg).split()
        return (t, s)

    def _getvalue(self):
        return neg(value(self.arg))
    value = property(_getvalue)

def neg(obj):
    if isinstance(obj, (int, float)):
        return __builtin__.min(obj, 0)
    elif isinstance(obj, (matrix, spmatrix)):
        (r, c) = size(obj)
        z = zeros(r, c)
        for i in xrange(r*c):
            z[i] = __builtin__.min(obj[i], 0)
        return z
    elif isneg(obj):
        return obj
    elif ispos(obj):
        return zeros(size(obj))
    else:
        return negfunction(obj)

class maxeigfunction(matrixfunction, convex, increasing):
    """The maximum eigenvalue of a matrix."""
    # jem: do know some stuff about positivity / negativity here.
    name ='maxeig'
    def __init__(self, arg):
        if not equiv(rows(arg), cols(arg)):
            raise DimError("cannot find maximum eigenvalue of non-square object")
        self.arg = arg
        self.rows = 1
        self.cols = 1

    def epiorhypo(self):
        # doesn't handle matrices at the moment.
        t = dummyvar()
        s = stdstruct()
        if not issymm(self.arg):
            xs = dummyvar(size(self.arg), symm=True)
            s += (xs == self.arg).split()
            s += (xs |lt| t*eye(rows(self.arg), True)).split()
        else:
            s += (self.arg |lt| t*eye(rows(self.arg), True)).split()
        return (t, s)

    def _getvalue(self):
        return maxeig(value(self.arg))
    value = property(_getvalue)
    def cvx(self):
        return "lambda_max(%s)" % str(self.arg)

def maxeig(obj):
    if isinstance(obj, (int, float, matrix, spmatrix)):
        return _maxeignum(obj)
    else:
        return maxeigfunction(obj)

class mineigfunction(matrixfunction, concave, increasing):
    """The minimum eigenvalue of a matrix."""
    # jem: do know some stuff about positivity / negativity here.
    name ='mineig'
    def __init__(self, arg):
        if not equiv(rows(arg), cols(arg)):
            raise DimError("cannot find minimum eigenvalue of non-square object")
        self.arg = arg
        self.rows = 1
        self.cols = 1

    def epiorhypo(self):
        # doesn't handle matrices at the moment.
        t = dummyvar()
        s = stdstruct()
        if not issymm(self.arg):
            xs = dummyvar(size(self.arg), symm=True)
            s += (xs == self.arg).split()
            s += (xs |gt| t*eye(rows(self.arg), True)).split()
        else:
            s += (self.arg |gt| t*eye(rows(self.arg), True)).split()
        return (t, s)

    def _getvalue(self):
        return mineig(value(self.arg))
    value = property(_getvalue)

    def cvx(self):
        return "lambda_min(%s)" % str(self.arg)

def mineig(obj):
    if isinstance(obj, (int, float, matrix, spmatrix)):
        return _mineignum(obj)
    else:
        return mineigfunction(obj)
