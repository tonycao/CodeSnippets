"""CVXMOD version 0.4.5, 2008-06-23."""

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

# jem
# dev at jaboc net
# jem appearing at any point is a marker that the code needs inspection.

from __future__ import division

import __builtin__
import cvxopt.solvers
import cvxopt.lapack
import cvxopt.base
from cvxopt.base import matrix, spmatrix, sparse

from math import log10, ceil
from cvxmod.errors import *

import cvxopt.info
import sys
import copy

inf = float(1e300000) # handle multiple platforms.
eps = 1e-5 # jem.

OPTVAR = 'optvar'
PARAM = 'param'
DIM = 'dim'


# jem. split this into stuff that should be imported by atoms and stuff that
# should be imported in general.
__all__ = ["affine", "classify", "cols", "concathoriz", "concatvert",
           "concave", "convex", "cvx", "decreasing", "diag", "dim", "dummyvar",
           "elementwise", "etranspose", "etp", "expandtr", "eye", "function",
           "getassertions", "getdims", "getoptvars", "getparams",
           "getquadmult", "getstdforms", "getdimmult", "getvarmult",
           "getvecmult", "equiv", "increasing", "unvec", "is1x1", "isaffine",
           "isconcave", "isconvex", "isdecreasing", "isincreasing", "isneg",
           "isnsd", "isoptvar", "isparam", "ispos", "ispsd", "issymm",
           "iszero", "lhexp", "matrix", "matrixfunction", "maximize",
           "minimize", "multfunction", "multiarg", "negative", "nnz", "nnzpc",
           "norm2", "ones", "optvar", "OPTVAR", "param", "PARAM", "positive",
           "printval", "problem", "replacevars", "rhexp", "rows", "size",
           "sparse", "speye", "spmatrix", "stdformlin", "stdformsoc",
           "stdstruct", "stroptvars", "symbol", "trace", "transpose", "tp",
           "trobj", "unitvec", "value", "vec", "vectorize", "version", "zeros",
           "zm", "issparse", "nzentries", "isnonzero"]
# remove getvarmult, getquadmult, info later. change name of seed.
# remove stdformsoc. remove stdstruct. remove trobj.

def version():
    print __doc__
    print 'Using CVXOPT version', cvxopt.info.version + '.'
    print 'Platform is ' + sys.platform + '.'
    print 'Using Python version %s, located at %s.' % (sys.version[:5], sys.executable)

class lhsrhs(object):
    def getoptvars(self):
        return getoptvars(self.lhs) | getoptvars(self.rhs)

    def getassertions(self):
        a = getassertions(self.lhs) + getassertions(self.rhs)
        # jem add alternate assertions: if either is 1x1, fine; otherwise,
        # match up sizes.
        return a

    def getstdforms(self):
        return getstdforms(self.lhs) | getstdforms(self.rhs)

    def getparams(self):
        return getparams(self.lhs) | getparams(self.rhs)

    def getdims(self):
        return getdims(self.lhs) | getdims(self.rhs)

    def replacevars(self, d):
        if isoptvar(self.lhs) and self.lhs in set(d.keys()):
            self.lhs = d[self.lhs]
        else:
            replacevars(self.lhs, d)

        if isoptvar(self.rhs) and self.rhs in set(d.keys()):
            self.rhs = d[self.rhs]
        else:
            replacevars(self.rhs, d)
    def _getconvex(self):
        return isconvex(self.lhs) and isconvex(self.rhs)
    convex = property(_getconvex)

    def _getconcave(self):
        return isconcave(self.lhs) and isconcave(self.rhs)
    concave = property(_getconcave)

    def _getdecreasing(self):
        return isdecreasing(self.lhs) and isdecreasing(self.rhs)
    decreasing = property(_getdecreasing)

    def _getincreasing(self):
        return isincreasing(self.lhs) and isincreasing(self.rhs)
    increasing = property(_getincreasing)
            
    def _getpos(self):
        return ispos(self.lhs) and ispos(self.rhs)
    pos = property(_getpos)
            
    def _getneg(self):
        return isneg(self.lhs) and isneg(self.rhs)
    neg = property(_getneg)

class convex(object):
    """General holder class for convex functions."""
    convfn = True

class concave(object):
    """General holder class for concave functions."""
    concfn = True

class affine(convex, concave):
    """General holder class for affine functions."""
    # jem. need to update with (possibly) mapping functions or something.
    convfn = True
    concfn = True

class increasing(object):
    """General holder class for increasing functions."""
    incfn = True

class decreasing(object):
    """General holder class for decreasing functions."""
    decfn = True

class positive(object):
    posfn = True

class negative(object):
    negfn = True

class psd(object):
    psd = True
    nsd = False
    symm = True

class nsd(object):
    psd = False
    nsd = True
    symm = True

class symbol(affine):
    """A general holder for optvars or params involved in optimization."""
    increasing = True
    convex = True
    concave = True
    def __init__(self, name=None, rs=None, cs=None, value=None, role=PARAM,
                 pos=False, neg=False, symm=False, psd=False,
                 nsd=False, lower=None, upper=None):
        # Prevent some of these attributes from changing?
        # jem.
        # optional warning levels?
        #if not isinstance(name, str):
        #    Jwarn("using string '%s' as name" % str(name))
        if name is None:
            self.name = 'noname' + str(nonamecount())
        else:
            self.name = name

        if rs is None and cs is None and value is not None:
            rs = rows(value)
            cs = cols(value)
        else:
            if rs is None:
                rs = 1
            if cs is None:
                cs = 1

        if not is1x1(rs):
            raise TypeError("rs must be a 1x1 quantity")
        self.rows = rs

        if not is1x1(rs):
            raise TypeError("cs must be a 1x1 quantity")
        self.cols = cs

        # jem: later change these warnings to errors?
        if getparams(rs):
            Jwarn("rows should not contain parameters: use dims instead (got %s)" % str(rs))

        if getparams(cs):
            Jwarn("cols should not contain parameters: use dims instead (got %s)" % str(cs))

        self.role = role

        self.pos = pos
        self.neg = neg
        self.symm = symm
        self.psd = psd
        self.nsd = nsd
        self.lower = lower
        self.upper = upper
        
        # jem. add assertions about size. deal with parametric size.
        if value is not None:
            if isdim(rs):
                # jem: add assertion here.
                pass
            #elif rs is not rows(value):
            #    raise ValueError("value must match in size")

            if isdim(cs):
                # jem: add assertion here.
                pass
            #elif cs is not cols(value):
            #    raise ValueError("value must match in size")

        if value is not None:
            self.value = value__(value)
        else:
            self.value = None

        self._vecvar = None

    def __repr__(self):
        if isdim(self):
            return "<dim symbol %s>" % self.name

        v = self.getattrs()
        if v:
            extras = '(' + ', '.join(v) + ') '
        else:
            extras = ''

        return "<%sx%s %s%s symbol %s>" % (withbrackets(self.rows),
                                            withbrackets(self.cols), extras,
                                            self.role, self.name)

    def __getitem__(self, k):
        return symbslice(self, k)

    def getvarmult(self, var):
        if self.role in [OPTVAR, 'unitvec']:
            if self is var:
                return eye(rows(var), True)
            else:
                return 0
        elif isparam(self) and var is None:
            return self
        else:
            return 0

    def getdimmult(self, dim):
        if isdim(self) and self is dim:
            return 1
        else:
            return 0

    def getvecmult(self, var):
        if self.role in [OPTVAR, 'unitvec']:
            if self is var:
                return eye(rows(var)*cols(var), True)
            else:
                return 0
        elif isparam(self) and var is None:
            return vec(self)
        else:
            return 0

    def __mul__(self, other):
        return multiply(self, other)
    
    def __rmul__(self, other):
        return multiply(other, self)

    def __rdiv__(self, other):
        return other*(self**-1)

    def __add__(self, other):
        return addup(self, other)

    def __radd__(self, other):
        return addup(self, other)

    def __sub__(self, other):
        return addup(self, -other)
    
    def __rsub__(self, other):
        return addup(other, -self)

    def __neg__(self):
        return multiply(-1, self)

    def __pos__(self):
        return self

    def __lt__(self, other):
        return relation(self, other, '<')

    def __le__(self, other):
        return relation(self, other, '<=')

    def __gt__(self, other):
        return relation(self, other, '>')

    def __ge__(self, other):
        return relation(self, other, '>=')

    def __eq__(self, other):
        return relation(self, other, '==')

    def __float__(self):
        if is1x1(self):
            if self.value is None:
                raise OptvarValueError
            else:
                return float(self.value)
        else:
            raise ValueError('cannot convert %s to float' % self.name)

    def __int__(self):
        if is1x1(self):
            if self.value is None:
                raise OptvarValueError
            else:
                return int(self.value)
        else:
            raise ValueError('cannot convert %s to int' % self.name)

    def __str__(self):
        return self.name

    def __pow__(self, other):
        if other is -1:
            return inv(self)

    def getattrs(self):
        v = []
        if self.symm:
            v.append('symmetric')
        if self.psd:
            v.append('psd')
        if self.nsd:
            v.append('nsd')
        if self.neg:
            v.append('neg')
        if self.pos:
            v.append('pos')

        return v

    def getoptvars(self):
        if isoptvar(self):
            return set((self,))
        else:
            return set()

    def getassertions(self):
        a = [ensureint(rows(self)), ensureint(cols(self))]
        if self.symm:
            a.append(rows(self) == cols(self))

        return a

    def getparams(self):
        if isparam(self):
            return set((self,)) | getparams(self.rows) | getparams(self.cols)
        else:
            return set()

    def getdims(self):
        if isdim(self):
            return set((self,))
        else:
            return getdims(self.rows) | getdims(self.cols)

    def cvxdeclare(self):
        if isoptvar(self):
            s = ""
            if is1x1(self):
                s += "variable %s" % str(self)
            elif self.cols is 1:
                s += "variable %s(%s)" % (str(self), str(self.rows))
            else:
                s += "variable %s(%s,%s)" % (str(self), str(self.rows),
                                               str(self.cols))
            if self.symm:
                s += " symmetric"
            if self.psd:
                s += "\n    %s == semidefinite(%s)" % (str(self), str(self.rows))
            return s
        else:
            raise OptimizationError('cannot call cvxdeclare on non-optvar')

    def matlab(self):
        if isparam(self):
            s = self.name + ' = '
            if isinstance(self.value, (matrix, spmatrix)):
                s += '['
                offset = ' '*len(s)
                for i in xrange(value(rows(self))):
                    for j in xrange(value(cols(self))):
                        s += '% .5f'.rjust(6) % self.value[i,j]
                    s += ';\n'
                    s += offset

                s = s[:-(2+len(offset))] + '];\n'
            else:
                s += '% .4g'.rjust(5)
                s += ';\n' % self.value[i,j]

            return s
        else:
            return OptimizationError('cannot call matlab on non-param')

    def _getdecreasing(self):
        return not isoptvar(self)
    decreasing = property(_getdecreasing)

    def _columnize(self):
        # jem verbose notes (TM).
        # could cunningly just have a columns property that automatically
        # creates these the first time, to make it transparent (and do the same
        # with transposed version, although add extra constr to self.)
        # produce (and cache) column columns to represent this matrix variable.
        # at this stage we are solving a problem, so all params should have
        # valid values.
        (m, n) = value(size(self))

        if not isoptvar(self):
            raise OptimizationError('should not be columnizing a param')
        if n == 1:
            raise OptimizationError('should not be columnizing a column')

        self._columnsymbs = []
        # we can proceed. start by making appropriate number of columns.
        # indexing from zero, because internal only.
        for i in range(n):
            self._columnsymbs.append(optvar(self.name + '_c' + str(i), m, 1))

            # this next bit is for the required extra inequalities.
            #s.lin += (X.columns[j] == \ 
            #          self.arg*unitvec(j+1, cols(self.arg))).split()

    def _getcolumns(self):
        try:
            return self._columnsymbs
        except AttributeError:
            self._columnize()
            return self._columnsymbs
    columns = property(_getcolumns)
    # jem: consider making columns, backsubcols private?

    def backsubcols(self):
        """Moves values from self.vectors to self.value."""
        (m, n) = value(size(self))
        self.value = zeros(m, n)
        for i in range(n):
            self.value[:,i] = value(self.columns[i])

    def vectorize(self):
        if isoptvar(self):
            return self.columns
        else:
            x = []
            A = value(self)
            for i in range(value(cols(self))):
                x.append(A[:,i])
            return x

    def getvecvar(self):
        # Create a vectorized version of this variable.
        if self.symm:
            # int() is to enforce data type only, in conjunction with importing
            # division from __future__.
            m = value(rows(self))
            numfreevars = int(m*(m+1)/2)
            return unsymm(value(rows(self)))*dummyvar(numfreevars)
        else:
            return dummyvar(value(rows(self)*cols(self)), 1)

    def nzentries(self):
        if isparam(self):
            d = {}
            for i in range(value(rows(self))):
                for j in range(value(cols(self))):
                    d[i,j] = self[i,j]
            return d
        else:
            raise NotImplementedError

class symbslice(symbol):
    """Sliced (indexed) symbol, e.g. x[0] or A[2,3] or X[(1,2,3),0]."""
    def __init__(self, arg, sl):
        self.arg = arg
        self.sl = sl
        # Pairmode means that sl is a sequence of indices, i.e. diag(X) would
        # have X[((0,0), (1,1), (2,2))].
        if iterable(sl) and iterable(sl[0]) and iterable(sl[1]):
            self.pairmode = True
        else:
            self.pairmode = False
        self.role = 'slice'

    def _getrows(self):
        (rowind, colind) = self.splitsl()
        if isinstance(rowind, slice):
            if colind is None:
                a = self.getslicelen(rowind, rows(self.arg)*cols(self.arg))
            else:
                a = self.getslicelen(rowind, rows(self.arg))
            if a is None:
                # jem: this is for dimensions not yet known?
                # jem: update this to be more sensible? can calculate lengths
                # in terms of the parameter (though only to some extent).
                # could add an assertion here about the eventual value of
                # symbol.
                return symbol('?')
            else:
                return a
        elif iterable(rowind):
            return len(rowind)
        else:
            return 1
    rows = property(_getrows)

    def _getcols(self):
        (rowind, colind) = self.splitsl()
        if colind is None:
            return 1
        elif self.pairmode:
            return 1
        elif isinstance(colind, slice):
            a = self.getslicelen(colind, cols(self.arg))
            if a is None:
                # jem: this is for dimensions not yet known?
                # jem: update this to be more sensible? can calculate lengths
                # in terms of the parameter (though only to some extent).
                # could add an assertion here about the eventual value of
                # symbol.
                return symbol('?')
            else:
                return a
        elif iterable(colind):
            return len(colind)
        else:
            return 1
    cols = property(_getcols)

    def getslicelen(self, s, l):
        if s.start is None:
            start = 0
        else:
            start = s.start

        if s.stop is None:
            stop = l
        elif isinstance(s.stop, int) and s.stop < 0:
            stop = l + s.stop
        else:
            stop = s.stop

        if s.step is None:
            step = 1
        elif not isinstance(s.step, int):
            return None
        elif s.step < 0:
            # Simply make positive, for the point of view of lengths.
            step = -s.step
        else:
            step = s.step

        # just give up if anything is negative.
        if (not isinstance(start, int)) or start < 0:
            raise NotImplementedError('unsupported start index')

        if step is 1:
            return stop - start
        else:
            if isinstance(start, int) and isinstance(stop, int):
                return int(ceil((stop - start) / float(step)))
            else:
                raise NotImplementedError('unsupported start or stop indices')

    def __repr__(self):
        return "<%sx%s sliced %s symbol %s>" % (withbrackets(self.rows),
                                                withbrackets(self.cols),
                                                self.arg.role, str(self))

    def splitsl(self):
        """Splits the slice into its left- and right-hand sides."""
        # If both are lists, they have to be (row, col) pairs.
        if not iterable(self.sl):
            rowind = self.sl
            colind = None
        elif iterable(self.sl) and len(self.sl) == 2 and \
                not (iterable(self.sl[0]) and iterable(self.sl[1])):
            # Not in (row, col) pairs format.
            rowind = self.sl[0]
            colind = self.sl[1]
        else:
            # Assume in (row, col) pairs format.
            (rowind, colind) = zip(*self.sl)
        return (rowind, colind)

    def __str__(self):
        if self.pairmode:
            slstr = str(self.sl)
        else:
            if iterable(self.sl):
                (rowind, colind) = self.sl
            else:
                rowind = self.sl
                colind = None

            slstr = ''
            if isinstance(rowind, slice):
                if rowind.start:
                    slstr += str(rowind.start)
                slstr += ':'
                if rowind.stop:
                    slstr += str(rowind.stop)
                if rowind.step:
                    slstr += ':' + str(rowind.step)
            else:
                slstr += str(rowind)

            if colind is not None:
                slstr += ','
                if isinstance(colind, slice):
                    if colind.start:
                        slstr += str(colind.start)
                    slstr += ':'
                    if colind.stop:
                        slstr += str(colind.stop)
                    if colind.step:
                        slstr += ':' + str(colind.step)
                else:
                    slstr += str(colind)

        return "%s[%s]" % (str(self.arg), slstr)

    def getoptvars(self):
        return getoptvars(self.arg)

    def getparams(self):
        return getparams(self.arg)

    def _getvalue(self):
        (rowind, colind) = self.splitsl()
        if colind is None:
            return value(self.arg)[rowind]
        else:
            return value(self.arg)[rowind,colind]
    value = property(_getvalue)

    def _getincreasing(self):
        return isincreasing(self.arg)
    increasing = property(_getincreasing)

    def _getdecreasing(self):
        return isdecreasing(self.arg)
    decreasing = property(_getdecreasing)

    def _getconvex(self):
        return isconvex(self.arg)
    convex = property(_getconvex)
    
    def _getconcave(self):
        return isconcave(self.arg)
    concave = property(_getconcave)

    def _getpos(self):
        return ispos(self.arg)
    pos = property(_getpos)

    def _getneg(self):
        return isneg(self.arg)
    neg = property(_getneg)

    def getvecmult(self, var):
        m = value(rows(self.arg))
        n = value(cols(self.arg))
        if var in getoptvars(self.arg):
            (rowind, colind) = self.splitsl()
            if self.pairmode:
                L = zeros(len(rowind), value(rows(self.arg)*cols(self.arg)))
                for k in range(len(rowind)):
                    L[k,rowind[k]+m*colind[k]] = 1
                return getvecmult(L*vec(self.arg), var)

            if isinstance(rowind, slice):
                rowindices = slicetoindices(rowind, rows(self.arg))
            elif iterable(rowind):
                rowindices = rowind
            else:
                rowindices = [value(rowind)]

            if colind is None:
                L = zeros(len(rowindices), value(rows(self.arg)*cols(self.arg)))
                for (i, j) in zip(range(len(rowindices)), rowindices):
                    L[i,j] = 1
                return getvecmult(L*self.arg, var)
            else:
                colindices = slicetoindices(colind, cols(self.arg))

                L = zeros(len(rowindices), value(rows(self.arg)))
                for (i, j) in zip(range(len(rowindices)), rowindices):
                    L[i,j] = 1

                R = zeros(value(cols(self.arg)), len(colindices))
                for (i, j) in zip(colindices, range(len(colindices))):
                    R[i,j] = 1

                return getvecmult(L*self.arg*R, var)
        else:
            return 0

    def getvarmult(self, var):
        return getvecmult(self, var)

    def cvx(self):
        if is1x1(self):
            (rowind, colind) = self.splitsl()
            if colind is None:
                return '%s(%d)' % (str(self.arg), rowind+1)
            else:
                return '%s(%d,%d)' % (str(self.arg), rowind+1, colind+1)
        else:
            raise NotImplementedError('cannot cvx complicated slices')

def optvar(name=None, rows=None, cols=None, value=None, role=OPTVAR,
           pos=False, neg=False, symm=False, psd=False, nsd=False, lower=None,
           upper=None):
    """Equivalent to calling symbol(), but with default role='optvar' instead
    of 'param'."""
    return symbol(name, rows, cols, value, role, pos, neg, symm, psd,
                  nsd, lower, upper)
    
def param(name=None, rows=None, cols=None, value=None, role=PARAM,
          pos=False, neg=False, symm=False, psd=False, nsd=False):
    """Equivalent to calling symbol(), with default role='param'."""
    return symbol(name, rows, cols, value, role, pos, neg, symm, psd,
                  nsd)

def dim(name=None, value=None):
    """Equivalent to calling symbol(), but with default role='dim' instead
    of 'param'."""
    # Most of the parameters are set to False---even though they are
    # technically True, they're irrelevant.
    return symbol(name, rs=1, cs=1, value=value, role='dim', pos=True,
                  neg=False, symm=False, psd=False, nsd=False)
    
class _unitvec(symbol):
    def __init__(self, i, rows):
        m = zeros(rows,1)
        m[i] = 1
        symbol.__init__(self, 'e'+str(i), rows, 1, m, 'unit vector', False, False,
                        False, False, False)
        self.i = i

    def getvarmult(self, var):
        if var is None:
            return self

def unitvec(i, rows):
    # could sneakily allow an option to have an indeterminate number of rows -
    # resolves at runtime from requirements for multiplication to be correct.
    # jem.
    if i > rows - 1:
        raise OptimizationError('unit vector index cannot exceed number'
                                       'of rows - 1')
    elif i < 0:
        raise OptimizationError('unit vector cannot be less than 0')
    else:
        if rows == 1:
            return 1
        else:
            return _unitvec(i,rows)

class objective(object):
    """Holds objectives / convex optimization goals."""
    def __repr__(self):
        return "<objective %s; optvars: %s>" % (str(self),
                                                  stroptvars(self))

    def getoptvars(self):
        return getoptvars(self.arg)

    def getassertions(self):
        return getassertions(self.arg)

    def getstdforms(self):
        return getstdforms(self.arg)
    
    def getparams(self):
        return getparams(self.arg)

    def getdims(self):
        return getdims(self.arg)

    def _getvalue(self):
        # perhaps later make this [0] to avoid returning a matrix?
        return value(self.arg)
    value = property(_getvalue)

    def classify(self):
        if isconvex(self):
            print "convex objective."
        else:
            print "non-convex objective."

    def replacevars(self, d):
        if isoptvar(self.arg) and self.arg in set(d.keys()):
            self.arg = d[self.arg]
        else:
            replacevars(self.arg, d)

class minimizeobjective(objective):
    def __init__(self, arg):
        self.arg = arg
        self.rows = rows(arg)
        self.cols = cols(arg)

    def __str__(self):
        return "minimize %s" % str(self.arg)

    def cvx(self):
        return "minimize(%s)" % cvx(self.arg)

    def latex(self):
        return r"\mbox{mimimize} & %s" % latex(self.arg)

    def gettype(self):
        return "minimization"

    def _getconvex(self):
        return isconvex(self.arg)
    convex = property(_getconvex)

    def minarg(self):
        return self.arg
        
        # jem experimental.
        t = dummyvar(size(self.arg))
        return (minimize(t), t >= self.arg)

def minimize(obj):
    if is1x1(obj):
        return minimizeobjective(obj)
    else:
        raise TypeError('cannot minimize non-scalar expression')

class maximizeobjective(objective):
    def __init__(self, arg):
        self.arg = arg
        self.rows = rows(arg)
        self.cols = cols(arg)

    def __str__(self):
        return "maximize %s" % str(self.arg)

    def cvx(self):
        return "maximize(%s)" % cvx(self.arg)

    def latex(self):
        return r"\mbox{maximize} & %s" % latex(self.arg)

    def gettype(self):
        return "maximization"

    def _getconvex(self):
        return isconcave(self.arg)
    convex = property(_getconvex)

    def minarg(self):
        return -self.arg

class findobjective(objective):
    convex = True
    def __init__(self, optvars):
        if iterable(optvars):
            self.arg = set(optvars)
        else:
            # ensure that self.arg is type set.
            self.arg = set((optvars,))

    def __str__(self):
        return "find %s" % stroptvars(self)

    def gettype(self):
        return 'feasibility'

def find(optvars):
    return findobjective(optvars)
    
def maximize(obj):
    if is1x1(obj):
        return maximizeobjective(obj)
    else:
        raise TypeError('cannot maximize non-scalar expression')

class function(object):
    def __repr__(self):
        return "<%sx%s expression %s; optvars: %s>" % (str(self.rows),
            str(self.cols), str(self), stroptvars(self))

    def __str__(self):
        try:
            return self.name + '(%s)' % ", ".join([str(x) for x in self.args])
        except AttributeError:
            return self.name + '(%s)' % str(self.arg)

    def __mul__(self, other):
        return multiply(self, other)
    
    def __rmul__(self, other):
        return multiply(other, self)

    def __add__(self, other):
        return addup(self, other)

    def __radd__(self, other):
        return addup(self, other)

    def __sub__(self, other):
        return addup(self, -other)
    
    def __rsub__(self, other):
        return addup(other, -self)

    def __neg__(self):
        return multiply(-1, self)

    def __pos__(self):
        return self

    def __lt__(self, other):
        return relation(self, other, '<')

    def __le__(self, other):
        return relation(self, other, '<=')

    def __gt__(self, other):
        return relation(self, other, '>')

    def __ge__(self, other):
        return relation(self, other, '>=')

    def __eq__(self, other):
        return relation(self, other, '==')

    def __rdiv__(self, other):
        return other*(self**-1)

    def getoptvars(self):
        if hasattr(self, 'arg'):
            return getoptvars(self.arg)
        else:
            return getoptvars(self.args)

    def getassertions(self):
        return getassertions(self.arg)

    def replacevars(self, d):
        if hasattr(self, 'arg'):
            if isoptvar(self.arg) and self.arg in set(d.keys()):
                self.arg = d[self.arg]
            else:
                replacevars(self.arg, d)
        elif hasattr(self, 'args'):
            for i in range(len(self.args)):
                if isoptvar(self.args[i]) and self.args[i] in set(d.keys()):
                    self.args[i] = d[self.args[i]]
                else:
                    replacevars(self.args[i], d)
        else:
            raise NotImplementedError

    def getstdforms(self):
        try:
            s = self._stdforms
        except AttributeError:
            s = set()
        try:
            s |= getstdforms(self.arg)
        except AttributeError:
            s |= getstdforms(self.args)
        return s

    def getparams(self):
        if hasattr(self, 'args'):
            s = set()
            for x in self.args:
                s |= getparams(x)
            return s
        else:
            return getparams(self.arg)

    def getdims(self):
        if hasattr(self, 'args'):
            s = set()
            for x in self.args:
                s |= getdims(x)
            return s
        else:
            return getdims(self.arg)

    def _getvalue(self):
        return self.func.eval(value(self.arg))
    value = property(_getvalue)

    def _getincreasing(self):
        return (hasattr(self, 'incfn') and self.incfn and
                isincreasing(self.arg)) or \
                (hasattr(self, 'decfn') and self.decfn and
                 isdecreasing(self.arg))
    increasing = property(_getincreasing)

    def _getdecreasing(self):
        return (hasattr(self, 'decfn') and self.decfn and
                isincreasing(self.arg)) or \
                (hasattr(self, 'incfn') and self.incfn and
                 isdecreasing(self.arg))
    decreasing = property(_getdecreasing)

    # jemjemjem: (and for _getconcave, too) should isincreasing refer to the
    # extended value extension, or to the function with active domain? i.e. can
    # we always create an arbitrary extension with appropriate monotonicity if
    # the function is known monotonic over domain?
    def _getconvex(self):
        try:
            arg = self.arg
        except AttributeError:
            arg = self.args

        if hasattr(self, 'convfn') and self.convfn:
            if isaffine(arg):
                return True
            else:
                return (hasattr(self, 'incfn') and self.incfn and isconvex(arg)) or \
                        (hasattr(self, 'decfn') and self.decfn and isconcave(arg))
        else:
            return False
    convex = property(_getconvex)
    
    def _getconcave(self):
        if hasattr(self, 'concfn') and self.concfn:
            if isaffine(self.arg):
                return True
            else:
                return (hasattr(self, 'incfn') and self.incfn and \
                        isconcave(self.arg)) or \
                        (hasattr(self, 'decfn') and self.decfn and \
                         isconvex(self.arg))
        else:
            return False
    concave = property(_getconcave)

    # jem. somewhat overkill as a property.
    def _getpos(self):
        return hasattr(self, 'posfn') and self.posfn
    pos = property(_getpos)

    # jem. somewhat overkill as a property.
    def _getneg(self):
        return hasattr(self, 'negfn') and self.negfn
    neg = property(_getneg)

    # jemjemjem: (and for _getconcave, too) should isincreasing refer to the
    # extended value extension, or to the function with active domain? i.e. can
    # we always create an arbitrary extension with appropriate monotonicity if
    # the function is known monotonic over domain?
    def epiorhypo(self):
        repl = [] # for relaxations / replacements.
        if not (hasattr(self, 'multiarg') and self.multiarg):
            constr = []
            t1 = dummyvar(size(self)) # epigraph (hypograph) variable.
            if isoptvar(self.arg):
                t2 = self.arg
            else:
                t2 = dummyvar(size(self.arg)) # replacement argument.
                repl.append((self.arg, t2))
            ps = [t2]

        else:
            # Multiple argument functions.
            # Possibly should handle different monotonicity patterns?
            constr = []
            t1 = dummyvar(size(self)) # epigraph (hypograph) variable.
            ps = [] # for calling functions.
            for x in self.args:
                # replace live optvars with dummy optvars. Don't touch
                # params.
                if getoptvars(x):
                    if isoptvar(x):
                        t = x
                    else:
                        t = dummyvar(size(x))
                        repl.append((x, t))
                    ps.append(t)
                else:
                    ps.append(x)

        if isconvex(self.func(*ps) <= t1): # function is convex.
            stdform = [self.func(*ps) <= t1]
            conv = True
        elif isconvex(self.func(*ps) >= t1): # function is concave.
            stdform = [self.func(*ps) >= t1]
            conv = False
        else:
            raise ConvexityError

        for a in repl:
            (x, t) = a
            if isaffine(x):
                constr.append(x == t)
            elif hasattr(self, 'incfn') and self.incfn and conv or \
                    hasattr(self, 'decfn') and self.decfn and not conv:
                constr.append(x <= t)
            elif hasattr(self, 'decfn') and self.decfn:
                constr.append(x >= t)
            else:
                raise ConvexityError

        s = stdstruct(stdform)

        for x in constr:
            s += x.split()

        return (t1, s)
    def cvx(self):
        try:
            return self.name + '(%s)' % ", ".join([cvx(x) for x in self.args])
        except AttributeError:
            return self.name + '(%s)' % cvx(self.arg)


class elementwise(object):
    elementwise = True

class multiarg(object):
    multiarg = True

class matrixfunction(function):
    # jem not implemented.
    pass

class transposefunction(function):
    def __init__(self, arg):
        self.arg = arg
        self.rows = cols(arg)
        self.cols = rows(arg)
    
    def __str__(self):
        return "tp(%s)" % self.arg

    def cvx(self):
        return "transpose(%s)" % self.arg

    def _getconvex(self):
        return isconvex(self.arg)
    convex = property(_getconvex)

    def _getconcave(self):
        return isconcave(self.arg)
    concave = property(_getconcave)

    def _getvalue(self):
        if is1x1(self):
            return v
        else:
            # Uses cvxopt representation.
            return transpose(value(self.arg))
    value = property(_getvalue)

    def getvarmult(self, var):
        if var in getoptvars(self):
            raise TransposedVarError
        else:
            return 0

    def getvecmult(self, var):
        if var in getoptvars(self):
            return trobj(size(var))
        else:
            return 0

    def expandtr(obj):
        return etranspose(obj.arg)

    def nzentries(obj):
        d = {}
        dobj = nzentries(obj.arg)
        for (i,j) in dobj.keys():
            d[j,i] = dobj[i,j]

        return d

def transpose(obj):
    # Numeric function transpose doesn't ever give errors, it seems.
    if is1x1(obj):
        return obj
    elif isinstance(obj, (matrix, spmatrix)):
        return obj.trans()
    elif hasattr(obj, 'transpose'):
        return obj.transpose()
    elif issymm(obj):
        return obj
    else:
        if isinstance(obj, transposefunction):
            return obj.arg
        else:
            return transposefunction(obj)

tp = transpose

def etranspose(obj):
    # Transpose and expand.
    try:
        return obj.etranspose()
    except AttributeError:
        return transpose(obj)

etp = etranspose

def expandtr(obj):
    # Expand transposes.
    try:
        return obj.expandtr()
    except AttributeError:
        return obj

def issymm(obj):
    if isinstance(obj, (int, float, matrix, spmatrix)):
        return value(relation(obj, transpose(obj), '=='))

    return is1x1(obj) or hasattr(obj, 'symm') and obj.symm

class addormultfunction(lhsrhs):
    def __mul__(self, other):
        return multiply(self, other)
    
    def __rmul__(self, other):
        return multiply(other, self)

    # Handle all inequalities the same way.
    def __lt__(self, other):
        return relation(self, other, '<')

    def __le__(self, other):
        return relation(self, other, '<=')

    def __gt__(self, other):
        return relation(self, other, '>')

    def __ge__(self, other):
        return relation(self, other, '>=')

    def __eq__(self, other):
        return relation(self, other, '==')

    def __int__(self):
        return int(value(self))

    def __float__(self):
        return float(value(self))

    def __repr__(self):
        return "<%sx%s expression %s; optvars: %s>" % \
            (str(self.rows), str(self.cols), str(self), stroptvars(self))
    def __add__(self, other):
        return addup(self, other) 

    def __radd__(self, other):
        return addup(other, self)

    def __sub__(self, other):
        return addup(self, -other)

    def __rsub__(self, other):
        return addup(other, -self)

    def __neg__(self):
        return -1*self

    def __pos__(self):
        return self

class addfunction(addormultfunction):
    def __init__(self, lhs, rhs):
        # First, extract the sizes.
        lhsrows = rows(lhs)
        lhscols = cols(lhs)
        rhsrows = rows(rhs)
        rhscols = cols(rhs)

        if is1x1(lhs) or is1x1(rhs) or \
           equivdims(lhsrows, rhsrows) and equivdims(lhscols, rhscols):
            # Valid addition, proceed.
            if lhsrows is 1:
                self.rows = rhsrows
            else:
                self.rows = lhsrows

            if lhscols is 1:
                self.cols = rhscols
            else:
                self.cols = lhscols

            self.lhs = lhs
            self.rhs = rhs
            self.brackets = True

        else:
            raise DimError

    def __str__(self):
        if str(self.rhs)[0] == '-':
            return "%s - %s" %(str(self.lhs), str(self.rhs)[1:])
        else:
            return "%s + %s" %(str(self.lhs), str(self.rhs))

    def _getpsd(self):
        return ispsd(self.lhs) and ispsd(self.rhs)
    psd = property(_getpsd)

    def _getnsd(self):
        return isnsd(self.lhs) and isnsd(self.rhs)
    nsd = property(_getnsd)
            
    def _getvalue(self):
        return value(self.lhs) + value(self.rhs)
    value = property(_getvalue)

    def getvarmult(self, var):
        if var is None and not getoptvars(self):
            return self
        else:
            lhs = getvarmult(self.lhs, var)
            rhs = getvarmult(self.rhs, var)
            s = lhs + rhs
            if is1x1(s):
                # Test to see if lhs and rhs cancel, without getting errors if
                # the equality test is forbidden.
                if iszero(s):
                    return 0
                else:
                    return s*ones(size(self), symb=True)
            else:
                return s

    def getdimmult(self, d):
        if d is None and not getdims(self):
            return self
        else:
            lhs = getdimmult(self.lhs, d)
            rhs = getdimmult(self.rhs, d)
            s = lhs + rhs
            return getdimmult(self.lhs, d) + getdimmult(self.rhs, d)

    def getvecmult(self, var):
        if var is None and not getoptvars(self):
            return vec(self)
        else:
            lhs = getvecmult(self.lhs, var)
            rhs = getvecmult(self.rhs, var)
            s = lhs + rhs
            if var is None and is1x1(s):
                # Test to see if lhs and rhs cancel, without getting errors if
                # the equality test is forbidden.
                if iszero(s):
                    return 0
                else:
                    return s*ones(rows(self)*cols(self), 1, symb=True)
            else:
                return s

    def epiorhypo(self):
        if isaffine(self):
            return (self, stdstruct())
        else:
            if isaffine(self.lhs):
                lhs = self.lhs
                sl = stdstruct()
            else:
                (lhs, sl) = self.lhs.epiorhypo()
            if isaffine(self.rhs):
                rhs = self.rhs
                sr = stdstruct()
            else:
                (rhs, sr) = self.rhs.epiorhypo()
            return (lhs + rhs, sl + sr)
    
    def etranspose(self):
        return etranspose(self.lhs) + etranspose(self.rhs)

    def expandtr(self):
        return expandtr(self.lhs) + expandtr(self.rhs)

    def getquadmult(self, var):
        return getquadmult(self.lhs, var) + getquadmult(self.rhs, var)

    def vectorize(self):
        # jem: need to expand this to include scalars?
        n = value(cols(self))
        return [x + y for (x, y) in zip(vectorize(self.lhs, n),
                                        vectorize(self.rhs, n))]

    def cvx(self):
        r = cvx(self.rhs)
        if r[0] == '-':
            return cvx(self.lhs) + ' - ' + cvx(-self.rhs)
        else:
            return cvx(self.lhs) + ' + ' + cvx(self.rhs)

    def _getsymm(self):
        return issymm(self.lhs) and issymm(self.rhs)
    symm = property(_getsymm)

    def nnz(self):
        if is1x1(self.lhs) or is1x1(self.rhs):
            # A scalar on either side will (we assume) cause complete fill-in.
            return rows(self)*cols(self)
        else:
            return nnz(self.lhs) + self.rhs

class multfunction(addormultfunction):
    def __init__(self, lhs, rhs):
        # First, if we have optvars on both sides we have a problem because
        # we would be violating the product rule. However, things like 3*(x+y)
        # are ok, so check for multiple optvars.
        #if getoptvars(lhs) and getoptvars(rhs): jem ignoring this for now.
        #    raise ProductError
        # First, check that we have appropriate sizes.
        rhrows = rows(rhs)
        lhcols = cols(lhs)

        if equivdims(lhcols, rhrows) or is1x1(lhs) or is1x1(rhs):
            # Valid multiplication, proceed.
            # Set the correct resulting size.
            if is1x1(lhs):
                self.rows = rhrows
                self.cols = cols(rhs)
            elif is1x1(rhs):
                self.rows = rows(lhs)
                self.cols = lhcols
            else:
                self.cols = cols(rhs)
                self.rows = rows(lhs)

            # Goal of next parts: make lhs the only scalar, if it exists.
            # If the rhs is a scalar, reverse lhs and rhs.
            if is1x1(rhs) and not is1x1(lhs):
                lhs, rhs = rhs, lhs

            # Put a strict scalar (i.e. float / int) on the lhs, regardless.
            if isinstance(rhs, (int, float)) and not isinstance(lhs, (int, float)):
                lhs, rhs = rhs, lhs

            # Next line is to avoid problems with ((3*A)*x)*4.
            if hasattr(lhs, 'lhs') and isinstance(lhs, multfunction):
                if is1x1(lhs.lhs):
                    lhs, rhs = lhs.lhs, lhs.rhs*rhs

            # Collect all scalars to the lhs.
            if hasattr(rhs, 'lhs') and isinstance(rhs, multfunction) and \
               is1x1(rhs.lhs):
                if is1x1(lhs):
                    lhs, rhs = lhs*rhs.lhs, rhs.rhs
                elif hasattr(lhs, 'lhs') and is1x1(lhs.lhs):
                    lhs, rhs = lhs.lhs * rhs.lhs, lhs.rhs * rhs.rhs
                else:
                    if is1x1(lhs):
                        lhs, rhs = lhs*rhs.lhs, rhs.rhs
                
            self.lhs = lhs
            self.rhs = rhs
            self.brackets = False

        else:
            raise DimError

    def epiorhypo(self):
        if isaffine(self):
            return (self, stdstruct())
        else:
            if isaffine(self.lhs):
                lhs = self.lhs
                sl = stdstruct()
            else:
                (lhs, sl) = self.lhs.epiorhypo()
            if isaffine(self.rhs):
                rhs = self.rhs
                sr = stdstruct()
            else:
                (rhs, sr) = self.rhs.epiorhypo()
            return (lhs*rhs, sl + sr)

    def __str__(self):
        if self.lhs is -1 or self.lhs is -1.0:
            return '-' + withbrackets(self.rhs)
        else:
            return withbrackets(self.lhs) + '*' + withbrackets(self.rhs)
        
    def _getconvex(self):
        if getoptvars(self.lhs) and getoptvars(self.rhs):
            return False

        # Otherwise, figure out which side has the variables.
        if getoptvars(self.rhs):
            constbit = self.lhs
            varbit = self.rhs
        elif getoptvars(self.lhs):
            constbit = self.rhs
            varbit = self.lhs
        else:
            return True

        # Look at the rules.
        if isaffine(varbit):
            return True
        elif ispos(constbit) and isconvex(varbit):
            return True
        elif isneg(constbit) and isconcave(varbit):
            return True

        return False
    convex = property(_getconvex)

    def _getconcave(self):
        if getoptvars(self.lhs) and getoptvars(self.rhs):
            return False

        # Otherwise, figure out which side has the variables.
        if getoptvars(self.rhs):
            constbit = self.lhs
            varbit = self.rhs
        elif getoptvars(self.lhs):
            constbit = self.rhs
            varbit = self.lhs
        else:
            return True

        # Look at the rules.
        if isaffine(varbit):
            return True
        elif ispos(constbit) and isconcave(varbit):
            return True
        elif isneg(constbit) and isconvex(varbit):
            return True

        return False
    concave = property(_getconcave)

    def _getincreasing(self):
        return (ispos(self.lhs) and isincreasing(self.rhs)) or \
           (isneg(self.lhs) and isdecreasing(self.rhs))
    increasing = property(_getincreasing)

    def _getdecreasing(self):
        return (ispos(self.lhs) and isdecreasing(self.rhs)) or \
           (isneg(self.lhs) and isincreasing(self.rhs))
    decreasing = property(_getdecreasing)

    def _getpos(self):
        return (ispos(self.lhs) and ispos(self.rhs)) or \
           (isneg(self.lhs) and isneg(self.rhs))
    pos = property(_getpos)

    def _getneg(self):
        return (ispos(self.lhs) and isneg(self.rhs)) or \
           (isneg(self.lhs) and ispos(self.rhs))
    neg = property(_getneg)

    def _getpsd(self):
        return (ispsd(self.lhs) and ispsd(self.rhs)) or \
           (isnsd(self.lhs) and isnsd(self.rhs)) or \
           (transpose(self.lhs) is self.rhs) or \
           (self.lhs is transpose(self.rhs))
    psd = property(_getpsd)

    def _getnsd(self):
        return (ispsd(self.lhs) and isnsd(self.rhs)) or \
           (isnsd(self.lhs) and ispsd(self.rhs))
    nsd = property(_getnsd)

    def _getvalue(self):
        return value(self.lhs) * value(self.rhs)
    value = property(_getvalue)

    def getvarmult(self, var):
        if var is None: # constant expression portion.
            if getoptvars(self.lhs):
                lhs = getvarmult(self.lhs, None)
            else:
                lhs = self.lhs

            if getoptvars(self.rhs):
                rhs = getvarmult(self.rhs, None)
            else:
                rhs = self.rhs

            if iszero(lhs) or iszero(rhs):
                return 0

            # Adjust for situations like u[0]*b, where u[0] should actually be
            # on the rhs.
            if is1x1(self.lhs):
                return rhs * lhs
            else:
                return lhs * rhs

        else:
            if var in getoptvars(self.lhs):
                lhs = getvarmult(self.lhs, var)
            else:
                lhs = self.lhs

            if var in getoptvars(self.rhs):
                rhs = getvarmult(self.rhs, var)
            else:
                rhs = self.rhs

            if iszero(lhs) or iszero(rhs):
                return 0
            else:
                # Adjust for situations like u[0]*b, where u[0] should actually be
                # on the rhs.
                if is1x1(self.lhs):
                    return rhs * lhs
                else:
                    return lhs * rhs

    def getdimmult(self, d):
        if d is None: # constant expression portion.
            if getdims(self.lhs):
                lhs = getdimmult(self.lhs, None)
            else:
                lhs = self.lhs

            if getdims(self.rhs):
                rhs = getdimmult(self.rhs, None)
            else:
                rhs = self.rhs

            if iszero(lhs) or iszero(rhs):
                return 0

            return lhs * rhs

        else:
            if d in getdims(self.lhs):
                lhs = getdimmult(self.lhs, d)
            else:
                lhs = self.lhs

            if d in getdims(self.rhs):
                rhs = getdimmult(self.rhs, d)
            else:
                rhs = self.rhs

            if iszero(lhs) or iszero(rhs):
                return 0
            else:
                return lhs * rhs

    def getvecmult(self, var):
        if var is None: # constant expression portion.
            lhs = getvecmult(self.lhs, None)
            rhs = getvecmult(self.rhs, None)

            if iszero(lhs) or iszero(rhs):
                return 0

            return lhs * rhs
        else:
            if var in getoptvars(self.lhs):
                lhs = getvecmult(self.lhs, var)
            else:
                if is1x1(self.lhs):
                    lhs = self.lhs
                else:
                    lhs = lhexp(self.lhs, size(self.rhs))

            if var in getoptvars(self.rhs):
                rhs = getvecmult(self.rhs, var)
            else:
                rhs = rhexp(self.rhs, size(self.lhs))

            if iszero(lhs) or iszero(rhs):
                return 0
            else:
                # Keep trobjs at the rhs by swapping the sides.
                # Also swap the sides if the variable appears on the left.
                if isinstance(lhs, trobj) or var in getoptvars(self.lhs):
                    return rhs * lhs
                else:
                    return lhs * rhs

    def etranspose(self):
        return etranspose(self.rhs)*etranspose(self.lhs)

    def expandtr(self):
        return expandtr(self.lhs)*expandtr(self.rhs)

    def getquadmult(self, var):
        if var not in getoptvars(self):
            return 0

        c = self

        lhs = 1
        rhs = 1
        while isinstance(c, multfunction):
            if var in getoptvars(c.lhs) and var not in getoptvars(c.rhs):
                rhs = c.rhs * rhs
                c = c.lhs
            elif var not in getoptvars(c.lhs) and var in getoptvars(c.rhs):
                lhs = lhs * c.lhs
                c = c.rhs
            elif var in getoptvars(c.lhs) and var in getoptvars(c.rhs):
                lhs, rhs = lhs*c.lhs, c.rhs*rhs

                lhm = getvarmult(etranspose(lhs), var)
                rhm = getvarmult(rhs, var)

                return etranspose(lhm)*rhm
            else:
                raise OptimizationError("shouldn't be here")

        return 0

    def vectorize(self):
        V = getoptvars(self.lhs)
        if len(V) > 1:
            raise OptimizationError('cannot vectorize: too many variables in'
                                    'expression')
        n = value(cols(self))
        lhs = self.lhs
        if V:
            v = V.pop()
            if not is1x1(v) or getoptvars(self.rhs):
                raise OptimizationError('cannot vectorize when non-1x1'
                                        'variable is on lhs')

        return [self.lhs*x for x in vectorize(self.rhs)]
    def cvx(self):
        if hasattr(self.lhs, 'brackets') and self.lhs.brackets:
            l = '(%s)' % cvx(self.lhs)
        else:
            l = cvx(self.lhs)

        if hasattr(self.rhs, 'brackets') and self.rhs.brackets:
            r = '(%s)' % cvx(self.rhs)
        else:
            r = cvx(self.rhs)
            
        return l + '*' + r

    def _getsymm(self):
        return is1x1(self.lhs) and issymm(self.rhs)
    symm = property(_getsymm)

    def nnz(self):
        if is1x1(self.lhs):
            return nnz(self.rhs)
        elif is1x1(self.rhs):
            return nnz(self.lhs)
        else:
            return rows(self)*cols(self)

    def nzentries(self):
        if is1x1(self.lhs):
            d = nzentries(self.rhs)
            for k in d.keys():
                d[k] = self.lhs*d[k]

            return d
        else:
            raise NotImplementedError

def multiply(lhs, rhs):
    # jemjemjem size checking should be in this function, not in
    # multfunction!!!

    # jem: speed optimized. Be gentle.

    if iszero(lhs):
        return 0
    elif iszero(rhs):
        return 0
    elif lhs is 1 or lhs is 1.0:
        return rhs
    elif rhs is 1 or rhs is 1.0:
        return lhs
    elif not is1x1(lhs) and isinstance(rhs, eyesymbol):
        return lhs # jemjem. need size checking here.
    elif not is1x1(rhs) and isinstance(lhs, eyesymbol):
        return rhs # jemjem. need size checking here.
    else:
        a = multfunction(lhs, rhs)
        # check that we don't have --x == 1*x.
        if is1x1(a.lhs) and (a.lhs is 1 or a.lhs is 1.0):
            return a.rhs
        else:
            return a
    
def addup(lhs, rhs):
    if iszero(lhs):
        return rhs
    elif iszero(rhs):
        return lhs
    else:
        return addfunction(lhs, rhs)

def JGen(i = 0):
    """Returns a generator of incrementing integers."""
    while 1:
        yield i
        i += 1

def tcount(init = JGen(1)):
    return init.next()

def nonamecount(init = JGen(1)):
    return init.next()

class norm2function(function, convex, positive):
    name = 'norm2'
    def __init__(self, arg):
        self.arg = arg
        self.rows = 1
        self.cols = 1

    def _getvalue(self):
        return sum(value(self.arg)**2)**0.5
    value = property(_getvalue)

    def _getincfn(obj):
        return ispos(obj.arg)
    incfn = property(_getincfn)

    def _getdecfn(obj):
        return isneg(obj.arg)
    decfn = property(_getdecfn)

    def cvx(self):
        return 'norm(%s, 2)' % str(self.arg)

    def epiorhypo(self):
        t = dummyvar(1, 1)
        t2 = dummyvar(size(self.arg))
        if isoptvar(self.arg):
            s = (norm2(self.arg) <= t).split()
        elif isaffine(self.arg):
            s = (self.arg == t2).split()
            s += (norm2(t2) <= t).split()
        else:
            if self.incfn:
                s = (self.arg <= t2).split()
            elif self.decfn:
                s = (self.arg >= t2).split()
            else:
                raise ConvexityError('invalid norm2 composition')
            s += (norm2(t2) <= t).split()
        return (t, s)

def norm2(obj):
    if isinstance(obj, (int, float, matrix, spmatrix)):
        return sum(obj**2)**0.5
    else:
        # jem. this (and possibly other situations) will be problematic with
        # params. need some kind of conditional comparison / put on stack
        # for later assertion.
        if cols(obj) is not 1:
            raise DimError('norm2 arg must be a column vector')
        else:
            return norm2function(obj)

class relation(lhsrhs):
    # split this according to sign [possibly w/ superclass]? then don't have to
    # use self.sign as an attribute.
    # should this have rows and columns???
    def __init__(self, lhs, rhs, sign):
        # If either is a scalar, no worries. If they're both non-1x1, they
        # had better be the same (at this point, anyway).
        if is1x1(lhs) or is1x1(rhs) or equivdims(rows(lhs), rows(rhs)) and \
           equivdims(cols(lhs), cols(rhs)):
            self.lhs = lhs
            self.rhs = rhs
            self.sign = sign
            if is1x1(lhs):
                self.rows = rows(rhs)
                self.cols = cols(rhs)
            else:
                self.rows = rows(lhs)
                self.cols = cols(lhs)
        else:
            raise DimError

    def _getvalue(self):
        if self.sign == '==':
            # could have more sophisticated checking in here.
            a = value(self.lhs - self.rhs)
            if not isinstance(a, (matrix, spmatrix)):
                a = matrix(a, tc='d')
            return cvxopt.blas.nrm2(a) <= (eps**2)*rows(a) + 1e-7
        else:
            # jem. deal with bug of no proper comparison for matrices.
            a = self.stdlhs()
            A = value(a)
            if isinstance(A, (int, float)):
                return A < eps
            for i in xrange(len(A)):
                if A[i] > eps:
                    return False
            return True
    value = property(_getvalue)

    def __repr__(self):
        if self.sign == '==':
            return "<%sx%s equality %s %s %s; optvars: %s>" % \
                (str(rows(self)), str(cols(self)), str(self.lhs), self.sign,
                str(self.rhs), stroptvars(self))
        else:
            return "<%sx%s inequality %s %s %s; optvars: %s>" % \
                (str(rows(self)), str(cols(self)), str(self.lhs), self.sign,
                str(self.rhs), stroptvars(self))

    def __str__(self):
        return "%s %s %s" % (str(self.lhs), self.sign, str(self.rhs))

    def cvx(self):
        return "%s %s %s" % (cvx(self.lhs), self.sign, cvx(self.rhs))

    def latex(self):
        s = self.sign
        if s == '<=':
            s = r'\leq'
        elif s == '>=':
            s = r'\geq'

        return "%s %s %s" % (latex(self.lhs), s, latex(self.rhs))

    def _getaffine(self):
        return isaffine(self.lhs - self.rhs)
    affine = property(_getaffine)

    def _getconvex(self):
        # This isn't really defined?
        if self.sign == '==':
            return isaffine(self.lhs) and isaffine(self.rhs)
        elif self.sign in ('<=', '<'):
            return isconvex(self.lhs - self.rhs)
        else:
            return isconvex(self.rhs - self.lhs)
    convex = property(_getconvex)

    def __nonzero__(self):
        raise OptimizationError("you should use `is', not `==' for comparing "
              "expressions/optvars.\nalso don't use bool(a >= 0), for example")

    def stdlhs(self):
        if self.sign == '<':
            return self.lhs - self.rhs
        elif self.sign == '<=':
            return self.lhs - self.rhs
        elif self.sign == '>':
            return self.rhs - self.lhs
        elif self.sign == '>=':
            return self.rhs - self.lhs
        else:
            return self.lhs - self.rhs

    def split(self):
        if isaffine(self):
            return stdstruct(lin=[self])
        elif isinstance(self.lhs, norm2function) and isoptvar(self.lhs.arg) and isoptvar(self.rhs):
            return stdstruct(socone=[self])
        else:
            (t, s) = self.stdlhs().epiorhypo()
            s.lin.append(t <= 0)
            return s

class problem(object):
    """problem([objective[, constr[, assertions]]]) -> convex optimization
    problem"""
    # jem. add affine property for problem.
    def __init__(self, objective=None, constr=None, assertions=None):
        self.objective = objective
        if constr is None:
            self.constr = []
        else:
            self.constr = constr
        if assertions is None:
            self.assertions = []
        else:
            self.assertions = assertions

    def __str__(self):
        if self.constr:
            s = "%s,\nsubject to:\n" % self.strobjective()
            for x in self.constr:
                s += '  ' + str(x) + '\n'
            s = s[:-1]
        elif self.objective is not None:
            s = self.strobjective()
        else:
            return 'empty problem.'

        s += '\n\noptimization variables:\n'
        for x in bylowerstr(getoptvars(self)):
            s += '  %s\n' % repr(x)
        s = s[:-1]

        if getparams(self):
            s += '\nparameters:\n'
            for x in bylowerstr(getparams(self)):
                s += '  %s\n' % repr(x)
            s = s[:-1]

        if getdims(self):
            s += '\ndimensions:\n'
            for x in bylowerstr(getdims(self)):
                s += '  %s\n' % repr(x)
            s = s[:-1]

        return s

    def __repr__(self):
        if len(self.constr) == 0:
            constr = 'no contraints'
        elif len(self.constr) == 1:
            constr = '1 constraint'
        else:
            constr = '%d constraints' % len(self.constr)

        if len(self.assertions) == 0:
            assertions = 'no assertions'
        elif len(self.assertions) == 1:
            assertions = '1 assertion'
        else:
            assertions = '%d assertions' % len(self.assertions)

        return "<problem with %s and %s; optvars: %s>" % \
                (constr, assertions, stroptvars(self))

    def gettype(self):
        if self.objective is None:
            return "feasibility"
        else:
            return self.objective.gettype()

    def cvx(self):
        s = ''
        s += '% CVX representation, generated by CVXMOD.\n'
        s += '% WARNING: not all atoms are supported in CVX.\n'
        s += '% WARNING: code may require modification.\n'

        if self.getparams():
            s += '\n% Parameter definitions.\n'

        for x in bylowerstr(self.getparams()):
            if x.value:
                s += x.matlab()
            else:
                pass

        if self.getdims():
            s += '\n% Dimension definitions.\n'

        for x in bylowerstr(self.getdims()):
            if x.value:
                s += x.matlab()
            else:
                pass

        s += "\ncvx_begin\n"
        for x in getoptvars(self):
            s += "    " + x.cvxdeclare() + '\n'
            if x.pos:
                s += "    " + str(x >= 0) + '\n'
            if x.neg:
                s += "    " + str(x <= 0) + '\n'

        if self.objective is not None:
            s += "    %s\n" % cvx(self.objective)
            if len(self.constr) > 0:
                s += "    subject to\n"

        for x in self.constr:
            if self.objective is None:
                # Don't indent as much.
                s += "    %s\n" % cvx(x)
            else:
                s += "        %s\n" % cvx(x)
        s += "cvx_end"
        return s

    def latex(self):
        s = ''
        s += '% Latex representation, generated by CVXMOD.\n'
        s += '% WARNING: markup may require modification.\n'

        if self.getparams():
            s += '\nLet \n'

        s += ', '.join([x.latexintroduce for x in self.getparams()]) + '.'

        s += '\nIn particular, let\n\\[\n'

        for x in self.getparams():
            if x.value:
                s += x.latexintroduce()
            else:
                pass

        s += '\nIn particular, let\n\\[\n'

        s += "\ncvx_begin\n"
        for x in self.getoptvars():
            s += "    " + x.latexdeclare() + '\n'
        if self.objective is not None:
            s += "    %s\n" % cvx(self.objective)
            if len(self.constr) > 0:
                s += "    subject to\n"

        for x in self.constr:
            if self.objective is None:
                # Don't indent.
                s += " %s\n" % cvx(x)
            else:
                s += "        %s\n" % cvx(x)
        s += "cvx_end\n"
        return s

    def _getvalue(self):
        if self.objective is None:
            return 0
        else:
            return value(self.objective)
    value = property(_getvalue)

    def getoptvars(self):
        return getoptvars(self.objective) | getoptvars(self.constr)

    def getassertions(self):
        return getassertions(self.objective) + getassertions(self.constr)

    def getstdforms(self):
        return getstdforms(self.objective) | getstdforms(self.constr)

    def getparams(self):
        s = getparams(self.objective)

        for x in self.constr:
            s |= getparams(x)

        for x in self.assertions:
            s |= getparams(x)

        return s

    def getdims(self):
        s = getdims(self.objective)

        for x in self.constr:
            s |= getdims(x)

        for x in self.assertions:
            s |= getdims(x)

        return s

    def strobjective(self):
        if self.objective is None:
            return "find %s" % stroptvars(self)
        else:
            s = str(self.objective)
            return str(self.objective)

    def _getconvex(self):
        if not isconvex(self.objective):
            return False
        else:
            for x in self.constr:
                if not isconvex(x):
                    return False
            else:
                return True
    convex = property(_getconvex)

    def classify(self):
        try:
            if self.validateassertions():
                print 'Assertion check: pass.'
            else:
                raise AssertionError
        except AssertionError:
            print 'Assertions: fail.'

        try:
            if self.validateparams():
                print 'Parameter check: pass.'
            else:
                raise ParamValueError
        except ParamValueError:
            print 'Parameter check: fail.'

        try:
            if self.validateconvexity():
                print 'Convexity check: pass.'
            else:
                raise ConvexityError
        except ConvexityError:
            print 'Convexity check: fail.'

        print '\nDetailed convexity check:'
        print '  ' + strconvex(self.objective) + ' objective: ' + str(self.objective)

        for x in self.constr:
            print '  ' + strconvex(x) + ' constraint: ' + str(x)

    def expand(self):
        """Expands the constraints and splits into linear/nonlinear."""
        # Force the objective to be a single variable. jem.
        constr = list(self.constr)
        if self.objective is None:
            m = 0
        else:
            m = self.objective.minarg()

        if isaffine(m):
            objv = m
            s = stdstruct()
        else:
            objv, s = m.epiorhypo()

        for c in constr:
            s += c.split()

        # Convert matrix variables into vector variables.
        (postconvert, objv) = s.pulloutmtx(objv)

        # Add two small extra term to the stdform constraints to ensure there is
        # always an A and a G matrix?
        t = dummyvar()
        s.lin += [t == 0, t >= -1]

        return (objv, s, postconvert)

    def printexpand(self):
        # for debugging/demo only.
        # jem: remove this at some point, or make it more like the proper print
        # of a function?
        (objv, s, postconvert) = self.expand()

        st = ''

        st += 'original problem:\n'
        for l in str(self).splitlines():
            st += l + '\n'

        st += '--------------------\n'
        st += 'transformed problem:\n'
        st += '--------------------\n'

        st += 'variables:\n'
        for x in getoptvars(s):
            st += '  ' + repr(x) + "\n"

        st += "minimize(%s)\n" % str(objv)
        if s.stdform:
            st += "with standard form constr:\n"
            for x in s.stdform:
                st += '  ' + str(x) + '\n'
        if s.lin:
            st += "with linear constr:\n"
            for x in s.lin:
                st += '  ' + str(x) + '\n'
        if s.socone:
            st += "with second-order cone constr:\n"
            for x in s.socone:
                st += '  ' + str(x) + '\n'
        if s.psdcone:
            st += "with psd cone constr:\n"
            for x in s.psdcone:
                st += '  ' + str(x) + '\n'
        if postconvert:
            st += "later, substitute back:\n"
            for x in postconvert.iteritems():
                st += '  ' + str(x[1]) + ' -> ' + str(x[0]) + '\n'

        print st[:-1]
    
    def validateassertions(self):
        for x in self.assertions:
            if not value(x):
                raise AssertionError('param assertion %s failed' % str(x))

        return True

    def validateuniqueness(self):
        d = {}
        for x in (getdims(self) | getparams(self) | getoptvars(self)):
            if x.name in d:
                d[x.name] += 1
            else:
                d[x.name] = 1

        for x in d:
            if d[x] > 1:
                # jem: turn this into an exception?
                print 'Warning: name collision detected: %s occurs %d times.' % d[x]

    def validateconvexity(self):
        if not isconvex(self.objective):
            raise ConvexityError('objective %s is non-convex' % \
                                        str(self.objective))
        else:
            for x in self.constr:
                if not isconvex(x):
                    raise ConvexityError('constraint %s is non-convex' \
                                                % str(x))

        # If we haven't run into an exception yet, we have a convex problem.
        return True

    def validateparams(self):
        error = False
        for x in getparams(self):
            if x.value is None:
                print 'no value assigned for %s' % str(x) # jem stderr?
                error = True
            elif size(x.value) != value(size(x)):
                print 'param %s has inconsistent value size' % str(x)
                error = True
            elif ispsd(x) and not ispsd(x.value):
                print 'value of psd param %s has negative eigenvalue' % str(x)
                error = True
            elif isnsd(x) and not isnsd(x.value):
                print 'value of nsd param %s has negative eigenvalue' % str(x)
                error = True

        if error:
            raise ParamValueError
        else:
            return True

    def validatebounds(self):
        error = False
        for x in getoptvars(self):
            if x.lower is None:
                print 'no lower bound for %s.' % str(x) # jem stderr?
                error = True
            elif not is1x1(x.lower) or rows(x.lower) is not rows(x) or \
                    cols(x.lower) is not cols(x):
                print '%s has inconsistent value size' % str(x)
                error = True

            if x.upper is None:
                print 'no upper bound for %s.' % str(x) # jem stderr?
                error = True
            elif not is1x1(x.upper) or rows(x.upper) is not rows(x) or \
                    cols(x.upper) is not cols(x):
                print '%s has inconsistent value size' % str(x)
                error = True

        if error:
            raise OptvarBoundError
        else:
            return True

    def strsymbsolve(self, stdform='cAbGh'):
        # Add line breaks after the semicolons to make it more readable.
        if stdform == 'cAbGh':
            ((c, A, b, G, h), x, d, optvars) = self.symbsolve(stdform)
            s = ''
            s += strsymbmatrix(c, 'ctilde') + '\n'
            s += strsymbmatrix(A, 'Atilde') + '\n'
            s += strsymbmatrix(b, 'btilde') + '\n'
            s += strsymbmatrix(G, 'Gtilde') + '\n'
            s += strsymbmatrix(h, 'htilde') + '\n'

        elif stdform == 'cAbp':
            ((c, A, b, S), x, d, optvars) = self.symbsolve(stdform)
            s = ''
            s += strsymbmatrix(c, 'ctilde') + '\n'
            s += strsymbmatrix(A, 'Atilde') + '\n'
            s += strsymbmatrix(b, 'btilde') + '\n'
        else:
            raise TypeError('no such stdform: try cAbGh or cAbp')

        s += 'optvars, in order: ' + joinlist(optvars)
        return s

    def symbsolve(self, stdform):
        self.validateassertions()
        #self.validateparams() # should be inside C code.
        self.validateconvexity()

        (objv, s, postconvert) = self.expand()

        optvars = bylowerstr(getoptvars([objv, s]))

        # simple LP.
        if not s.stdform and not s.socone and not s.psdcone:
            if stdform == 'cAbGh':
                (sf, optvars) = stdformlinsymb(objv, s.lin, optvars, stdform)
            elif stdform == 'cAbp':
                (sf, optvars) = stdformlinsymb(objv, s.lin, optvars, stdform)
            else:
                raise TypeError('no such stdform: try cAbGh or cAbp')
        else:
            raise NotImplementedError('can only handle LPs for symbsolve')

        z = None
        for y in optvars:
            z = cv(z, y)

        realoptvars = getoptvars(self)
        rsabove = 0
        d = {} # Format of d is (start, rows).
        for x in optvars:
            if x in realoptvars:
                d[x] = (rsabove, rows(x))
            rsabove += rows(x)

        return (sf, x, d, optvars) 

    def solve(self, quiet=False, kktsolver=None, full=True):
        try:
            oldval = cvxopt.solvers.options['show_progress']
        except KeyError:
            oldval = False
        cvxopt.solvers.options['show_progress'] = not quiet

        self.validateassertions()
        self.validateparams()
        self.validateuniqueness()
        self.validateconvexity()

        (objv, s, postconvert) = self.expand()
        optvars = bylowerstr(getoptvars([objv, s]))

        # simple LP.
        if not s.stdform and not s.socone and not s.psdcone:
            if not quiet:
                print 'using linear solver.'

            (c, A, b, G, h) = stdformlin(objv, s.lin, optvars, full=full)
            res = cvxopt.solvers.lp(c, G, h, A, b)

        # conic.
        elif not s.stdform:
            if not quiet:
                print 'using conic solver.'

            (c, A, b, G, h) = stdformlin(objv, s.lin, optvars, full=full)

            dims = {}
            if G:
                dims['l'] = rows(G)
            else:
                dims['l'] = 0

            (Gp, hp, qs) = stdformsoc(s.socone, optvars)
            G = concatvert(G, Gp)
            h = concatvert(h, hp)

            dims['q'] = qs

            if s.psdcone:
                # Drop the c off the front below.
                (Ap, bp, Gp, hp) = stdformlin(None, s.psdcone, optvars, full=full)[1:]
                G = concatvert(G, Gp, full=False)
                h = concatvert(h, hp)

            dims['s'] = []
            for ct in s.psdcone:
                dims['s'].append(int(rows(ct)**0.5))

            res = cvxopt.solvers.conelp(c, G, h, dims, A, b)

        # general nonlinear.
        else:
            if not quiet:
                print 'using nonlinear solver.'

            Flist = []
            # really stdform handlers. jem: this needs to be made clear.
            stdforms = self.getstdforms()
            for x in s.stdform:
                # try and match to a nonlinear function.
                d = x.stdlhs()
                for sf in stdforms:
                    try:
                        # Include extra domain constr.
                        (f, l) = sf(d)
                        Flist.append(f)
                        s.lin += l
                        break
                    except StdFormError:
                        continue
                else:
                    raise StdFormError

            # build up the matrix c in linear objective. should handle
            # the case where there is no objective as well.
            (c, A, b, G, h) = stdformlin(objv, s.lin, optvars, full=full)
            dims = {}
            if G is not None:
                dims['l'] = rows(G)
            else:
                dims['l'] = 0

            (Gp, hp, qs) = stdformsoc(s.socone, optvars)
            G = concatvert(G, Gp)
            h = concatvert(h, hp)
            dims['q'] = qs

            if s.psdcone:
                (Ap, bp, Gp, hp) = stdformlin(None, s.psdcone, optvars, full=full)[1:]
                G = concatvert(G, Gp)
                h = concatvert(h, hp)

            dims['s'] = []
            for ct in s.psdcone:
                dims['s'].append(int(rows(ct)**0.5))

            F = superF(Flist, optvars)

            # Protection for solver.
            if G is not None and iszero(rows(G)):
                G = None
                h = None
            # Protection for solver.
            if A is not None and iszero(rows(A)):
                A = None
                b = None

            res = cvxopt.solvers.cpl(c, F, G, h, dims, A, b, kktsolver=kktsolver)

        # Once we have solved the problem, go through and pull out the
        # optvars.
        if res['status'] == 'optimal':
            i = 0
            for v in optvars:
                v.value = res['x'][i:i+value(rows(v)),:]
                i += value(rows(v))

            # Go through and substitute the postconverts.
            for X in postconvert:
                X.value = matrix(value(postconvert[X]), size(X))

            if not quiet:
                print 'optimal value: %.4g.' % value(self)

        else:
            for v in optvars:
                v.value = None

            # Go through and substitute the postconverts.
            for X in postconvert:
                X.value = None

        cvxopt.solvers.options['show_progress'] = oldval

        return res['status']

    def aspartialspec(self, name, args):
        if not iterable(args):
            raise ValueError('args must be iterable')

        if not isconvex(self):
            raise ConvexityError('cannot create partial specification from '
                                 'non-convex problem')

        if self.objective is None:
            raise OptimizationError('cannot use feasibility problem as partial spec')
        elif isinstance(self.objective, minimizeobjective):
            convfn = True
            concfn = False
        else:
            convfn = False
            concfn = True

        # jem: will be copying parameters as well, is this ok?
        # jem: assuming in here that variables are uniquely named. I think
        # this is an ok assumption, but perhaps check it?

        (p, args) = copyprobandargs(self, args)
        ps = partialspec(name, p, args)
        ps.convfn = convfn
        ps.concfn = concfn
        return ps
    
    def replacevars(self, d):
        replacevars(self.objective, d)
        for x in self.constr:
            replacevars(x, d)

    def stdform(self):
        (objv, s, postconvert) = self.expand()
        optvars = bylowerstr(getoptvars([objv, s]))

        if s.stdform or s.socone or s.psdcone:
            raise NotImplementedError("stdform only works for LPs")

        # in the form (c, A, b, G, h),
        return stdformlin(objv, s.lin, optvars)

    def cgen(self, folder='cvxgen', skel='skeleton'):
        """Generate README and tostdform.c in folder."""
        # jem some of the below things will drop out later once we are more
        # comfortable with the code generation.
        self.validateassertions()
        self.validateconvexity()
        #self.validatebounds()
        #self.validatedims()

        (objv, s, postconvert) = self.expand()
        if s.stdform or s.socone or s.psdcone:
            raise NotImplementedError("code generation only works for LPs")

        # Delegate code generation to the separate code generation module.
        # Technically it belongs under problem, but split off some of the work.
        cg = codegen(self, folder, skel)
        print 'Input directory: %s.' % skel
        print 'Output directory: %s.' % folder
        print 'Generating tostdform.c.'
        cg.tostdform()
        print 'Generating data.h.'
        cg.data()
        print 'Generating testwithdata.c.'
        cg.testwithdata()
        print 'Generating README.'
        cg.readme()
        print 'done.'

    def ctostdform(self, folder='cvxgen'):
        # jem: validate some stuff first?
        cg = codegen(self, folder)
        cg.tostdform()

    def ctestwithdata(self, folder='cvxgen'):
        # jem: validate some stuff first?
        cg = codegen(self, folder)
        cg.testwithdata()

    def cdata(self, folder='cvxgen/'):
        """Generate compilable C code to instantiate data for this particular
        problem instance."""
        self.validateparams()
        #self.validatedims()

        cg = codegen(self, folder)
        cg.data()

class partialspec(object):
    def __init__(self, name, p, args):
        self.p = p
        self.args = args
        self.name = name
        # jem: later make this more sophisticated?
        self.convfn = False
        self.concfn = False

    def __str__(self):
        s = 'partial problem specification of %s, with argument list ' % self.name
        s += '(' + ','.join([str(x) for x in self.args]) + '),\n'
        s += 'and defining problem:\n'
        s += str(self.p)

        return s

    def __repr__(self):
        return "<%s function, defined by partial problem specification>" % self.name

    def __call__(self, *newargs):
        # Perhaps there are better ways of setting convfn and concfn?
        # jem: later upgrade this.
        psf = psfunc(self.name, self.p, self.args, newargs)
        psf.convfn = self.convfn
        psf.concfn = self.concfn
        return psf

class psfunc(function):
    def __init__(self, name, p, origargs, newargs):
        # p is the underlying problem prototype, so copy it and substitute the
        # variables in the appropriate way now.
        (p, origargs) = copyprobandargs(p, origargs)
        d = {}
        for (x, y) in zip(origargs, newargs):
            d[x] = y
        p.replacevars(d)

        self.args = newargs
        self.p = p
        self.rows = 1
        self.cols = 1
        self.name = name

    def epiorhypo(self):
        (p, args) = copyprobandargs(self.p, self.args)
        d = {}
        for (x, y) in zip(self.args, self.args):
            d[x] = y
        p.replacevars(d)

        t = dummyvar()
        constr = p.constr
        if isinstance(p.objective, minimizeobjective):
            constr.append(t >= p.objective.arg)
        else:
            constr.append(t <= p.objective.arg)

        s = stdstruct()
        for c in constr:
            s += c.split()

        return (t, s)

    def _getvalue(self):
        self.p.solve()
        return value(self.p)
    value = property(_getvalue)

def copyprobandargs(p, args):
    p = copy.deepcopy(p)
    d = {}
    # Build a dictionary of the variables in the new problem.
    for x in getoptvars(p):
        d[x.name] = x
    
    args = tuple([d[x.name] for x in list(args)])

    return (p, args)

class superF(object):
    # Flist is constr of the form constr <= 0.
    def __init__(self, Flist, optvars):
        self.Flist = tuple(Flist)
        self.optvars = optvars
        for v in self.optvars:
            if cols(v) != 1:
                raise NotImplementedError

    def __call__(self, x=None, z=None):
        # should allow for None objectives.
        if x is None and z is None:
            # first count the number of (scalar) functions.
            # also initialize to get a point in the domain.
            m = 0

            for c in self.Flist:
                m += c.rows * c.cols
                c.setindomain()

            # ensure any other optvars have an initial value set.
            for v in self.optvars:
                if v.value is None:
                    v.value = ones(size(v))

            # now gather values for returning.
            x0 = zm()
            for v in self.optvars:
                x0 = concatvert(x0, value(v))

            return (value(m), x0)
        elif z is None:
            i = 0
            for v in self.optvars:
                v.value = x[i:i+value(v.rows)]
                i += value(v.rows)

            for c in self.Flist:
                if not c.indomain():
                    return None

            f = zm()
            # go through and get values.
            for c in self.Flist:
                f = concatvert(f, c.value())

            Df = zm()
            # now go through and get gradients.
            for c in self.Flist:
                r = zm()
                for v in self.optvars:
                    if v in c.optvars:
                        r = concathoriz(r, c.jacobian(v))
                    else:
                        r = concathoriz(r, zeros(c.rows, v.rows))
                Df = concatvert(Df, r)

            return (f, Df)
        else:
            (f, Df) = self(x)
            H = zeros(rows(x), full=True)
            k = 0
            for c in self.Flist:
                i = 0
                for vfirst in self.optvars:
                    if vfirst in c.optvars:
                        j = 0
                        for vsecond in self.optvars:
                            if vsecond in c.optvars:
                                a = c.hessianz(vfirst, vsecond, z[k:k+value(c.rows)])
                                #H[i:i+value(vfirst.rows),j:j+value(vsecond.rows)] = \
                                #   H[i:i+value(vfirst.rows),j:j+value(vsecond.rows)] + a
                                H[i:i+value(vfirst.rows),j:j+value(vsecond.rows)] = a
                            j += value(vsecond.rows)
                    i += value(vfirst.rows)
                k += value(c.rows)

            return(f, Df, H)

def getoptvars(obj):
    """Returns a set of all optvars associated with an object."""
    try:
        return obj.getoptvars()
    except AttributeError:
        if iterable(obj):
            optvars = set()
            for x in obj:
                optvars.update(getoptvars(x))
            return optvars
        else:
            return set()

def getassertions(obj):
    """Returns a set of all assertions or implicit constr associated with
    an object."""
    try:
        return obj.getassertions()
    except AttributeError:
        if iterable(obj):
            assertions = []
            for x in obj:
                assertions += getassertions(x)
            return assertions
        else:
            return []

def getimplicit(obj):
    try:
        return obj.getimplicit()
    except AttributeError:
        if iterable(obj):
            implicit = []
            for x in obj:
                implicit.append(getimplicit(x))
            return implicit
        else:
            return []

def getstdforms(obj):
    """Returns a set of all standard forms associated with an object."""
    try:
        return obj.getstdforms()
    except (TypeError, AttributeError):
        if iterable(obj):
            stdforms = set()
            for x in obj:
                stdforms.update(getstdforms(x))
            return stdforms
        else:
            return set()

def getparams(obj):
    """Returns a set of all params associated with an object."""
    try:
        return obj.getparams()
    except AttributeError:
        return set()

def getdims(obj):
    """Returns a set of all dimensions associated with an object."""
    try:
        return obj.getdims()
    except AttributeError:
        return set()

def nnz(obj):
    """Returns the number of nonzero elements in an object."""
    if isinstance(obj, spmatrix):
        return obj.I.size[0]
    try:
        return obj.nnz()
    except AttributeError:
        if iszero(obj):
            return 0
        else:
            return rows(obj)*cols(obj)

def nzentries(obj):
    d = {}
    if iszero(obj):
        return d
    elif isinstance(obj, spmatrix):
        for i in obj.I:
            for j in obj.J:
                d[i,j] = obj[i,j]
        return d
    elif isinstance(obj, matrix):
        for i in range(rows(obj)):
            for j in range(cols(obj)):
                d[i,j] = obj[i,j]
        return d
    elif isinstance(obj, (int, float)):
        d[0,0] = obj
        return d
    else:
        try:
            return obj.nzentries()
        except AttributeError:
            raise NotImplementedError('could not find nonzero entries of %s' % str(obj))

def nnzpc(obj):
    if obj is None:
        return 0
    elif value(rows(obj)*cols(obj)) is 0:
        return 0
    else:
        return float(nnz(obj)) / value(rows(obj)*cols(obj))

def replacevars(self, d):
    # Try to replace variables. If it's not possible, just give up - it means
    # that there aren't any variables to replace in the below structure.
    try:
        return self.replacevars(d)
    except AttributeError:
        pass

def stroptvars(obj):
    """Returns a sorted, comma separated list of optvars associated with an
    object."""
    if not getoptvars(obj):
        return "None"

    return ", ".join([str(x) for x in bylowerstr(getoptvars(obj))])

def strparams(obj):
    """Returns a sorted, comma separated list of params associated with an
    object."""
    if iterable(obj):
        params = set()
        for x in obj:
            params.add(x)
    else:
        if not getparams(obj):
            return "None"
        else:
            params = getparams(obj)

    return ", ".join([str(x) for x in bylowerstr(getparams(obj))])

def rows(obj):
    try:
        return obj.rows
    except AttributeError:
        if isinstance(obj, (int, float)):
            return 1
        try:
            return obj.size[0]
        except AttributeError:
            raise AttributeError("cannot find rows of " + str(obj))

def cols(obj):
    try:
        return obj.cols
    except AttributeError:
        if isinstance(obj, (int, float)):
            return 1
        try:
            return obj.size[1]
        except AttributeError:
            raise AttributeError("cannot find cols of " + str(obj))

def size(obj, forcevv=False):
    if obj is None:
        return (None, None)

    if forcevv:
        return (value(rows(obj)), value(cols(obj)))
    else:
        return (rows(obj), cols(obj))

def strsize(obj, forcevv=False):
    s = size(obj, forcevv)
    return '%sx%s' % (str(s[0]), str(s[1]))

def Jwarn(msg):
    print "!!! WARNING: %s !!!" % msg

def withbrackets(obj):
    s = str(obj).strip().rstrip()
    if hasattr(obj, 'brackets') and obj.brackets:
        return '(%s)' % s
    else:
        return s

def is1x1(obj):
    # jem: this function has been sped up dramatically. Be gentle with it.
    if isinstance(obj, (int, float)):
        return True
    else:
        return rows(obj) is 1 and cols(obj) is 1

def isaffine(obj):
    # overloaded to handle lists as well.
    if isinstance(obj, (int, float, matrix, spmatrix)) or obj is None:
        return True

    if iterable(obj):
        for x in obj:
            if not isaffine(x):
                return False
        return True

    try:
        # jem experimental.
        return obj.affine
    except AttributeError:
        return isconvex(obj) and isconcave(obj)

def isconvex(obj):
    """Returns True if convexity can be proven."""
    if isinstance(obj, (int, float, matrix, spmatrix)) or obj is None:
        return True

    try:
        return obj.convex
    except AttributeError:
        if iterable(obj):
            for x in obj:
                if not isconvex(x):
                    return False
            return True
        else:
            pass

    return False

def isconcave(obj):
    """Returns True if concavity can be proven."""
    if isinstance(obj, (int, float, matrix, spmatrix)) or obj is None:
        return True

    try:
        return obj.concave
    except AttributeError:
        pass

    return False

def strconvex(obj):
    if isconvex(obj):
        return 'convex'
    else:
        return 'non-convex'

def isoptvar(obj):
    return isinstance(obj, symbol) and obj.role == OPTVAR

def iszero(obj):
    """True if obj is 0, 0.0, matrix(0.0) or zeros(...)."""

    # jem: speed optimized. Be gentle.

    if obj is 0:
        return True
    elif isinstance(obj, float) and obj == 0.0:
        return True
    elif isinstance(obj, constsymb):
        return obj.constval is 0 or obj.constval is 0.0
    elif isinstance(obj, (matrix, spmatrix)) and is1x1(obj):
        # jem: not entirely sure if this clause is necessary.
        return obj[0] is 0 or obj[0] is 0.0
    else:
        return False

def isnonzero(obj):
    return not iszero(obj)

def isparam(obj):
    return isinstance(obj, symbol) and obj.role == PARAM

def isdim(obj):
    return isinstance(obj, symbol) and obj.role == DIM

def isincreasing(obj):
    if isinstance(obj, (int, float, matrix, spmatrix)):
        return True

    try:
        return obj.increasing
    except AttributeError:
        pass

    return False

def isdecreasing(obj):
    if isinstance(obj, (int, float, matrix, spmatrix)):
        return True

    try:
        return obj.decreasing
    except AttributeError:
        pass

    return False

def ispos(obj):
    if isinstance(obj, (matrix, spmatrix)):
        for x in obj:
            if x < 0:
                return False
        else:
            return True
    elif isinstance(obj, (int, float)):
        return obj >= 0

    try:
        return obj.pos
    except AttributeError:
        pass

    return False

def isneg(obj):
    if isinstance(obj, (matrix, spmatrix)):
        for x in obj:
            if x > 0:
                return False
        else:
            return True
    elif isinstance(obj, (int, float)):
        return obj <= 0

    try:
        return obj.neg
    except AttributeError:
        pass

    return False

def _maxeignum(obj):
    """Numerical maximum eigenvalue calculation."""
    if isinstance(obj, (int, float)):
        return obj

    A = matrix(obj, tc='d')
    n = rows(obj)
    W = zeros(n, 1)
    W = matrix(W, tc='d')
    cvxopt.lapack.syevr(A, W, range='I', il=n, iu=n)
    return W[0]

def _mineignum(obj):
    """Numerical minimum eigenvalue calculation."""
    if isinstance(obj, (int, float)):
        return obj

    A = matrix(obj, tc='d')
    n = rows(obj)
    W = zeros(n, 1)
    W = matrix(W, tc='d')
    cvxopt.lapack.syevr(A, W, range='I', il=1, iu=1)
    return W[0]

def ispsd(obj):
    try:
        size(obj)
    except AttributeError:
        return False

    if isinstance(obj, (int, float, matrix, spmatrix)):
        if rows(obj) is not cols(obj):
            return False

        if _mineignum(obj) >= 0:
            return True
        else:
            return False

    try:
        return obj.psd
    except AttributeError:
        pass # handle error below, but not as an AttributeError.

    return False

def isnsd(obj):
    try:
        size(obj)
    except AttributeError:
        return False

    if isinstance(obj, (int, float, matrix, spmatrix)):
        if rows(obj) is not cols(obj):
            return False

        if _maxeignum(obj) <= 0:
            return True
        else:
            return False

    try:
        return obj.nsd
    except AttributeError:
        pass # handle error below, but not as an AttributeError.

    return False

def issparse(obj):
    return isinstance(obj, spmatrix)

def classify(obj):
    try:
        obj.classify()
    except AttributeError:
        attributes = []
        varattributes = [] # attributes that are `in x', say.
        if ispos(obj) and isneg(obj):
            attributes.append('zero')
        elif ispos(obj):
            attributes.append('positive')
        elif isneg(obj):
            attributes.append('negative')

        # jem. think about this one.
        if 'zero' not in attributes:
            if ispsd(obj):
                attributes.append('PSD')
            if isnsd(obj):
                attributes.append('NSD')

        if isaffine(obj): # includes simultaneous convex and concave.
            varattributes.append('affine')
        elif isconvex(obj):
            varattributes.append('convex')
        elif isconcave(obj):
            varattributes.append('concave')

        if isincreasing(obj) and isdecreasing(obj):
            constant = True
        else:
            constant = False
            if isincreasing(obj):
                varattributes.append('increasing')
            elif isdecreasing(obj):
                varattributes.append('decreasing')

        if not attributes and not varattributes and not constant:
            print 'nothing special, as far as I know.'
            return

        if attributes:
            s = joinlist(attributes) + '; '
        else:
            s = ''

        # jem. trying not to mistakenly include functions on the next line.
        if constant:
            print s + 'constant.'
            return
        elif len(varattributes) == 0:
            print s[:-2] + '.'
            return
        else:
            s += joinlist(varattributes)

        if len(getoptvars(obj)) == 0:
            print s + '.'
            return
        else:
            print s + ' in ' + stroptvars(obj) + '.'
            return

def value(obj):
    """Attempt to return an actual numeric value using .value attributes."""
    if obj is None:
        return None
    elif isinstance(obj, (int, float, matrix, spmatrix, bool)):
        return obj
    elif isinstance(obj, (list, tuple)):
        y = []
        for x in obj:
            y.append(value(x))
        return tuple(y)
    else:
        v = obj.value
        if v is None:
            if getoptvars(obj):
                raise OptvarValueError
            elif getparams(obj):
                raise ParamValueError
            else:
                # jem revise.
                raise OptimizationError('null value of unknown thing')
        
        # return matrix entry directly if a 1x1 matrix.
        if isinstance(v, (matrix, spmatrix)) and is1x1(v):
            return v[0]
        else:
            return v

# For use inside functions with value already defined.
value__ = value
def printval(obj, val=None):
    if val is not None:
        s = obj
        v = value(val)
    else:
        s = str(obj)
        v = value(obj)

    if isinstance(v, float):
        # jem: replace this with something better?
        v = '%.4f' % v

    print s + ' ='
    s = str(v)
    for l in s.splitlines():
        print '  ' + l

def vectorize(obj, n=None):
    if isinstance(obj, (int, float, matrix, spmatrix)):
        return [obj]*n
    else:
        return obj.vectorize()

def eye(size, symb=False):
    """Creates an identity matrix. Expand this later to be more general."""
    if symb:
        if equiv(size, 1):
            return 1
        else:
            return eyesymbol(size)
    else:
        return speye(size)
    
def speye(size):
    """Creates a sparse identity matrix. Expand this later to be more general."""
    return cvxopt.base.spmatrix(1, xrange(size), xrange(size))

def zeros(rows, cols=None, symb=False, full=False):
    if iterable(rows):
        if len(rows) == 2:
            cols = rows[1]
            rows = rows[0]
        else:
            raise TypeError('invalid dimension tuple')

    if cols is None:
        cols = rows
    
    if symb:
        return constsymb(rows, cols, 0)
    else:
        if full:
            return matrix(0.0, (rows, cols))
        else:
            return spmatrix([], [], [], (rows, cols))

def ones(rows, cols=None, symb=False):
    # should the default return a vector rather than a square matrix?
    # inconsistent with zeros, but possibly more useful.
    # we might want a special display method thing.
    if iterable(rows):
        if len(rows) == 2:
            cols = rows[1]
            rows = rows[0]
        else:
            raise TypeError('invalid dimension tuple')

    if cols is None:
        cols = rows

    if symb:
        if rows is 1 and cols is 1:
            return 1
        else:
            return constsymb(rows, cols, 1)
    else:
        return matrix(1.0, (rows, cols))

def getvarmult(obj, var):
    # error checking to make sure that we don't try and use a parameter etc?
    # jem: combine this and getvecmult eventually?
    # First expand out any transposes.
    obj = expandtr(obj)
    if var is not None and var not in getoptvars(obj):
        return 0

    try:
        return obj.getvarmult(var)
    except AttributeError:
        # this should return 7 or a matrix, for example, if there is no value.
        if var is None:
            return obj
        else:
            return 0

def getdimmult(obj, dim):
    # error checking to make sure that we don't try and use a parameter etc?
    # jem: combine this and getvecmult eventually?
    # No need to expand transposes for dimensions.

    if dim is not None and dim not in getdims(obj):
        return 0

    try:
        return obj.getdimmult(dim)
    except AttributeError:
        # this should return 7 or a matrix, for example, if there is no value.
        if dim is None:
            return obj
        else:
            return 0

def getvecmult(obj, var):
    # First expand out any transposes.
    obj = expandtr(obj)
    if var is not None and var not in getoptvars(obj):
        return 0

    try:
        a = obj.getvecmult(var)
        if isinstance(a, (matrix, spmatrix)):
            b = matrix(a, tc='d')
            if cvxopt.blas.nrm2(b) <= (eps**2)*rows(b) + 1e-7:
                # saturate certain vectors to zero.
                return 0
            else:
                return a
        else:
            return a
    except AttributeError:
        if var is None:
            return vec(obj)
        else:
            return 0

class trobj(symbol):
    """Matrix representing change from column-major representation of matrix to
    column-major representation of its transpose."""
    pos = True
    def __init__(self, size):
        self.rows = size[0]*size[1]
        self.cols = size[0]*size[1]
        self.varsize = size

    def __repr__(self):
        return "<%sx%s transposer of %sx%s symbol>" % (withbrackets(self.rows),
           withbrackets(self.cols), withbrackets(self.varsize[0]),
           withbrackets(self.varsize[1]))

    def __str__(self):
        return 'transposer'

    def _getvalue(self):
        # jem: make this cache.
        # square matrix.
        k = value(self.rows)
        m = value(self.varsize[0])
        n = value(self.varsize[1])

        # Deal with trivial transposition.
        if k is 1 or n is 1 or m is 1:
            return eye(k)

        T = zeros(k)

        for i in range(n):
            T[range((m*k+1)*i, m*k*(i+1), (m+1)*n)] = 1

        return T
    value = property(_getvalue)
        
class lhexp(function, affine, increasing):
    # special holding class for left-hand expansion.
    # vec(A*X) == lhexp(A)*vec(X).
    name = 'lhexp'
    def __init__(self, arg, varsize):
        self.arg = arg
        # not quite sure what rows and columns should be.
        if varsize[0] is 1 and varsize[1] is 1:
            self.rows = rows(arg)*cols(arg)
        else:
            self.rows = value(rows(arg))*varsize[1]
        self.cols = varsize[0]*varsize[1]
        self.varsize = varsize

    def _getvalue(self):
        L = value(self.arg)
        if self.varsize[0] is 1 and self.varsize[1] is 1:
            return L[:]
        elif cols(L) == 1:
            return L
        else:
            #    L    *   var
            # (k x m) * (m x n) -> input (m*n) to output (k*n).
            k = rows(L)
            m = self.varsize[0]
            n = self.varsize[1]

            A = zeros(k*n, m*n)
            for i in range(n):
                A[i*k:i*k+k,i*m:i*m+m] = value(L)

            return A
    value = property(_getvalue)

class rhexp(function, affine, increasing):
    # special holding class for left-hand expansion.
    # vec(X*B) == rhexp(B)*vec(X).
    name = 'rhexp'
    def __init__(self, arg, varsize):
        self.arg = arg
        # not quite sure what rows and columns should be.
        if varsize[0] is 1 and varsize[1] is 1:
            self.rows = rows(arg)*cols(arg)
        else:
            self.rows = varsize[0]*cols(arg)
        self.cols = varsize[0]*varsize[1]
        self.varsize = varsize

    def _getvalue(self):
        R = value(self.arg)
        if self.varsize[0] is 1 and self.varsize[1] is 1:
            return R[:]
        else:
            #   var   *    R
            # (m x n) * (n x k) -> input (m*n) to output (m*k).
            k = cols(R)
            m = self.varsize[0]
            n = self.varsize[1]

            A = zeros(m*k, m*n)
            for i in range(n):
                for j in range(k):
                    A[i*m*k*m+j*m:(i+1)*m*k*m+j*m:m*k+1] = R[i,j]

            return A
    value = property(_getvalue)

def getquadmult(obj, var):
    try:
        return obj.getquadmult(var)
    except AttributeError:
        return 0

def concathoriz(lhs, rhs, full=True):
    if lhs is None or iszero(rows(lhs)):
        if rhs is None or iszero(rows(rhs)):
            return zm()
        else:
            return rhs
    elif rhs is None or iszero(rows(rhs)):
        return lhs

    if not isinstance(lhs, (matrix, spmatrix, int, float)) or \
       not isinstance(rhs, (matrix, spmatrix, int, float)):
        raise TypeError('can only concatenate matrices')

    if full:
        return matrix([[lhs], [rhs]])
    else:
        return sparse([[lhs], [rhs]])

def concatvert(lhs, rhs, full=True):
    if lhs is None or iszero(rows(lhs)):
        if rhs is None or iszero(rows(rhs)):
            return zm()
        else:
            return rhs
    elif rhs is None or iszero(rows(rhs)):
        return lhs


    if not isinstance(lhs, (matrix, spmatrix, int, float)) or \
       not isinstance(rhs, (matrix, spmatrix, int, float)):
        raise TypeError('can only concatenate matrices')

    if full:
        return matrix([lhs, rhs])
    else:
        return sparse([lhs, rhs])

def ensureint(obj):
    if isinstance(obj, int):
        return True
    else:
        return _ensureint(obj)

class _ensureint(object):
    def __init__(self, arg):
        self.arg = arg

    def _getvalue(self):
        return isinstance(value(obj), int)
    value = property(_getvalue)

def zm(cols=0):
    return matrix(0, size=(0,cols), tc='d')

def dummyvar(rows=1, cols=None, symm=False):
    if iterable(rows):
        if len(rows) == 2:
            cols = rows[1]
            rows = rows[0]
        else:
            raise TypeError('invalid dimension tuple')
    elif cols is None:
        cols = 1

    return optvar('t%03d' % tcount(), rows, cols, symm=symm)

class diagfunction(function, affine, increasing):
    name = 'diag'
    def __init__(self, arg):
        self.arg = arg
        self.rows = rows(arg)
        self.cols = 1

    def _getvalue(self):
        return diag(value(self.arg))
    value = property(_getvalue)

    def getvecmult(self, var):
        diags = [(x,x) for x in range(value(rows(self.arg)))]
        return getvecmult(self.arg[diags], var)

class todiagfunction(function, affine, increasing):
    name = 'diag'
    def __init__(self, arg):
        self.arg = arg
        self.rows = rows(arg)
        self.cols = rows(arg)

    def _getvalue(self):
        return diag(value(self.arg))
    value = property(_getvalue)

    def getvarmult(self, var):
        return getvarmult(todiag(rows(self.arg))*self.arg, var)

    def getvecmult(self, var):
        return getvecmult(todiag(rows(self.arg))*self.arg, var)

def diag(obj):
    # not the most efficient way of creating a diagonal matrix.
    # should probably use sparse at least.
    # overwrites diag from numpy.
    # jem. needs overhaul.
    if getoptvars(obj) or getparams(obj):
        if is1x1(obj):
            return obj
        elif rows(obj) is cols(obj):
            return diagfunction(obj)
        else:
            return todiagfunction(obj)

    x = value(obj)

    try:
        s = size(x)
    except AttributeError:
        s = (len(x), 1)

    if s[0] is 1 and s[1] is 1:
        return x
    elif 1 in s:
        X = zeros(max(size(x)))
        for i in xrange(len(x)):
            X[i,i] = x[i]
        return X
    elif s[0] is s[1]:
        return x[range(0,s[0]*s[1],s[0]+1)]

class tracefunction(function, affine, increasing):
    name = 'trace'
    def __init__(self, arg):
        self.arg = arg
        self.rows = 1
        self.cols = 1

    def _getvalue(self):
        return trace(value(self.arg))
    value = property(_getvalue)

    def getvecmult(self, var):
        m = value(rows(self.arg))
        e = zeros(1, m*m)
        for i in range(value(rows(self.arg))):
            e[i+i*m] = 1
        return e*getvecmult(self.arg, var)

def trace(obj):
    if isinstance(obj, (int, float)):
        return obj
    elif isinstance(obj, (matrix, spmatrix)):
        if rows(obj) is not cols(obj):
            raise DimError("cannot find trace of non-square matrix")
        m = value(rows(obj))
        e = zeros(1, m*m)
        for i in range(value(rows(obj))):
            e[i+i*m] = 1
        return float((e*vec(obj))[0])
    else:
        return tracefunction(obj)

def stdformlin(objv, lin, optvars, withbounds=False, full=True):
    # my personal least favourite function in the world. jem.
    A = zm()
    b = zm() 
    G = zm()
    h = zm()
    for d in lin:
        s = d.stdlhs()
        r = zm()
        if d.sign == '==':
            for v in optvars:
                a = value(getvarmult(s, v))
                if iszero(a):
                    a = zeros(rows(s), rows(v))
                r = concathoriz(r, a)
            A = concatvert(A, r, full)
            bb = -value(getvarmult(s, None))
            if is1x1(bb):
                bb = bb*ones(size(s))
            b = concatvert(b, bb)
        else:
            for v in optvars:
                a = value(getvarmult(s, v))
                if iszero(a):
                    a = zeros(rows(s), rows(v))
                r = concathoriz(r, a, full)
            G = concatvert(G, r, full)
            bb = -value(getvarmult(s, None))
            if is1x1(bb):
                bb = bb*ones(size(s))
            h = concatvert(h, bb)

    # Remove any zero-row matrices for cvxopt's benefit.
    if rows(A) == 0:
        A = None
        b = None
    if rows(G) == 0:
        G = None
        h = None

    if objv is None and A is not None:
        c = zeros(cols(A), 1)
    else:
        c = zm()
        for v in optvars:
            a = value(tp(getvarmult(objv, v)))
            if iszero(a):
                a = zeros(rows(v), 1)
            c = concatvert(c, a)

    BIGM = 200
    if withbounds:
        l = zm()
        u = zm()
        for x in optvars:
            if x.lower is not None:
                if is1x1(x.lower):
                    l = concatvert(l, x.lower*ones(size(x)))
                else:
                    l = concatvert(l, x.lower)
            else:
                l = concatvert(l, -BIGM*ones(size(x)))

            if x.upper is not None:
                if is1x1(x.upper):
                    u = concatvert(u, x.upper*ones(size(x)))
                else:
                    u = concatvert(u, x.upper)
            else:
                u = concatvert(u, BIGM*ones(size(x)))

        return ((c, A, b, G, h), (l, u))
    else:
        return (c, A, b, G, h)

def stdformsoc(constr, optvars):
    # not equipped to handle more complicated constr.
    # cannot, for example, handle even norm2(x) <= 5, or norm2(3*x) <= t. must
    # be strictly of the form norm2(x) <= t.
    G = zm()
    qs = []
    for c in constr:
        # assume exact form norm2(x) <= t.
        r = zm()
        qs.append(rows(c.lhs.arg) + 1)
        for v in optvars:
            if v is c.rhs:
                a = -1.0
            else:
                a = zeros(1, rows(v))
            r = concathoriz(r, a)
        G = concatvert(G, r)
        r = zm()
        for v in optvars:
            if v is c.lhs.arg:
                a = eye(rows(v))
            else:
                a = zeros(rows(c.lhs.arg), rows(v))
            r = concathoriz(r, a)
        G = concatvert(G, r)
    h = zeros(rows(G), 1)

    return (G, h, qs)

class unsymm(symbol):
    """Matrix representing change from lower-triangular representation of
    symmetric matrix to full matrix."""
    # jem: is this overkill?
    pos = True
    def __init__(self, m):
        self.rows = m*m
        self.cols = int(m*(m+1)/2)
        self.m = m

    def __repr__(self):
        return "<%sx%s unsymm of %sx%s symbol>" % (withbrackets(self.rows),
           withbrackets(self.cols), withbrackets(m), withbrackets(m))

    def __str__(self):
        return 'unsymm'

    def _getvalue(self):
        m = self.m
        A = zeros(self.rows, self.cols)
        for i in range(m):
            for j in range(m):
                # Access lower triangular entries only.
                if i >= j:
                    (i2, j2) = (i, j)
                else:
                    (i2, j2) = (j, i)

                # int() is to enforce data type only, in conjunction with importing
                # __div__ from the future.
                A[i+j*m, i2+j2*m-int(j2*(j2+1)/2)] = 1
        return A
    value = property(_getvalue)

class todiag(symbol):
    """Matrix representing change from diagonals as vector to diagonal
    matrix."""
    # jem: is this overkill?
    pos = True
    def __init__(self, m):
        self.rows = m*m
        self.cols = m
        self.m = m

    def __repr__(self):
        return "<%sx%s todiag of %sx%s symbol>" % (withbrackets(self.rows),
           withbrackets(self.cols), withbrackets(self.m), withbrackets(self.m))

    def __str__(self):
        return 'todiag'

    def _getvalue(self):
        m = self.m
        A = zeros(self.rows, self.cols)
        for i in range(m):
            A[i*(m+1),i] = 1
        return A
    value = property(_getvalue)

def equiv(obj1, obj2):
    """Tests equivalence of two objects.

    Avoids the broken __nonzero__ test that would otherwise test equivalence
    with (e.g.) m == n. Use this anytime you want to test whether two objects
    are the same and one of the objects is a CVXMOD object with meaning for ==.
    """

    # jem: super speed optimized. Be gentle! Note that some functionality has
    # been removed because it was never used and slowed things down. Some
    # things like equiv(1, 1.0) will no longer return True.
    # This was a huge hotspot.

    if obj1 is obj2:
        return True

    # jem: explain exactly what equiv does.
    if iterable(obj1) and len(obj1) is 2 and iterable(obj2) and len(obj2) is 2:
        return equiv(obj1[0], obj2[0]) and equiv(obj1[1], obj2[1])

    return False

def cvx(obj):
    if isinstance(obj, (matrix, spmatrix)):
        s = '['
        for i in range(rows(obj)):
            for j in range(cols(obj)):
                s += ' %.4g' % obj[i,j]
            s += ';'
        return s + ']'

    try:
        return obj.cvx()
    except AttributeError:
        return str(obj)

def latex(obj):
    try:
        return obj.latex()
    except AttributeError:
        return str(obj)

class vecfunction(function, affine, increasing):
    """The vectorized, column-major, form of its argument."""
    # Should implement using a set of linear inequalities.
    name ='vec'
    def __init__(self, arg):
        self.arg = arg
        self.rows = rows(arg)*cols(arg)
        self.cols = 1

    def epiorhypo(self):
        t = dummyvar(size(self))
        s = stdstruct()
        for j in range(cols(self.arg)):
            # jem later change this to self.arg[:,j], once it is supported.
            a = zeros(1, rows(self))
            a[j*rows(self.arg):(j+1)*rows(self.arg)] = 1
            # sign is not necessarily equals: depends on convexity.
            if isaffine(self):
                s += (a*t == self.arg*unitvec(j+1, cols(self.arg))).split()
            elif isconvex(self):
                s += (a*t >= self.arg*unitvec(j+1, cols(self.arg))).split()
            elif isconcave(self):
                s += (a*t <= self.arg*unitvec(j+1, cols(self.arg))).split()
        return (t, s)

    def _getvalue(self):
        return vec(value(self.arg))
    value = property(_getvalue)

    def getvecmult(self, var):
        return getvecmult(self.arg, var)

def vec(obj):
    if isinstance(obj, (int, float)) or cols(obj) is 1:
        return obj
    elif isinstance(obj, (matrix, spmatrix)):
        return matrix(obj[:])
    else:
        return vecfunction(obj)

class unvecfunction(function, affine, increasing):
    """The unvectorized, column-major, form of its argument."""
    # Should implement using a set of linear inequalities.
    name ='unvec'
    def __init__(self, arg, rs, cs):
        self.arg = arg
        self.rows = rs
        self.cols = cs

    def _getvalue(self):
        return vec(value(self.arg))
    value = property(_getvalue)

def unvec(obj, rs=None, cs=None):
    if iterable(rs):
        if len(rs) == 2:
            cs = rs[1]
            rs = rs[0]
        else:
            raise TypeError('invalid dimension tuple')

    if isinstance(obj, (int, float)) or cols(obj) is not 1:
        return obj
    elif isinstance(obj, (matrix, spmatrix)):
        if size is None:
            raise TypeError('unvec needs a size argument if reshaping a matrix')
        return matrix(obj[:])
    elif isinstance(obj, vecfunction):
        return obj.arg
    else:
        return unvecfunction(obj, rs, cs)

class stdstruct(object):
    """Standard structure for holding parts of a problem in standard form."""
    # Examples:
    # - square(x).split() should return (epivar, stdstruct).
    # - (x <= 3).split() should return stdstruct.
    # stdstruct() | stdstruct() should combine the two.
    def __init__(self, stdform=None, lin=None, socone=None, psdcone=None):
        if stdform is None:
            self.stdform = []
        else:
            self.stdform = stdform

        if lin is None:
            self.lin = []
        else:
            self.lin = lin

        if socone is None:
            self.socone = []
        else:
            self.socone = socone

        if psdcone is None:
            self.psdcone = []
        else:
            self.psdcone = psdcone

    def __add__(self, other):
        if isinstance(other, stdstruct):
            s = stdstruct()
            s.stdform = self.stdform + other.stdform
            s.lin = self.lin + other.lin
            s.socone = self.socone + other.socone
            s.psdcone = self.psdcone + other.psdcone
            return s
        else:
            raise TypeError('can only add stdstructs together')

    def __iadd__(self, other):
        if isinstance(other, stdstruct):
            self.stdform += other.stdform
            self.lin += other.lin
            self.socone += other.socone
            self.psdcone += other.psdcone

            return self
        else:
            raise TypeError('can only add stdstructs together')

    def __repr__(self):
        return '<stdstruct(\n  %s, \n  %s, \n  %s, \n  %s)>' % (str(self.stdform),
                                                        str(self.lin),
                                                        str(self.socone),
                                                        str(self.psdcone))

    def getoptvars(self):
        return getoptvars((self.stdform, self.lin, self.psdcone))

    def pulloutmtx(self, objv):
        """Replace matrix variables with vector variables and relevant
        multipliers. Do the same for an associated (objective) expression objv,
        if necessary."""

        allvars = getoptvars(self) | getoptvars(objv)

        # Mark variables as positive or negative, if necessary.
        for x in allvars:
            if x.pos:
                self.lin.append(x >= 0)
            if x.neg:
                self.lin.append(x <= 0)

        # First find the problem variables.
        mvars = set([X for X in allvars if value(cols(X)) > 1])
        d = {}
        dp = []

        # Build the dictionary.
        for X in mvars:
            d[X] = X.getvecvar()

        def replinexpr(c):
            a = 0
            # Add the vectorized matrices for the replacement relation.
            for X in (mvars & getoptvars(c)):
                a += getvecmult(c, X)*d[X]

            a += getvecmult(c, None)

            # Add in the non-matrix variables.
            for x in getoptvars(c) - mvars:
                a += getvecmult(c, x)*x

            return a

        for i in range(len(self.lin)):
            l = self.lin[i]
            if mvars & getoptvars(l):
                self.lin[i] = relation(replinexpr(l.lhs), replinexpr(l.rhs), l.sign)

        if mvars & getoptvars(objv):
            objv = replinexpr(objv)

        # Figure out which variables need to be marked as psd (nsd), and do so.
        for X in mvars:
            if X.psd:
                if X not in d:
                    d[X] = X.getvecvar()
                dp.append(-d[X] <= 0)
            if X.nsd:
                if X not in d:
                    d[X] = X.getvecvar()
                dp.append(d[X] <= 0)

        # Add psd expressions into the mix.
        for ct in self.psdcone:
            c = ct.stdlhs()
            expr = 0

            for X in (mvars & getoptvars(c)):
                if X not in d:
                    d[X] = X.getvecvar()

                expr += getvecmult(c, X)*d[X]

            expr += getvecmult(c, None)

            # Add in the non-matrix variables.
            for x in getoptvars(c) - mvars:
                expr += getvecmult(c, x)*x

            dp.append(expr <= 0)

        # Replace psd expressions with these new ones.
        self.psdcone = dp

        # Deal with elementwise standard forms.
        # jem: somewhat experimental way of handling matrix-valued elementwise
        # functions using existing support for vector valued functions.
        cn = []
        for c in list(self.stdform):
            if hasattr(c.lhs, 'elementwise') and c.lhs.elementwise:
                try:
                    X = c.lhs.arg
                except AttributeError:
                    # Just ignore anything that has .args, for example, for
                    # now.
                    cn.append(c)
                    continue

                if value(cols(X)) > 1:
                    cn.append(relation(c.lhs.func(d[X]), d[c.rhs], c.sign))
                else:
                    cn.append(c)
            else:
                cn.append(c)

        self.stdform = cn

        return (d, objv)

    def _getvalue(self):
        for c in self.stdform + self.lin + self.socone + self.psdcone:
            if not value(c):
                return False
        return True
    value = property(_getvalue)

# Bizarre post-imports. Mainly to stop this file being quite so big.
import errors
from errors import *
__all__ += errors.__all__
import symbolic
from symbolic import *
import simpleatoms
from simpleatoms import *
import setsbase
from setsbase import *
import codegen
from codegen import codegen
import util
from util import *
__all__ += simpleatoms.__all__
__all__ += setsbase.__all__
__all__ += symbolic.__all__
