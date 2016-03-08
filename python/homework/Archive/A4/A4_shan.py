#######################################################################################
## Assignment 4                                                                      ##
## Discussion is allowed.                                                            ##
## Copying or sharing code is prohibited.                                            ##
## By typing your name below, you indicate agreement with the UNC Honor Code Pledge, ##
## that you have not given or received unauthorized assistance on this assignment.   ##
## Name: Liang Shan                                                                  ##
## Collaborators: None                                                               ## 
#######################################################################################

import numpy as np
import pylab
from A4Func_shan import *

# peaks and pits
terrain = np.load('elevation.npy')
#terrain = np.load('test.npy')

#1 Draw the terrain 
pylab.figure()
pylab.imshow(terrain, cmap = pylab.cm.gray)
pylab.savefig('terrain.png')

#2 Draw pits on the terrain
pits = findPits(terrain)
pylab.plot(pits[:,1], pits[:,0], 'r.')

#3 Draw peaks on the terrain
peaks = findPits(-terrain)
pylab.plot(peaks[:,1], peaks[:,0], 'g+')

#4 Print the number of peaks and the number of pits
num_pits = pits.shape[0] # replace with your code here
num_peaks = peaks.shape[0] # replace withyour code here

print 'Number of peaks:',num_peaks
print 'Number of pits:',num_pits

#5 Save this figure as 'peaksNPits.png'
pylab.axis('image')
pylab.savefig("peaksNPits_shan.png")
pylab.close()

#6-9 Trace drop in the terrain
pylab.imshow( terrain, cmap=pylab.cm.gray ) 
point = np.array( pylab.ginput(1)[0] ) 
r = int( np.round( point[1] ) ) 	# an integer row index 
c = int( np.round( point[0] ) ) # an integer column index

print 'Clicked point at (row=',r,',col=',c,')...'

path = traceDrop( terrain, r, c) # path = [row col]
pylab.plot(path[:,1],path[:,0],'b-')
pylab.axis('image')
pylab.savefig("raindrop_shan.png")
pylab.show()