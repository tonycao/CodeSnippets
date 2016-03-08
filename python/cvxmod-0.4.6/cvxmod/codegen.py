"""
Code generation for CVXMOD.

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
from cvxmod.base import withbrackets, addfunction, multfunction, Jwarn,\
        addormultfunction, symbslice
from cvxmod.symbolic import *
from cvxmod.symbolic import concatvertsymb, concathorizsymb, constsymb, eyesymbol
from cvxmod.util import bylowerstr, joinlist
from cvxopt.amd import order

from time import strftime
import os
import re

class nze(symbol):
    # Nonzero elements, eg for use in a matrix. Invariant under multiplication
    # and division, except for by zero.
    def __init__(self, name=None):
        self.rows = 1
        self.cols = 1
        self.name = name

    def __repr__(self):
        return str(self)

    def __str__(self):
        if self.name is None:
            return '<nze>'
        else:
            return '<nze %s>' % self.name

    def __div__(self, other):
        if iszero(other):
            raise ZeroDivisionError
        else:
            return self

    def __rdiv__(self, other):
        if iszero(other):
            return 0
        else:
            return self

    def __mul__(self, other):
        if iszero(other):
            return 0
        else:
            return self

    def __rmul__(self, other):
        if iszero(other):
            return 0
        else:
            return self

    def __add__(self, other):
        return self

    def __radd__(self, other):
        return self

    def __sub__(self, other):
        return self

    def __rsub__(self, other):
        return self

class divfunction(addormultfunction):
    # first cut. no size checking or anything.
    def __init__(self, lhs, rhs):
        self.lhs = lhs
        self.rhs = rhs
        self.rows = 1
        self.cols = 1
        self.brackets = True

    def __str__(self):
        return withbrackets(self.lhs) + '/' + withbrackets(self.rhs)

def divide(lhs, rhs):
    if iszero(lhs) or iszero(rhs):
        return 0
    else:
        return divfunction(lhs, rhs)

class sparsedict(dict):
    def __init__(self):
        dict.__init__(self)

    def __getitem__(self, key):
        try:
            return dict.__getitem__(self, key)
        except KeyError:
            return 0

def addsplit(obj):
    # Argument order is (pre-operations, actual, nonindexed).
    if isoptvar(obj) or isparam(obj) or isinstance(obj, (int, float)):
        if is1x1(obj):
            return ([], [], obj)
        else:
            return ([], [obj], 0)
    elif isinstance(obj, addfunction):
        return [x + y for (x, y) in zip(addsplit(obj.lhs), addsplit(obj.rhs))]
    elif isinstance(obj, multfunction):
        if is1x1(obj.lhs):
            (pre, actual, nonind) = addsplit(obj.rhs)
            pre = [obj.lhs*x for x in pre]
            actual = [obj.lhs*x for x in actual]
            nonind = obj.lhs*nonind
            
            return (pre, actual, nonind)
        else:
            raise NotImplementedError('could not handle ' + str(obj))
    elif isinstance(obj, constsymb):
        return ([], [], obj.constval)
    else:
        raise NotImplementedError('could not handle ' + str(obj))

def stuffmatrix(obj, name):
    s = ''
    s += '\n// Begin: definition of %s.\n' % name
    for l in strsymbmatrix(obj, name).splitlines():
        s += '//   %s\n' % l

    s += '%s = malloc((%s)*sizeof(double));\n\n' % \
            (name, str(rows(obj) * cols(obj)))

    s += stuffentry(obj, name, rows(obj), 0, 0, 0)
    s += '// End: definition of %s.\n' % name

    return s

def stuffentry(obj, name, rs, csleft, rsabove, rsbelow, smult=1):
    def stuff1x1(val):
        return '%s[%s] = %s;\n' % (name, str(topleft), str(val))

    def nwsm(n):
        # Name with scalar multiplier.
        # Takes smult implicitly.
        return '%s' % str(smult*n)

    # here (or elsewhere) keep track of existing multiplied stuff. for example,
    # if we have tr(c)*x, don't want to have to work it out every time.

    # Everything should be able to accept a scalar multiple for one of its
    # arguments.

    s = ''
    topleft = rs*csleft + rsabove

    if isinstance(obj, (int, float, matrix, spmatrix)) and is1x1(obj):
        s += stuff1x1(str(obj))
    elif isinstance(obj, concatvertsymb):
        s += stuffentry(obj.lhs, name, rs, csleft, rsabove, rsbelow, smult)
        s += stuffentry(obj.rhs, name, rs, csleft, rsabove + rows(obj.lhs),
                        rsbelow - rows(obj.lhs), smult)
    elif isinstance(obj, concathorizsymb):
        s += stuffentry(obj.lhs, name, rs, csleft, rsabove, rsbelow, smult)
        s += stuffentry(obj.rhs, name, rs, csleft + cols(obj.lhs), rsabove,
                        rsbelow, smult)
    elif isinstance(obj, constsymb):
        s += 'for (col = 0; col < %s; col++)\n' % str(cols(obj))
        s += ' '*4 + 'for (row = 0; row < %s; row++)\n' % str(rows(obj))
        s += ' '*8 + '%s[%s + col*(%s) + row] = %s;\n\n' % \
                (str(name), str(topleft), str(rs), nwsm(obj.constval))
    elif isinstance(obj, eyesymbol):
        s += 'for (col = 0; col < %s; col++)\n' % str(cols(obj))
        s += ' '*4 + 'for (row = 0; row < %s; row++)\n' % str(rows(obj))
        s += ' '*8 + '%s[%s + col*(%s) + row] =\n          (row == col) ? %s : 0;\n\n' % \
                (str(name), str(topleft), str(rs), str(smult))
    elif isparam(obj):
        s += 'for (col = 0; col < %s; col++)\n' % str(cols(obj))
        s += ' '*4 + 'for (row = 0; row < %s; row++)\n' % str(rows(obj))
        s += ' '*8 + '%s[%s + col*(%s) + row] =\n          %s[col*(%s) + row];\n\n' % \
                (str(name), str(topleft), str(rs), nwsm(obj), str(rows(obj)))
    elif isinstance(obj, multfunction):
        # nastiness of non-recursion here!
        if is1x1(obj.lhs):
            s += stuffentry(obj.rhs, name, rs, csleft, rsabove, rsbelow, obj.lhs)
        else:
            raise NotImplementedError('could not handle ' + str(obj))
    elif isinstance(obj, addfunction):
        # pre: temporary variables that need to be calculated first.
        # (need to come up with an indexing scheme so that A*x, for example,
        # can be reused. Probably assume 
        # actual: pieces of expression that should be indexed.
        # noniter: pieces of expression that should not be indexed.

        (pre, actual, nonind) = addsplit(obj)

        if pre:
            s += pre + '\n\n'

        rhs = "\n" + " "*11 + " + " .join(
            [str(smult*x) + ("[col*(%s) + row]" % str(cols(x))) for x in actual])
        if nonind:
            rhs += "\n" + " "*10 + " + " + str(smult*nonind)

        s += 'for (col = 0; col < %s; col++)\n' % str(cols(obj))
        s += ' '*4 + 'for (row = 0; row < %s; row++)\n' % str(rows(obj))
        s += ' '*8 + '%s[%s + col*(%s) + row] = %s;\n' % \
                (str(name), str(topleft), str(rs), rhs)
    else:
        raise NotImplementedError('could not handle ' + str(obj))

    return s

def exprtoC(obj):
    if isinstance(obj, symbslice):
        (a, b) = obj.splitsl()
        if b is None:
            return str(obj.arg) + '[%d]' % a
        else:
            index = a + b*value(rows(obj.arg))
            return str(obj.arg) + '[%d]' % index
    elif isinstance(obj, (int, float)):
        return str(obj)
    elif isinstance(obj, multfunction):
        if obj.lhs is -1:
            return '-' + exprtoC(obj.rhs)
        else:
            return exprtoC(obj.lhs) + '*' + exprtoC(obj.rhs)
    elif isinstance(obj, addfunction):
        return exprtoC(obj.lhs) + ' + ' + exprtoC(obj.rhs)
    else:
        raise NotImplementedError('cannot handle %s' % str(obj))

class codegen(object):
    def __init__(self, p, outdir, skel):
        self.p = p
        self.outdir = outdir
        self.skel = skel

    def printmatrix(self, x):
        m = rows(x)
        n = cols(x)
        s = 'printf("%s =\\n");\n' % str(x)
        s += "printmatrix(%s, %s, %s);\n" % (str(x), str(m), str(n))
        self.write(s)

    def declarematrix(self, A):
        s = "double %s[] = {\n " % str(A)
        offset = 1
        v = matrix(value(A))
        k = 0
        for j in range(value(cols(A))):
            for i in range(value(rows(A))):
                t = "% .7g, " % v[i,j]
                # jem: enhance this later to be nicer looking.
                s += t.rjust(12)
                if (k % 7) == 6:
                    s += "\n"
                    s += ' ' * offset
                k += 1
            #s += "\n"
            #s += ' ' * offset

        s = s[:-(offset+3)] + "};\n\n"
        return s

    def readme(self):
        p = self.p

        d = {}
        d['header'] = header()
        d['probdef'] = str(p)
        d['stdform'] = p.strsymbsolve()

        writecode(self.outdir, self.skel, 'README', d)

    def tostdform(self):
        p = self.p

        ((ct, At, bt, Gt, ht), xt, d, optvars) = p.symbsolve('cAbGh')

        d = {}
        d['header'] = header()

        # Now is when we determine the signature.
        sig = 'lpstdform tostdform(\n' + ' '*8
        if getdims(p):
            sig += ', '.join(['int %s' % x for x in bylowerstr(getdims(p))])

        if getparams(p):
            sig += ',\n' + ' '*8
            sig += ', '.join(['double *%s' % x for x in bylowerstr(getparams(p))])

        sig += ')'
        d['tostdform_sig'] = sig

        d['lsf_c'] = stuffmatrix(ct, 'lsf->c')
        d['lsf_A'] = stuffmatrix(At, 'lsf->A')
        d['lsf_b'] = stuffmatrix(bt, 'lsf->b')
        d['lsf_G'] = stuffmatrix(Gt, 'lsf->G')
        d['lsf_h'] = stuffmatrix(ht, 'lsf->h')

        sig = 'int convertback(outvar *vars,\n' + ' '*8
        if getdims(p):
            sig += ', '.join(['int %s' % x for x in bylowerstr(getdims(p))])
        sig += ',\n        double *xt)'

        d['convertback_sig'] = sig
        d['lsf_m'] = str(rows(At))
        d['lsf_n'] = str(cols(At))
        d['lsf_p'] = str(rows(Gt))

        s = ''
        i = 0
        rs = 0
        for x in optvars:
            if x in getoptvars(p):
                # jem: need to also deal with substitute back situations.
                s += '// Recover %s.\n' % str(x)
                name = 'vars[%d]' % i;
                s += '%s->m = %s;\n' % (name, str(rows(x)))
                s += '%s->n = 1;\n' % name # for the moment (jem).
                s += '%s->val = malloc((%s)*sizeof(double));\n' % (name, str(cols(x)))
                s += 'for (row = 0; row < %s; row++)\n' % str(rows(x))
                s += '    %s->val[row] = xt[%s + row];\n\n' % (name, str(rs))
                i += 1

            rs = compactdims(rs + rows(x))

        d['varrecover'] = s

        writecode(self.outdir, self.skel, 'tostdform.h', d)
        writecode(self.outdir, self.skel, 'tostdform.c', d)

    def data(self):
        p = self.p

        d = {}
        d['header'] = header()

        s = ''
        for x in getparams(p):
            s += self.declarematrix(x)
        d['params'] = s

        writecode(self.outdir, self.skel, 'data.h', d)

    def feasdata(self, As, bs, n, p, LOWER):
        d = {}
        d['header'] = header()


        print 'Solving feasibility problem to get feasible starting point.'
        As = value(As)
        bs = value(bs)
        p = value(p)
        x = optvar('x', n)
        prob = problem(constr=[As*x == bs, x[:p] >= 0, x[p:] >= -LOWER + 1])
        prob.solve()

        x = value(x)
        s = ''
        for i in range(rows(x)):
            s += 'CM_x[%d] = % .8g;\n' % (i, x[i])

        d['CM_x'] = s
        writecode(self.outdir, self.skel, 'feas.h', d)

        return x

    def testfa(self, n):
        p = self.p

        d = {}
        d['header'] = header()

        d['n'] = n

        d['params'] = joinlist(bylowerstr(getparams(p)), True)
        d['optvars'] = joinlist(bylowerstr(getoptvars(p)), True)

        s = joinlist(bylowerstr(getparams(p)), True)
        d['fa_args'] = s

        writecode(self.outdir, self.skel, 'testfa.c', d)

    def testba(self, n):
        p = self.p

        dt = {}
        dt['header'] = header()

        dt['n'] = n

        dt['params'] = joinlist(bylowerstr(getparams(p)), True)
        dt['optvars'] = joinlist(bylowerstr(getoptvars(p)), True)

        print 'Creating method signature.'
        if getparams(self.p):
            dt['fb_sig_params'] = ', '.join(['double *%s' % x for x in \
                                     bylowerstr(getparams(self.p))])
            dt['fb_sig_params'] += ','
        else:
            dt['fb_sig_params'] = ''

        dt['fb_args'] = joinlist(bylowerstr(getparams(p)), True)

        writecode(self.outdir, self.skel, 'testba.c', dt)

    def test2p(self, As, bs, cs, m, n, p):
        dt = {}
        dt['header'] = header()
        dt['m'] = value(m)
        dt['n'] = value(n)
        dt['p'] = value(p)

        dt['params'] = joinlist(bylowerstr(getparams(self.p)), True)
        dt['optvars'] = joinlist(bylowerstr(getoptvars(self.p)), True)

        print 'Generating code for two phase fast barrier method:'

        print 'Creating method signature.'
        if getparams(self.p):
            dt['fb_sig_params'] = ', '.join(['double *%s' % x for x in \
                                     bylowerstr(getparams(self.p))])
            dt['fb_sig_params'] += ','
        else:
            dt['fb_sig_params'] = ''

        A = nzentries(As)
        b = nzentries(bs)
        print 'Generating code for initial feasible point.'
        s = ''
        # CVXMOD_WL_t1.
        t1 = optvar('CM_t1', m, 1)
        for i in range(m):
            t = -b[i]
            for j in range(n):
                if (i,j) in A:
                    t = t + A[i,j]
            s += 'CM_t1[%d] = %s;\n' % (i, exprtoC(t))
        dt['CM_t1'] = s
        dt['fb_args'] = joinlist(bylowerstr(getparams(self.p)), True)

        writecode(self.outdir, self.skel, 'test2p.c', dt)


    def fastacent(self, As, cs, m, n, p):
        dt = {}
        dt['header'] = header()
        dt['m'] = value(m)
        dt['n'] = value(n)
        dt['p'] = value(p)

        print 'Generating code for fast analytic centering method:'

        print 'Framing objective.'
        cs = value(cs)
        s = ''
        for i in range(n):
            s += 'CM_c[%d] = %s;\n' % (i, exprtoC(cs[i]))
        dt['CM_c'] = s

        print 'Creating method signature.'
        if getparams(self.p):
            dt['params'] = ', '.join(['double *%s' % x for x in \
                                      bylowerstr(getparams(self.p))])
            dt['params'] += ','
        else:
            dt['params'] = ''

        print 'Inspecting problem structure.'
        A = nzentries(As)
        AT = nzentries(tp(As))

        # Create a gh optvar simply to make it easy to convert the multiplication.
        gh = optvar('CM_gh', n, 1)
        
        # Now multiply and solve.
        print 'Generating reduced Newton system coefficient matrix.'
        (ASATnum, s, ss, p) = self.multstuff(A, AT, m, n)
        dt['CM_ASAT'] = s
        dt['CM_ASAT_size'] = len(ss)

        # Reverse the permutation. Ran into a weird bug when trying a fancier
        # scheme of inverting the permutation.
        pinv = [None,]*len(p)
        for i in range(len(p)):
            pinv[p[i]] = i

        print 'Generating code for b = A*gh.'
        s = ''
        # Take note of the (inverse) permutation p.
        for i in range(m):
            d = 0
            for j in range(n):
                if (p[i], j) in A:
                    d = d - A[p[i],j]*gh[j]
            s += 'CM_b[%d] = %s;\n' % (i, exprtoC(d))
        dt['CM_b'] = s


        print 'Generating Cholesky factorization and solution code:'
        (d, (L, ssL, KL)) = self.cholsolve(ASATnum, ss)

        dt.update(d)

        print 'Generating code for dx.'
        s = ''
        w = optvar('CM_w', m, 1)
        for i in range(n):
            d = 0
            for j in range(m):
                if (i, j) in AT:
                    # Take note of the (inverse) permutation p.
                    d = d + AT[i,j]*w[pinv[j]]
            s += 'CM_dx[%d] = -CM_h[%d]*(%s + CM_g[%d]);\n' % (i, i, exprtoC(d), i)
        dt['CM_dx'] = s

        writecode(self.outdir, self.skel, 'fastacent.c', dt)

    def fastbarr(self, As, bs, cs, m, n, p, suffix=''):
        dt = {}
        dt['header'] = header()
        dt['m'] = value(m)
        dt['n'] = value(n)
        dt['p'] = value(p)

        dt['suffix'] = suffix

        print 'Generating code for fast barrier method:'

        print 'Framing objective.'
        cs = value(cs)
        s = ''
        for i in range(n):
            s += 'CM_c[%d] = %s;\n' % (i, exprtoC(cs[i]))
        dt['CM_c'] = s

        print 'Creating method signature.'
        if getparams(self.p):
            dt['params'] = ', '.join(['double *%s' % x for x in \
                                      bylowerstr(getparams(self.p))])
            dt['params'] += ','
        else:
            dt['params'] = ''

        print 'Inspecting problem structure.'
        A = nzentries(As)
        AT = nzentries(tp(As))

        # Create a gh optvar simply to make it easy to convert the multiplication.
        gh = optvar('CM_gh', n, 1)
        
        # Now multiply and solve.
        print 'Generating reduced Newton system coefficient matrix.'
        (ASATnum, s, ss, p) = self.multstuff(A, AT, m, n)
        dt['CM_ASAT'] = s
        dt['CM_ASAT_size'] = len(ss)

        # Reverse the permutation. Ran into a weird bug when trying a fancier
        # scheme of inverting the permutation.
        pinv = [None,]*len(p)
        for i in range(len(p)):
            pinv[p[i]] = i

        print 'Generating code for b = A*gh.'
        s = ''
        # Take note of the (inverse) permutation p.
        for i in range(m):
            d = 0
            for j in range(n):
                if (p[i], j) in A:
                    d = d - A[p[i],j]*gh[j]
            s += 'CM_b[%d] = %s;\n' % (i, exprtoC(d))
        dt['CM_b'] = s


        print 'Generating Cholesky factorization and solution code:'
        (d, (L, ssL, KL)) = self.cholsolve(ASATnum, ss)

        dt.update(d)

        print 'Generating code for dx.'
        s = ''
        w = optvar('CM_w', m, 1)
        for i in range(n):
            d = 0
            for j in range(m):
                if (i, j) in AT:
                    # Take note of the (inverse) permutation p.
                    d = d + AT[i,j]*w[pinv[j]]
            s += 'CM_dx[%d] = -CM_h[%d]*(%s + CM_g[%d]);\n' % (i, i, exprtoC(d), i)
        dt['CM_dx'] = s

        writecode(self.outdir, self.skel, 'fastbarr.c', dt,
                  outname='fastbarr%s.c' % suffix)

    def testwithdata(self, dispvars=False):
        p = self.p

        d = {}
        d['header'] = header()

        d['dims'] = joinlist(bylowerstr(getdims(p)), True)
        d['params'] = joinlist(bylowerstr(getparams(p)), True)
        d['optvars'] = joinlist(bylowerstr(getoptvars(p)), True)
        d['numvars'] = str(len(getoptvars(p)))

        # jem: making the assumption that optvars order will be sorted like
        # this.
        s = ''
        i = 0
        for x in bylowerstr(getoptvars(p)):
            s += 'outvar %s;\n%s = vars[%d];\n' % (str(x), str(x), i)
            i += 1
        d['namevars'] = s

        s = joinlist(bylowerstr(getdims(p)) + bylowerstr(getparams(p)), True)
        d['tsf_args'] = s

        # jemjemjem.
        #if dispvars:
        #    d['tsf_args'] = s
        #// Display the variables.
        #pm(x->val, x->m, x->n);
        #pm(y->val, y->m, y->n);

        writecode(self.outdir, self.skel, 'testwithdata.c', d)

    def backsubs(self, L, n, ssL):
        # Include an implicit transpose here. ie, L is a lower triangular
        # version of an upper triangular matrix.
        s = ''
        for i in range(n - 1, -1, -1):
            #s += 'CM_w[%d] = CM_x[%d];\n' % (i, i)
            for j in range(i + 1, n):
                if not iszero(L[j,i]):
                    s += 'CM_w[%d] -= CM_L[%s]*CM_w[%d];\n' % (i, ssL[j,i], j)

        return s

    def forwardsubs(self, L, n, ssL):
        s = ''
        for i in range(n):
            s += 'CM_w[%d] = CM_b[%d];\n' % (i, i)
            for j in range(0, i):
                if not iszero(L[i,j]):
                    s += 'CM_w[%d] -= CM_L[%s]*CM_w[%d];\n' % (i, ssL[i,j], j)

        return s

    def cholsolve(self, Anum, ssA):
        n = rows(Anum)
        (L, ssL, KL, Aclean) = self.cholss(Anum, ssA)

        dt = {}
        dt['CM_L_size'] = KL

        print '- code for Cholesky factorization.'
        dt['chol'] = self.chol(Aclean, n, ssA, ssL)
        print '- code for forward substitution.'
        dt['forwardsubs'] = self.forwardsubs(L, n, ssL)

        print '- code for back substitution.'
        dt['backsubs'] = self.backsubs(L, n, ssL)
        return (dt, (L, ssL, ssA))

    def chol(self, A, n, ssA, ssL):
        v = [None,]*n
        d = [None,]*n
        L = {}
        d[0] = nze()
        s = 'CM_d[0] = CM_ASAT[%d];\n' % ssA[0,0]

        for i in range(1, n):
            L[i,0] = A[i,0]# / d[0]
            if (i,0) in ssA:
                s += 'CM_L[%d] = CM_ASAT[%d] / CM_d[0];\n' % (ssL[i,0], ssA[i,0])

        for j in range(1, n):
            for i in range(j):
                v[i] = L[j,i]*d[i]
                if isnonzero(L[j,i]) and isnonzero(d[i]):
                    s += 'CM_v[%d] = CM_L[%d]*CM_d[%d];\n' % (i, ssL[j,i], i)

            v[j] = A[j,j]
            s += 'CM_v[%d] = CM_ASAT[%d];\n' % (j, ssA[j,j])

            for i in range(j):
                v[j] = v[j] - L[j,i]*v[i]
                if isnonzero(L[j,i]*v[i]):
                    s += 'CM_v[%d] -= CM_L[%d]*CM_v[%d];\n' % (j, ssL[j,i], i)

            d[j] = v[j]
            s += 'CM_d[%d] = CM_v[%d];\n' % (j, j)

            if j < n - 1:
                for i in range(j + 1, n):
                    L[i,j] = A[i,j]
                    if (i,j) in ssL:
                        if isnonzero(A[i,j]):
                            s += 'CM_L[%d] = CM_ASAT[%d];\n' % (ssL[i,j], ssA[i,j])
                        else:
                            s += 'CM_L[%d] = 0;\n' % ssL[i,j]
                    else:
                        continue

                    for k in range(j):
                        L[i,j] = L[i,j] - L[i,k]*v[k]
                        if isnonzero(L[i,k]*v[k]):
                            s += 'CM_L[%d] -= CM_L[%d]*CM_v[%d];\n' % (ssL[i,j], ssL[i,k], k)

                    if isnonzero(L[i,j]):
                        s += 'CM_L[%d] /= CM_v[%d];\n' % (ssL[i,j], j)

        # Implicitly assuming CM_L_{ii} = 1 for all i.
        return s

    def cholss(self, Anum, ssA):
        # Returns (L, Lss) where Lss[i,j] returns the index to store L[i,j].
        # L[i,j] = nze() or 0.
        # Note: implicit about the fact that L_{ii} = 1 for all i.
        n = rows(Anum)

        # Work from a clean A.
        A = sparsedict()
        for i in range(n):
            for j in range(i + 1):
                if isnonzero(Anum[i,j]):
                    A[i,j] = nze()

        v = [None,]*n
        d = [None,]*n
        L = sparsedict()
        d[0] = A[0,0]

        for i in range(1, n):
            L[i,0] = A[i,0]

        for j in range(1, n):
            for i in range(j):
                v[i] = L[j,i]*d[i]

            v[j] = A[j,j]

            for i in range(j):
                v[j] = v[j] - L[j,i]*v[i]

            d[j] = v[j] # will probably be translated directly.

            if j < n - 1:
                for i in range(j + 1, n):
                    L[i,j] = A[i,j]
                    for k in range(j):
                        L[i,j] = L[i,j] - L[i,k]*v[k]

        # Compute (simple) storage scheme for L.
        k = 0
        ssL = {}
        Lclean = sparsedict()
        for i in range(n):
            for j in range(n):
                if isnonzero(L[i,j]):
                    ssL[i,j] = k
                    Lclean[i,j] = nze()
                    k += 1
        KL = k

        return (Lclean, ssL, KL, A)

    def cholmoddata(self, Anum):
        # jem: temporary function.
        # jem: later need to store only one half of A: pick which!

        d = {}
        d['header'] = header()

        # There must be a better way of doing this.
        n = rows(Anum)
        s = ''
        s += 'int *Ai = At->i;\n'
        s += 'int *Aj = At->j;\n'
        s += 'double *Ax = At->x;\n'

        k = 0
        for i in range(n):
            for j in range(i, n):
                if isnonzero(Anum[i,j]):

                    s += 'Ai[%d] = %d; ' % (k, i)
                    s += 'Aj[%d] = %d; ' % (k, j)
                    s += 'Ax[%d] = %.7g;\n' % (k, Anum[i,j])
                    k += 1

        s = 'At = cholmod_allocate_triplet(%d, %d, %d, 1, CHOLMOD_REAL, &common);\n' % \
                (n, n, k) + s
        s = 'cholmod_triplet *At;\n' + s
        s += 'At->nnz = %d;\n' % k

        d['At'] = s

        writecode(self.outdir, self.skel, 'cholmod_data.h', d)

    def choldata(self, Anum, bnum, n):
        # jem: later need to store only one half of A: pick which!

        d = {}
        d['header'] = header()

        ssA = self.cholss(Anum, True)

        s = ''
        for (i, j) in sorted(ssA.keys()):
            s += 'A[%d] = %.7g;\n' % (ssA[i, j], Anum[i,j])

        d['A'] = s

        s = ''
        for i in range(n):
            s += 'b[%d] = %.7g;\n' % (i, bnum[i])

        d['b'] = s

        writecode(self.outdir, self.skel, 'chol_data.h', d)

    def backsubsdata(self, L, ss, b):
        # jem: temporary function.

        d = {}
        d['header'] = header()

        (dss, K) = ss
        b = param('b', value=b)

        # Reverse the role of the keys and values.
        dss2 = {}
        for k in dss.keys():
            dss2[dss[k]] = k

        s = ''
        for k in range(K):
            s += 'L[%d] = %.7g;\n' % (k, L[dss2[k]])
        d['L'] = s

        d['b'] = self.declarematrix(b)

        writecode(self.outdir, self.skel, 'backsubs_data.h', d)

    def multstuff(self, A, AT, m, n):
        """Multiplies and stuffs matrices."""

        # Make a sparse mask of rn. Use A*A'.
        Am = zeros(m, n)
        for k in A.keys():
            Am[k] = 1
        Am = Am*tp(Am)

        p = order(Am)
        Ao = Am[p,p]

        # Design a simple storage scheme for Ao.
        k = 0
        ss = {}
        for (i, j) in zip(Ao.I, Ao.J):
            if i >= j:
                ss[i,j] = k
                k += 1

        # Find reduced Newton system matrix ASAT.
        d = {}
        ASAT = {}
        # Write some code.
        h = param('CM_h', m, 1)
        for i in range(m):
            ip = p[i]
            for j in range(i + 1):
                jp = p[j]
                for k in range(n):
                    if (ip,k) in A and (k,jp) in AT:
                        if ss[i,j] not in d:
                            d[ss[i,j]] = exprtoC(A[ip,k] * h[k] * AT[k,jp])
                        else:
                            d[ss[i,j]] += ' + ' + exprtoC(A[ip,k] * h[k] * AT[k,jp])

        s = ''
        for k in sorted(d.keys()):
            s += 'CM_ASAT[%d] = %s;\n' % (k, d[k])

        return (Ao, s, ss, p)

    def sparsematrixvec(self, ss, m, n, A, x, b):
        """Provides explicit C code for multiplying A*x, where ss is the
        storage scheme for a sparse matrix A, and x and b are both strings."""
        A = nzentries(A)

        x = optvar(x, n)

        for i in range(m):
            d = 0
            for j in range(n):
                if (i, j) in ss:
                    d = d + A[i,j]*x[j]
                    print A[i,j]
                    print d
            print '%s[%d] = %s;' % (b, i, exprtoC(d))

    def getss(self, A):
        # Design a simple storage scheme for Ao.
        m, n = value(size(A))
        A = nzentries(A)

        # Make a sparse mask of A.
        Am = zeros(m, n)
        for k in A.keys():
            Am[k] = 1

        k = 0
        ss = {}
        for (i, j) in zip(Am.I, Am.J):
            if i >= j:
                ss[i,j] = k
                k += 1

        return ss

def withheading(s):
    return s.rstrip() + '\n' + '-'*len(s.rstrip()) + '\n'

def header():
    s = '// CVXMOD code generation.\n'
    s += '// Produced by CVXMOD, %s.\n' % strftime("%Y-%m-%d %H:%M:%S")
    s += '// CXVMOD is Copyright (C) 2006-2008 Jacob Mattingley.\n'
    return s

def writecode(outdir, skeleton, inname, d, outname=None):
    if outname is None:
        outname = inname

    infile = open(os.path.join(skeleton, inname))
    outname = os.path.join(outdir, outname)
    outfile = open(outname, 'w')
    print 'Writing to %s.' % outname
    ril = re.compile('(CVXMOD_IL_(\\w+))')
    rwl = re.compile('(\s*)CVXMOD_WL_(\\w+);?')
    ind = ''
    for l in infile:
        # Test for inline tags. Only one allowed max, per line.
        g = ril.search(l)
        # Test for whole line tags. These take on the same indent as the tag.
        h = rwl.search(l)

        if g:
            try:
                outfile.write(l[:g.start(1)] + str(d[g.group(2)]) + l[g.end(1):])
            except KeyError:
                Jwarn('could not match tag: ' + g.group(2))
                outfile.write(l[:-1] + ' // XXX failed to match tag.\n')
        elif h:
            try:
                for l2 in d[h.group(2)].splitlines():
                    outfile.write(h.group(1) + l2 + '\n')
            except KeyError:
                Jwarn('could not match tag: ' + h.group(2))
                outfile.write(l[:-1] + ' // XXX failed to match tag.\n')
        else:
            outfile.write(ind + l)

    infile.close()
    outfile.close()

