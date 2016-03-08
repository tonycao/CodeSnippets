import numpy as np
from datetime import date

def average_rain( data ):
    week = np.zeros(len(data))

    for i in xrange(len(data)):
        week[i] = date(int(data[i,0]),int(data[i,1]),int(data[i,2])).weekday()

    weekday = np.logical_and(week >= 1, week <= 3)
    weekend = np.logical_or(week == 5, week == 6)
    weekend = np.logical_or(weekend, week == 0)

    rain_weekday = np.mean( data[weekday, 3] )
    rain_weekend = np.mean( data[weekend, 3] )
    
    return rain_weekday, rain_weekend, rain_weekday-rain_weekend


data = np.loadtxt('krdu-rain-2001-2010.csv', delimiter=',')

rain = average_rain(data)
delta = rain[2]
print "average rain for midweek = %.4f" % rain[0]
print "average rain for weekend = %.4f" % rain[1]
print "the difference = %.4f" % delta

cnt = 0
N = 1000

for i in xrange(N):
    np.random.shuffle(data[:,:3])
    rain = average_rain(data)
    if rain[2] > delta:
        cnt = cnt + 1
p = float(cnt)/N
print "p value = %.4f" % p
