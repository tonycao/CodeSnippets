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
import pylab
from A4Func import *

terrain = np.load('elevation.npy')

#Q1. Draw the terrain 
pylab.figure()
pylab.imshow(terrain, cmap = pylab.cm.gray)
pylab.savefig('terrain.png')

#Q2. Your code to calculate the pit locations and draw pits on the terrain


#Q3. Your code to calculate the peak locations and draw peaks on the terrain


#Q4. Print the number of peaks and the number of pits
num_pits = 0 # replace with your code here
num_peaks = 0 # replace withyour code here

print 'Number of peaks:',num_peaks
print 'Number of pits:',num_pits

#Q5. Save this figure as 'peaksNPits.png'
pylab.axis('image')
pylab.savefig("peaksNPits.png")
pylab.close()

#Q6-Q9. Trace drop in the terrain

pylab.figure()
pylab.imshow( terrain, cmap=pylab.cm.gray ) 

point = np.array( pylab.ginput(1)[0] ) 
r = int( np.round( point[1] ) ) # an integer row index 
c = int( np.round( point[0] ) ) # an integer column index
print 'Clicked point at (row=',r,',col=',c,')...'

# Your code to calculate the trace and plot it in blue

pylab.axis('image')
pylab.savefig("raindrop.png")
pylab.close()