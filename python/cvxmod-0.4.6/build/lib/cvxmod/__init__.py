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

import cvxopt
cvxopt.printing.options['dformat'] = '%#8.4g'
cvxopt.printing.options['width'] = 14
cvxopt.base.matrix_repr = cvxopt.printing.matrix_str_default

from base import *
from sets import *
from util import *

__all__ = ["matrix", "spmatrix"]
__all__ += base.__all__
__all__ += util.__all__
