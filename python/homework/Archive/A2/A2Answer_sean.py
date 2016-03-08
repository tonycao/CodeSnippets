##  Assignment 2 - Analyzing water

## Author: Sean Curtis
## Collaborators: None
## Time spent (hours): N/A

## In this assignment, we're going to visualize and analyze data to answer
##   meaningful questions.  Some of the framework you need is in place, you
##   have to fill in the gaps.  

import numpy as np
import pylab as plt

# read the data

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
# rain gauges from 29 Aug 07 - 28 Aug 08.
hawrain = np.loadtxt('hawrain.txt')

## QUESTION 1
# 1. Plot a line graph of depths for both lakes.

plt.plot( depth )

# these show how to label the figure
plt.title('Depth of Jordan and Falls lakes')  # the title of the figure
plt.ylabel('Depth (feet)')                    # label for the y-axis
plt.xlabel('Months starting with Jan 1985')   # label for the x-axis
plt.savefig('Fig1.png')                       # the saved output figure
plt.close()                                   # close this plot so it doesn't interfere later

## QUESTION 2
# 2. The targets for Jordan and Falls lakes are 216ft and 251.5ft, respectively.
#    For how many months was each lake over its target?

jordanTgt = 216
fallsTgt = 251.5
targets = np.array([ jordanTgt, fallsTgt ] )
overTgt = depth > targets
overTgtCount = np.sum( overTgt, axis=0 )

print 'Months Jordan lake exceeded its target depth:', overTgtCount[0]
print 'Months Falls Lake exceeded its target depth:', overTgtCount[1]

## QUESTION 3
# 3. Plot the rain in August as a line graph over years for both lakes.

augRain = rain[ 7::12, : ]
plt.plot( augRain )

plt.title('Rain in August for Jordan and Falls lakes')
plt.savefig('Fig2.png')
plt.close()

## QUESTION 4
# 4. Compute the average height that Falls Lake is above its target
# for each month over the 23 years from 1985-2007, and display as bar
# chart with a bar for each month.  Plot the line for 2007 in red on
# top of this bar chart.

monthVsYear = np.reshape( depth[ :, 1 ], (-1, 12 ) )
FallsByMonth = np.mean( monthVsYear, axis=0 )
FallsByMonth -= fallsTgt
plt.bar( np.arange(1, 13), FallsByMonth, align='center')
year2007 = depth[-12:, 1] - fallsTgt
plt.plot( np.arange(1, 13), year2007, 'r')

plt.title('Average Falls lake depth 85-07, and line for 2007')
plt.ylabel('Height above target(ft)')
plt.xlabel('Month')
plt.savefig('Fig3.png')
plt.close()

## QUESTION 5
# 5. Determine how many days had more than 1 in of precipitation at
# the two sites in hawrain, and how many days had less than 1/4 in.

grtrOne = hawrain > 1
print 'Number of days either lake had more than one inch', np.sum( np.sum( grtrOne, axis=1 ) > 0 )
qrtr = hawrain < 0.25
print 'Number of days either lake had less than 1/4 inch:',  np.sum( np.sum( qrtr, axis=1 ) > 0 )


## QUESTION 6
# 6. Plot line graphs showing the cumulative amount of rain over the
# past year at both sites.  Which of the two locations (1 or 2)
# received the most rain?

cumRain = np.cumsum( hawrain, 0 )
plt.plot( cumRain )
maxIndex = np.argmax(cumRain[ -1, : ])

plt.title('Cumulative Rainfall')
plt.xlabel('Days since 28Aug07')
plt.ylabel('Cumulative rainfall (in)')
plt.savefig('Fig4.png')
plt.close()

# !!!  Determine which site had the most total rain -- the np.argmax function will help !!!
# !!!       This print statement should print 1 or 2 (be careful there....)             !!!

print 'The site with more total rain:', maxIndex + 1

## QUESTION 7
# 7. Determine the lowest height for each gauge, and create an array
# of adjusted heights by subtracting the corresponding lowest heights.
# Plot these adjust heights as a line graph.

minHeight = hawgage.min( 0 )
adjHeight = hawgage - minHeight
plt.plot( adjHeight )

plt.title('Adjusted gauge heights')
plt.xlabel('Days since 28Aug07')
plt.ylabel('Height above min (ft)')
plt.savefig('Fig5.png')
plt.close()

## QUESTION 8
# 8. Determine the maximum increase and maximum decrease in height
# from one day to the next for each of the four gauges in hawgage.

delta = np.diff( hawgage, axis=0 )
minDelta = delta.min( 0 )
maxDelta = delta.max( 0 )

print 'Maximum one-day change in height:', maxDelta
print 'Minimum one-day change in height:', minDelta


## YOUR THOUGHTS
##  Type in some of your thoughts about this assignment below.  Make sure that it all begins with
##  pound signs (#) or your python script won't run at all.