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

import cvxmod
from cvxmod.base import *
from cvxmod.base import addormultfunction, withbrackets
from cvxmod.util import iterable
from cvxmod.errors import *

__all__ = ["eyesymbol", "constsymb", "equivdims", "compactdims", "ch", "cv",
           "stdformlinsymb", "strsymbmatrix"]

class eyesymbol(symbol):
    symm = True
    psd = True
    def __init__(self, size):
        self.rows = size
        self.cols = size

    def __repr__(self):
        return "<%sx%s identity matrix>" % (withbrackets(self.rows),
           withbrackets(self.cols))

    def __str__(self):
        return 'I(%s)' % rows(self)

    def _getvalue(self):
        # jem. make this cache.
        return speye(value(self.rows))
    value = property(_getvalue)

    def nnz(self):
        return self.rows

    def nzentries(self):
        d = {}
        for i in range(value(self.rows)):
            d[i,i] = 1

        return d

class constsymb(symbol):
    def __init__(self, rs, cs, constval):
        self.rows = rs
        self.cols = cs
        self.role = 'constant'
        self.constval = constval

    def __repr__(self):
        if self.constval == 1:
            descr = "ones"
        else:
            descr = "zeros"
        descr += " "

        if equiv(self.cols, 1):
            descr += "vector"
        else:
            descr += "matrix"
        return "<%sx%s all %s>" % (withbrackets(self.rows),
           withbrackets(self.cols), descr)

    def __str__(self):
        if self.constval == 1:
            descr = "ones"
        else:
            descr = "zeros"

        return "%s(%s, %s)" % (descr, str(withbrackets(self.rows)),
                               str(withbrackets(self.cols)))

    def _getvalue(self):
        if self.constval == 1:
            return ones(value(self.rows), value(self.cols))
        else:
            return zeros(value(self.rows), value(self.cols))
    value = property(_getvalue)

    def etranspose(self):
        return constsymb(self.cols, self.rows, self.constval)

    def nnz(self):
        if iszero(self):
            return 0
        else:
            return self.rows*self.cols

    def nzentries(self):
        if iszero(self):
            return {}
        else:
            d = {}
            for i in range(value(self.rows)):
                for j in range(value(self.cols)):
                    d[i,j] = self.constval

            return d
    
def equivdims(lhs, rhs):
    """Compare two representations of a dimension, and see if they are the
    same."""

    if lhs is rhs:
        return True

    if lhs - rhs is 0:
        return True

    l = lhs - rhs

    if l is 0:
        return True
    elif isinstance(l, int):
        return False

    if getdimmult(l, None) is not 0:
        return False

    for p in getdims(l):
        a = getdimmult(l, p)
        if iszero(a):
            continue
        else:
            return False

    return True

def compactdims(x):
    """Turn b + b into 2*b."""
    # jem: will fail with products of dims.
    y = 0
    for p in sorted(getdims(x), lambda x, y: cmp(str(x).lower(),
                                                   str(y).lower())):
        y = y + getdimmult(x, p)*p

    return y + getdimmult(x, None)

class concathorizsymb(addormultfunction):
    def __init__(self, lhs, rhs):
        self.rows = rows(lhs)
        self.cols = compactdims(cols(lhs) + cols(rhs))

        self.lhs = lhs
        self.rhs = rhs

    def __repr__(self):
        return "<%sx%s horiz concat [%s; %s]>" % \
                (withbrackets(rows(self)), withbrackets(cols(self)),
                 str(self.lhs), str(self.rhs))

    def __str__(self):
        if isinstance(self.lhs, concathorizsymb):
            if isinstance(self.rhs, concathorizsymb):
                # both.
                return "%s %s" % (str(self.lhs)[:-1], str(self.rhs)[1:])
            else:
                # lhs only.
                return "%s %s]" % (str(self.lhs)[:-1], str(self.rhs))
        elif isinstance(self.rhs, concathorizsymb):
            # rhs only.
            return "[%s %s" % (str(self.lhs), str(self.rhs)[1:])
        else:
            return "[%s %s]" % (str(self.lhs), str(self.rhs))

    def _getvalue(self):
        return concathoriz(value(self.lhs), value(self.rhs))
    value = property(_getvalue)

    def getvarmult(self, var):
        l = getvarmult(self.lhs, var)
        r = getvarmult(self.rhs, var)
        if iszero(l):
            if var is None:
                l = zeros(size(self.lhs), symb=True)
            else:
                l = zeros(rows(self.lhs), rows(var), symb=True)
        if iszero(r):
            if var is None:
                r = zeros(size(self.rhs), symb=True)
            else:
                r = zeros(rows(self.rhs), rows(var), symb=True)

        return ch(l, r)

    def getvecmult(self, var):
        raise NotImplementedError('getvecmult for concathorizsymb')

    def nnz(self):
        return nnz(self.lhs) + nnz(self.rhs)

    def nzentries(self):
        d = {}
        d = nzentries(self.lhs)
        drhs = nzentries(self.rhs)

        n = value(cols(self.lhs))
        for (i, j) in drhs.keys():
            d[i,j+n] = drhs[i,j]

        return d

class concatvertsymb(addormultfunction):
    def __init__(self, lhs, rhs):
        self.cols = cols(lhs)
        self.rows = compactdims(rows(lhs) + rows(rhs))

        self.lhs = lhs
        self.rhs = rhs

    def __repr__(self):
        return "<%sx%s vert concat [%s; %s]>" % \
                (withbrackets(rows(self)), withbrackets(cols(self)),
                 str(self.lhs), str(self.rhs))

    def __str__(self):
        if isinstance(self.lhs, concatvertsymb):
            if isinstance(self.rhs, concatvertsymb):
                # both.
                return "%s %s" % (str(self.lhs)[:-1], str(self.rhs)[1:])
            else:
                # lhs only.
                return "%s; %s]" % (str(self.lhs)[:-1], str(self.rhs))
        elif isinstance(self.rhs, concatvertsymb):
            # rhs only.
            return "[%s; %s" % (str(self.lhs), str(self.rhs)[1:])
        else:
            return "[%s; %s]" % (str(self.lhs), str(self.rhs))
    def _getvalue(self):
        return concatvert(value(self.lhs), value(self.rhs))
    value = property(_getvalue)

    def getvarmult(self, var):
        l = getvarmult(self.lhs, var)
        r = getvarmult(self.rhs, var)
        if iszero(l):
            if var is None:
                l = zeros(size(self.lhs), symb=True)
            else:
                l = zeros(rows(self.lhs), rows(var), symb=True)
        if iszero(r):
            if var is None:
                r = zeros(size(self.rhs), symb=True)
            else:
                r = zeros(rows(self.rhs), rows(var), symb=True)

        return cv(l, r)

    def getvecmult(self, var):
        raise NotImplementedError('getvecmult for concatvertsymb')

    def nnz(self):
        return nnz(self.lhs) + nnz(self.rhs)
    def nzentries(self):
        d = {}
        d = nzentries(self.lhs)
        drhs = nzentries(self.rhs)

        m = value(rows(self.lhs))
        for (i, j) in drhs.keys():
            d[i+m,j] = drhs[i,j]

        return d

def ch(lhs, rhs):
    """Concatenate horizontally and symbolically, performing any available
    reductions."""
    if lhs is None:
        return rhs
    elif rhs is None:
        return lhs
    elif not equivdims(rows(lhs), rows(rhs)):
        raise DimError

    try:
        if lhs.constval == rhs.constval:
            return constsymb(rows(lhs), compactdims(cols(lhs) + cols(rhs)),
                             lhs.constval)
    except AttributeError:
        pass

    if isinstance(lhs, concathorizsymb):
        if isinstance(rhs, concathorizsymb):
            try:
                if lhs.rhs.constval == rhs.lhs.constval:
                    c = constsymb(rows(lhs.rhs),
                                  compactdims(cols(lhs.rhs) + cols(rhs.lhs)),
                                  lhs.rhs.constval)
                    return ch(ch(lhs.lhs, c), rhs.rhs)
            except AttributeError:
                pass
        else:
            try:
                if lhs.rhs.constval == rhs.constval:
                    c = constsymb(rows(lhs),
                                  compactdims(cols(lhs.rhs) + cols(rhs)),
                                  lhs.rhs.constval)
                    return ch(lhs.lhs, c)
            except AttributeError:
                pass
    elif isinstance(rhs, concathorizsymb):
        try:
            if lhs.constval == rhs.lhs.constval:
                c = constsymb(rows(lhs),
                              compactdims(cols(lhs) + cols(rhs.lhs)),
                              lhs.constval)
                return ch(c, rhs.rhs)
        except AttributeError:
            pass

    return concathorizsymb(lhs, rhs)
    
def cv(lhs, rhs):
    """Concatenate vertically and symbolically, performing any available
    reductions."""
    if lhs is None:
        return rhs
    elif rhs is None:
        return lhs
    elif not equivdims(cols(lhs), cols(rhs)):
        raise DimError

    try:
        if lhs.constval == rhs.constval:
            return constsymb(compactdims(rows(lhs) + rows(rhs)), cols(lhs),
                             lhs.constval)
    except AttributeError:
        pass

    if isinstance(lhs, concatvertsymb):
        if isinstance(rhs, concatvertsymb):
            try:
                if lhs.rhs.constval == rhs.lhs.constval:
                    c = constsymb(compactdims(rows(lhs.rhs) + rows(rhs.lhs)),
                                  cols(lhs.rhs), lhs.rhs.constval)
                    return cv(cv(lhs.lhs, c), rhs.rhs)
            except AttributeError:
                pass
        else:
            try:
                if lhs.rhs.constval == rhs.constval:
                    c = constsymb(compactdims(rows(lhs.rhs) + rows(rhs)),
                                  cols(lhs.rhs), lhs.rhs.constval)
                    return cv(lhs.lhs, c)
            except AttributeError:
                pass
    elif isinstance(rhs, concatvertsymb):
        try:
            if lhs.constval == rhs.lhs.constval:
                c = constsymb(compactdims(rows(lhs) + rows(rhs.lhs)),
                              cols(lhs), lhs.constval)
                return cv(c, rhs.rhs)
        except AttributeError:
            pass

    return concatvertsymb(lhs, rhs)

def stdformlinsymb(objv, lin, optvars, stdform='cAbGh'):
    # Symbolic version of stdformlin.

    A = None
    b = None
    G = None
    h = None
    for d in lin:
        s = d.stdlhs()
        r = None
        if d.sign == '==':
            for v in optvars:
                a = getvarmult(s, v)
                if iszero(a):
                    a = zeros(rows(s), rows(v), symb=True)
                r = ch(r, a)
            A = cv(A, r)
            bb = -getvarmult(s, None)
            if is1x1(bb) and not equiv(size(bb), size(s)):
                bb = bb*ones(size(s), symb=True)
            b = cv(b, bb)
        else:
            for v in optvars:
                a = getvarmult(s, v)
                if iszero(a):
                    a = zeros(rows(s), rows(v), symb=True)
                r = ch(r, a)
            G = cv(G, r)
            bb = -getvarmult(s, None)
            if is1x1(bb) and not equiv(size(bb), size(s)):
                if iszero(bb):
                    bb = zeros(size(s), symb=True)
                else:
                    bb = bb*ones(size(s), symb=True)
            h = cv(h, bb)

    if objv is None and A is not None:
        c = zeros(cols(A), 1, symb=True)
    else:
        c = None
        for v in optvars:
            a = etp(getvarmult(objv, v))
            if iszero(a):
                a = zeros(rows(v), 1, symb=True)
            c = cv(c, a)

    if stdform == 'cAbGh':
        return ((c, A, b, G, h), optvars)
    elif stdform == 'cAbp':
        m = rows(A)
        n = cols(A)
        p = rows(G)
        ysf = optvar('ysf', p)
        optvars.append(ysf)
        
        # Define new standard form as follows:
        # minimize ct^T*xt, subject to At*xt == bt, St*xt >= 0.
        # ct = [0; c]
        # At = [0 A; I G]
        # bt = [b; h]
        # xt = [x; ysf]
        # p = p.
        ct = cv(zeros(p, 1, True), c)
        At = cv(ch(zeros(m, p, True), A), ch(eye(p, True), G))
        bt = cv(b, h)

        return ((ct, At, bt, p), optvars)

def strsymbmatrix(A, name):
    s = ''
    s += 'rows: %s.\n' % withbrackets(rows(A))
    s += 'cols: %s.\n' % withbrackets(cols(A))
    s += '%s =\n' % name
    s += str(A).replace(';', ';\n') + '\n'
    return s
