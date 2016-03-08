'''Assignment 2 Water Data'''

# Author: (your name here)
# Collaborators: (put anyone you worked with here)

# This script will run as is but, of course, it doesn't yet produce
# the desired results. Your mission is to modify it to get the outputs
# requested.

import numpy as np
import pylab

# Make sure all the plots are closed
pylab.close('all')

# Read the data

# depth: a 276 by 2 array with depth of Jordan and Falls lakes
# for each month from Jan 1985 to Dec 2007, which is 23 years.
# Data that is not available is NaN.
depth = np.loadtxt('depth.txt')

# rain: a 276x2 array with total rainfall in inches for each month
rain = np.loadtxt('rain.txt')

# hawgage: a 365x4 array of daily average river or lake height (ft) at
# Haw River, Bynum, and above & below the Jordan Lake Dam by Moncure.
# (These sites are listed upstream to downstream, but the gauges are
# not in that order.)
hawgage = np.loadtxt('hawgage.txt')

# hawrain: a 365x2 array of daily rainfall (in) measured at two
# rain gauges from 29 Aug 2007 - 28 Aug 2008.
hawrain = np.loadtxt('hawrain.txt')

# 1. Plot a line graph of depths for both lakes.
# (Is there an obvious yearly cycle?)

# create a new figure for this part
pylab.figure(1)

# put the appropriate call here to plot the depths
pylab.plot(depth)
# these show how to label the figure
pylab.title('Depth of Jordan and Falls lakes')
pylab.ylabel('Depth (feet)')
pylab.xlabel('Months starting with Jan 1985')
pylab.savefig('Fig1.png')

# 2. The targets for Jordan and Falls lakes are 216ft and 251.5ft,
# respectively. For how many months was each lake over its target?

# include the code here to compute and print the answer

JordanOverTarget = np.sum(depth[:,0]>216) # replace this with some expression
print 'Months Jordan lake was over its target =', JordanOverTarget

FallsOverTarget = np.sum(depth[:,1]>251.5)  # replace this with some expression
print 'Months Falls lake was over its target =', FallsOverTarget

# 3. Plot the rain in August as a line graph over years for both lakes.

# start a new figure for the this part
pylab.figure(3)

# include code to plot the figure with some nice labels as above

pylab.title('Rain in August for Jordan and Falls lakes')
pylab.savefig('Fig2.png')

# 4. Compute the average height that Falls Lake is relative to its target
# for each month over the 23 years from 1985-2007, and display as bar
# chart with a bar for each month. Plot the line for 2007 in red on
# top of this bar chart.

# start a new figure for the this part
pylab.figure(4)

# put code here to compute FallsByMonth

# then you can create a bar chart of it like this:
# pylab.bar(np.arange(1,13), FallsByMonth, align='center')

# then plot a line in red on top of that with a call to plot like this:
# pylab.plot(np.range(1,13), something_goes_here, 'r')

pylab.title('Average Falls lake depth 85-07, and line for 2007')
pylab.ylabel('Height above target(ft)')
pylab.xlabel('Month')
pylab.savefig('Fig3.png')

# 5. Determine how many days had more than 1 in of precipitation at
# both two sites in hawrain, and how many days had less than 1/4 in.

# your code goes here

print 'Number of days both lakes had more than one inch =' # put expression here
print 'Number of days both lakes had less than 1/4 inch =' # put expression here

# 6. Plot line graphs showing the cumulative amount of rain over the
# past year at both sites.  Which of the two locations (1 or 2)
# received the most rain?

# You'll find the numpy function "cumsum" useful for this one
# put your code here

# start a new figure for the this part
pylab.figure(6)

pylab.title('Cumulative Rainfall')
pylab.xlabel('Days since 28Aug07')
pylab.ylabel('Cumulative rainfall (in)')
pylab.savefig('Fig4.png')

# determine which site had the most total rain -- the np.argmax function will help
# this print statement should print 1 or 2 

print 'The site with more total rain is' #put somehting here

# 7. Determine the lowest height for each gauge, and create an array
# of adjusted heights by subtracting the corresponding lowest heights.
# Plot these adjust heights as a line graph.

# compute the adjusted heights

# start a new figure for the this part
pylab.figure(7)

# and then plot them using commands similar to above

pylab.title('Adjusted gauge heights')
pylab.xlabel('Days since 28Aug07')
pylab.ylabel('Height above min (ft)')
pylab.savefig('Fig5.png')

# 8. Determine the maximum increase and maximum decrease in height
# from one day to the next for each of the four gauges in hawgage.

# your code goes here

print 'Maximum one-day change in height ='  # put something here
print 'Minimum one-day change in height ='  # and something else here
