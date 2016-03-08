"""
General utility functions that don't belong in cvxmod.base.

"""

# Copyright (C) 2006-2008 Jacob Mattingley and Stephen Boyd.
#
# Portions of this file were contributed by Timothy Hunter.
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

import cvxmod
from cvxmod.base import *

import cvxopt
from cvxopt import lapack
from cvxopt import cholmod

from math import sqrt

__all__ = ["randn", "rand", "randseed", "linspace", "joinlist", "iterable",
           "bylowerstr", "slicetoindices", "sqrtm", "svd", "eig",
           "leastsquares", "leastnorm", "cholsolve", "spy", "cholnum"]

def randn(rows=1, cols=None, mean=0, std=1):
    if iterable(rows):
        if len(rows) == 2:
            cols = rows[1]
            rows = rows[0]
        else:
            raise TypeError('invalid dimension tuple')

    if cols is None:
        cols = rows

    if equiv((rows, cols), (1, 1)):
        return float(cvxopt.base.normal(1, 1, mean=mean, std=std)[0])
    else:
        return cvxopt.base.normal(rows, cols, mean, std)

def rand(rows=1, cols=None, lowerlim=0, upperlim=1):
    if iterable(rows):
        if len(rows) == 2:
            cols = rows[1]
            rows = rows[0]
        else:
            raise TypeError('invalid dimension tuple')

    if cols is None:
        cols = rows

    if equiv((rows, cols), (1, 1)):
        return float(cvxopt.base.uniform(1, 1, lowerlim, upperlim)[0])
    else:
        return cvxopt.base.uniform(rows, cols, lowerlim, upperlim)

def linspace(start, end, N, incstop=True):
    x = zeros(N, 1, full=True)
    if incstop:
        step = (end - start) / (N - 1)
    else:
        step = (end - start) / N

    x[0] = start
    for i in range(1, N):
        x[i] = x[i-1] + step

    return x

def randseed(s=None):
    if s is None:
        cvxopt.base.setseed()
    else:
        cvxopt.base.setseed(s)

def joinlist(l, skipand=False):
    if not l:
        return ''
    elif len(l) == 1:
        return str(l[0])
    elif skipand:
        return ', '.join([str(x) for x in l])
    else:
        s = ''
        for x in l[:-2]:
            s += str(x) + ', '
        s += str(l[-2]) + ' and ' + str(l[-1])
        return s

def iterable(obj):
    """Returns True if obj is iterable, i.e., if obj is a sequence."""
    if isinstance(obj, (matrix, spmatrix)):
        return False
    try:
        len(obj)
        return True
    except TypeError:
        return False

def bylowerstr(l):
    return sorted(l, lambda x, y: cmp(str(x).lower(), str(y).lower()))

def slicetoindices(s, l):
    # takes a slice, a list or a constant, and returns a list of indices.
    # l is the length of the relevant object into which we are indexing.
    l = value(l)
    if isinstance(s, slice):
        # syntax is {range|slice}(start, stop, step).
        start = value(s.start)
        stop = value(s.stop)
        step = value(s.step)

        if start is None:
            start = 0

        if stop is None:
            stop = l

        if step is None:
            step = 1

        if stop < 0:
            stop = l + stop

        return range(start, stop, step)

    elif iterable(s):
        return [value(x) for x in s]
    
    else:
        return [value(s)]

def sqrtm(A):
    """Returns the matrix square root of a positive semidefinite matrix."""
    if not isinstance(A, (matrix, spmatrix)) or rows(A) != cols(A) or eig(A)[0][0] < 0:
        raise TypeError('a symmetric positive semidefinite matrix is required')

    V = matrix(A)
    z = zeros(rows(A), 1, full=True)
    lapack.syev(V, z, jobz='V')

    # Round eigenvalues to deal with numerical instability.
    # Note: don't use cvxmod atoms pos or sqrt here: overkill.
    for i in range(len(z)):
        if z[i] <= 0:
            z[i] = 0
        else:
            z[i] = sqrt(z[i])

    return V*diag(z)*tp(V)

def leastsquares(A, B):
    """Finds the least-squares approximate solution X, which minimizes ||AX -
    B||_fro.
    
    A must be full rank."""

    if not (isinstance(A, (matrix, spmatrix)) and isinstance(B, (matrix, spmatrix))):
        raise TypeError('both arguments must be matrices')

    if rows(A) < cols(A):
        raise DimError('A must be skinny')

    if rows(B) != rows(A):
        raise DimError('rows(B) must equal rows(A)')

    X = matrix(B)
    lapack.gels(matrix(A), X)
    return X

def leastnorm(A, B):
    """Finds the least-norm X which minimizes ||X||_fro while satisfying
    AX == B.
    
    A must be full rank."""

    if not (isinstance(A, (matrix, spmatrix)) and isinstance(B, (matrix, spmatrix))):
        raise TypeError('both arguments must be matrices')

    if rows(A) > cols(A):
        raise DimError('A must be fat')

    if rows(B) != rows(A):
        raise DimError('rows(B) must equal rows(A)')

    # Pad X to make room for the solution.
    X = concatvert(B, zeros(cols(A) - rows(B), cols(B), full=True))

    lapack.gels(matrix(A), X)
    return X

def eig(A):
    """Calculates the eigenvalues and eigenvectors of a real symmetric matrix.

    Returns (eigenvalues, eigenvectors), where the eigenvalues are sorted in
    increasing order."""
    if not isinstance(A, (matrix, spmatrix)):
        raise TypeError('a symmetric matrix is required')

    eigenvalues = zeros(rows(A), 1, full=True)
    eigenvectors = matrix(A)
    lapack.syevr(matrix(A), eigenvalues, jobz='V', Z=eigenvectors)
    return (eigenvalues, eigenvectors)

def svd(A):
    """Computes the singular value decomposition of a matrix.
    
    Returns (U, S, V) where the columns of U are the (truncated) left singular
    vectors, S contains the singular values in decreasing order, and the
    columns of V are the truncated right singular values. If (U, S, V) =
    svd(A) then A == U*diag(S)*transpose(V)."""
    m, n = size(A)
    k = min(m, n)
    S = zeros(k, 1, full=True)
    U = zeros(m, full=True)
    V = zeros(n, full=True)
    lapack.gesdd(matrix(A), S, jobz='A', U=U, Vt=V)
    return (U[:,0:k], S, tp(V[0:k,:]))

def cholsolve(A, B):
    B = matrix(B)
    cholmod.linsolve(A, B)
    return B

def spy(L):
    import pylab

    if isinstance(L, (matrix, spmatrix)):
        pylab.spy(matrix(L))
        return

    n = 0
    for (i, j) in L.keys():
        if i > n:
            n = i

        if j > n:
            n = j

    A = zeros(n+1)

    for (i, j) in L.keys():
        if isnonzero(L[i,j]):
            A[i,j] = 1.0


    pylab.spy(matrix(A))

def cholnum(A):
    # jem: retired code which will be removed soon. Used for testing code
    # generation of cholesky.
    n = rows(A)

    # Cholesky in Python.
    v = [None,]*n
    d = [None,]*n

    L = zeros(n)

    d[0] = A[0,0]

    for i in range(1, n):
        if isnonzero(A[i,0]):
            L[i,0] = A[i,0] / d[0]

    for j in range(1, n):
        for i in range(j):
            if iszero(L[j,i]) or iszero(d[i]):
                v[i] = 0
            else:
                v[i] = L[j,i]*d[i]

        v[j] = A[j,j]
        for i in range(j):
            if isnonzero(L[j,i]*v[i]):
                v[j] -= L[j,i]*v[i]

        d[j] = v[j]

        if j < n - 1:
            for i in range(j + 1, n):
                if iszero(A[i,j]):
                    L[i,j] = 0
                else:
                    L[i,j] = A[i,j]
                for k in range(j):
                    if isnonzero(L[i,k]*v[k]):
                        L[i,j] -= L[i,k]*v[k]
                if isnonzero(L[i,j]):
                    L[i,j] /= v[j]

    # Could replace this later by knowledge that these are identically 1.
    # Need some special token to add here, perhaps?
    for i in range(n):
        L[i,i] = 1

    return (sparse(L), matrix(d))

