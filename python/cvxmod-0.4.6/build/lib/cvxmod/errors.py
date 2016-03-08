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

__all__ = ["OptimizationError", "DimError", "OptvarValueError",
           "ParamValueError", "ProductError", "AssertionError",
           "ClassificationError", "ConvexityError",
           "ConstraintComplexityError", "StdFormError", "AtomArgsError",
           "TestError", "TransposedVarError", "OptvarBoundError"]

class OptimizationError(Exception):
    """Base class for errors in the jo package."""
    pass

class DimError(OptimizationError):
    """Occurs when combining two expressions of incompatible dimension."""
    def __init__(self, value='expressions have incompatible dimensions'):
        self.value = value

    def __str__(self):
        return repr(self.value)

class OptvarValueError(OptimizationError):
    """Occurs when an optvar has value None when it should not."""
    def __init__(self, value="optvar has value None"):
        self.value = value

    def __str__(self):
        return repr(self.value)

class ParamValueError(OptimizationError):
    """Occurs when a param has an inappropriate value (e.g. None when it
    shouldn't be."""
    def __init__(self, value="invalid param value"):
        self.value = value

    def __str__(self):
        return repr(self.value)

class ProductError(OptimizationError):
    """Occurs when two variables are multiplied."""
    def __init__(self, value="cannot form product of optimization variables"):
        self.value = value

    def __str__(self):
        return repr(self.value)

class AssertionError(OptimizationError):
    """Occurs when a param assertion is not met."""
    def __init__(self, value="problem assertion failed"):
        self.value = value

    def __str__(self):
        return repr(self.value)

class ClassificationError(OptimizationError):
    """Occurs when convexity or monotonicity cannot be determined."""
    def __init__(self, value="cannot classify object"):
        self.value = value

    def __str__(self):
        return repr(self.value)

class ConvexityError(OptimizationError):
    """Occurs when convexity is required and not assured."""
    def __init__(self, value="could not determine required convexity"):
        self.value = value

    def __str__(self):
        return repr(self.value)

class ConstraintComplexityError(OptimizationError):
    """Occurs when a constraint cannot be transformed or understood."""
    def __init__(self, value="constraint is too complicated"):
        self.value = value

    def __str__(self):
        return repr(self.value)

class StdFormError(OptimizationError):
    """Occurs when an expression is not in the expected standard form."""
    def __init__(self, value="expression is not in standard form"):
        self.value = value

    def __str__(self):
        return repr(self.value)

class AtomArgsError(OptimizationError):
    """Occurs when an atom is passed incorrect arguments."""
    def __init__(self, value="atom was passed incorrect arguments"):
        self.value = value

    def __str__(self):
        return repr(self.value)

class TestError(OptimizationError):
    """Occurs when an error is encountered during testing."""
    def __init__(self, value="error occurred during testing"):
        self.value = value

    def __str__(self):
        return repr(self.value)

class TransposedVarError(OptimizationError):
    """Occurs when a variable is transposed in an expression, thus preventing a
    correct result."""
    def __init__(self, value="transposed variable prevents valid result"):
        self.value = value

    def __str__(self):
        return repr(self.value)
class OptvarBoundError(OptimizationError):
    """Occurs when an optvar does not have a required bound."""
    def __init__(self, value="optvar does not have bound"):
        self.value = value

    def __str__(self):
        return repr(self.value)
