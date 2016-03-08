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
# Outputs: Two 2D-arrays. One represents the offset in rows toward the
#       direction of greatest downward change. The other represents
#       the offset in columns toward the direction of greatest downward change.
# Functionality: Water flows in the direction where the terrain is 
#       the steepest. In our terrain model, we need to determine, at each point,
#       which direction the terrain drops the most.
def findLowNhbr( terrain ):
    """Creates two 2D-arrays the shape of terrain consisting
    of the offsets (row and column) to the neighbor with the minimum eleveation"""
    rowOffset = np.zeros_like( terrain )
    colOffset = np.zeros_like( terrain )
    for i in xrange(1, terrain.shape[0]-1):
        for j in xrange(1, terrain.shape[1]-1):
            minValue = terrain[i,j]
            for di in xrange(-1, 2):
                for dj in xrage(-1, 2):
                    if terrain[i+di,j+dj] < minValue:
                        minValue = terrain[i+di,j+dj]
                        rowOffset[i,j] = di
                        colOffset[i,j] = dj
    return rowOffset, colOffset



# Inputs: terrain - a 2D-array representing a terrain elevation map.
# Outputs: An NX2 array of integer pairs representing the indices (row, col)
#       of all of the "pits" in the terrain.
# Functionality: A "pit" in the terrain is, mathematically speaking, a
#       local minimum. It is the point in terrain that is lower than all
#       of its neighbors. This function find all of the points in the terrain
#       map (ignoring the boundary points) and returns the row, column index values of each pit.
def findPits( terrain ):
    """Creates an Nx2 array of the array index values (row, column) of the
    local minima (aka pits) of the given terrain"""
    rowOffset, colOffset = findLowNhbr( terrain )
    rowOffset[0,:] = 1
    rowOffset[-1,:] = 1
    rowOffset[:,0] = 1
    rowOffset[:,-1] = 1
    pits = np.where( np.logical_and(rowOffset==0, colOffset==0) )
    pits = np.vstack( ( pits[0], pits[1] ) )
    return pits.T



# Inputs: terrain - a 2D-array representing a terrain elevation map.
#       row - the row index of the starting point of the drop.
#       column - the column index of the starting point of the drop.
# Outputs: An NX2 array of integer pairs representing the path a raindrop
#       would follow down the terrain from the initial point (row, column).
#       The columns are the row and column indices of all the points in
#       the terrain that make up the path.
# Functionality: This function traces the path of a drop of water down the
#       terrain.
def traceDrop( terrain, row, column ):
    """Creates a path (an Nx2 array of row, column indices) of the path that a
    raindrop would travel starting at the position (row, column)"""
    flow = []
    rowOffset, colOffset = findLowNhbr(terrain)
    while rowOffset[row, column] != 0 or colOffset[row, column] != 0:
        flow.append([row,column])
        row = row + rowOffset[row, column]
        column = column + colOffset[row, column]
        
    flow.append([row,column])
    return np.array(flow)


## THE findFlow FUNCTION IS EXTRA CREDIT!!!

# Inputs: terrain - a 2D-array representing a terrain elevation map.
# Outputs: A 2D-array (the same shape as terrain) consisting of the total
#       flow through each point in the terrain (except the boundaries.)
# Functionality: Computes the flow at each point on the terrain by accumulating
#       flow from the highest points to the lowest points.
def findFlow( terrain ):
    """Computes the flow array of the terrain"""
    flow = np.ones_like(terrain)
    idx = np.argsort(-terrain, axis=None)
    rowOffset, colOffset = findLowNhbr(terrain)
    pits = findPits(terrain)
    for i in idx:
        rowIdx = i / terrain.shape[1]
        colIdx = i % terrain.shape[1]
        rowOff = rowOffset[rowIdx,colIdx]
        colOff = colOffset[rowIdx,colIdx]
        if rowOff!=0 or colOff != 0:
            flow[rowIdx+rowOff, colIdx+colOff] += flow[rowIdx, colIdx]
    return flow
