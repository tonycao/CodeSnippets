#######################################################################################
## Assignment 4                                                                      ##
## Discussion is allowed.                                                            ##
## Copying or sharing code is prohibited.                                            ##
## By typing your name below, you indicate agreement with the UNC Honor Code Pledge, ##
## that you have not given or received unauthorized assistance on this assignment.   ##
## Name:                                                                             ##
## Collaborators:                                                                    ## 
#######################################################################################

import numpy as np

# Inputs: terrain - a 2D-array representing a terrain elevation map.
# Outputs: Two 2D arrays. One represents the offset in rows toward the
#          direction of greatest downward change. The other represents
#          the offset in columns toward the direction of greatest downward change.
# Functionality: Water flows in the direction where the terrain is 
#                the steepest. In our terrain model, we need to determine, at each point,
#                which direction the terrain drops the most.

def findLowNhbr( terrain ):
    """Return two 2D arrays the shape of terrain consisting
    of the offsets (row and column) to the neighbor with the minimum eleveation"""
    return None, None

# Inputs: terrain - a 2D array representing a terrain elevation map.
# Outputs: An N-by-2 array of integer pairs representing the indices (row, col)
#          of all of the "pits" in the terrain.
# Functionality: A "pit" in the terrain is, mathematically speaking, a
#                local minimum. It is the point in terrain that is lower than all
#                of its neighbors. This function find all of the points in the terrain
#                map (ignoring the boundary points) and returns the row, column index values of each pit.

def findPits( terrain ):
    """Creates an N-by-2 array of the array index values (row, column) of the
    local minima (aka pits) of the given terrain"""
    return None



# Inputs: terrain - a 2D array representing a terrain elevation map.
#         row - the row index of the starting point of the drop.
#         column - the column index of the starting point of the drop.
# Outputs: An NX2 array of integer pairs representing the path a raindrop
#          would follow down the terrain from the initial point (row, column).
#          The columns are the row and column indices of all the points in
#          the terrain that make up the path.
# Functionality: This function traces the path of a drop of water down the
#                terrain.

def traceDrop( terrain, row, column ):
    """Create a path (an N-by-2 array of row, column indices) of the path that a
    raindrop would travel starting at the position (row, column)"""
    return None
