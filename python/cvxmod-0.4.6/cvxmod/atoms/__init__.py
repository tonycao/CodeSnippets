"""
Convex atoms for cvxmod.

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

from cvxmod import *
from cvxmod.util import iterable

# jem. could do a search of the directory?
atoms = ["square", "log", "entropy", "exp", "kl", "sqrt", "huber", "quadform",
         "power", "lse", "inv", "logdet"]
__all__ = list(atoms)

class userfunc(object):
    def __init__(self, a):
        self.name = a.__name__.split('.')[-1]
        self.eval = a.eval
        self.functionalform = a.functionalform
        self.functionalform.name = self.name
        self.functionalform.eval = a.eval
        if iterable(a.applystdform):
            self.functionalform._stdforms = set(a.applystdform)
        else:
            self.functionalform._stdforms = set((a.applystdform,))
        # jem. redundancy, but used to make vex.split work.
        self.functionalform.func = self
        # jem: next line seems to be used only by test/atoms.py.
        self.module = a

        # only used for classify function etc (e.g. classify(log)).
        self.increasing = hasattr(self.functionalform, 'incfn') and \
                (not isinstance(self.functionalform.incfn, property)) and \
                self.functionalform.incfn
        self.decreasing = hasattr(self.functionalform, 'decfn') and \
                (not isinstance(self.functionalform.decfn, property)) and \
                self.functionalform.decfn
        self.pos = hasattr(self.functionalform, 'posfn') and \
                (not isinstance(self.functionalform.posfn, property)) and \
                self.functionalform.posfn
        self.neg = hasattr(self.functionalform, 'negfn') and \
                (not isinstance(self.functionalform.negfn, property)) and \
                self.functionalform.negfn
        self.convex = hasattr(self.functionalform, 'convfn') and \
                (not isinstance(self.functionalform.convfn, property)) and \
                self.functionalform.convfn
        self.concave = hasattr(self.functionalform, 'concfn') and \
                (not isinstance(self.functionalform.concfn, property)) and \
                self.functionalform.concfn

        self.psd = hasattr(self.functionalform, 'psd') and self.functionalform.psd
        self.nsd = hasattr(self.functionalform, 'nsd') and self.functionalform.nsd

    def __call__(self, *args):
        try:
            self.checkargs(args) # jem. make this more sophisticated?
        except AttributeError:
            pass

        try:
            a = self.earlyexit(args)
            if a is not None:
                return a
        except AttributeError:
            pass

        obj1 = args[0]
        if isinstance(obj1, (int, float, matrix, spmatrix)):
            return self.eval(*args)
        else:
            return self.functionalform(*args)

    def __repr__(self):
        return '<userfunc %s>' % self.functionalform.name

def check1arg(args):
    if len(args) != 1:
        raise AtomArgsError('wrong number of arguments, need 1')

# convert atoms for use.
for x in atoms:
    # special magic here.
    exec('import ' + x)
    # make a the module itself (won't be if imported later).
    exec('a=' + x)
    exec(a.__name__.split('.')[-1] + '=' + 'userfunc(a)')
    exec('s=' + a.__name__.split('.')[-1])

    if hasattr(a, 'checkargs'):
        s.checkargs = a.checkargs
    else:
        # assume exactly one argument required, unless we know otherwise.
        s.checkargs = check1arg

    # power(x, 1) should return x straight away. Use earlyexit for things like
    # this.
    if hasattr(a, 'earlyexit'):
        s.earlyexit = a.earlyexit
