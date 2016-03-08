import numpy as np
from datetime import date

def get_day_of_week(data):
    week = np.zeros(len(data))
    for i in xrange(len(data)):
        week[i] = date(int(data[i,0]),int(data[i,1]),int(data[i,2])).weekday()
    return week

def get_average_rain(week, rain):
    weekday = np.logical_and(week >= 1, week <= 3)
    weekend = np.logical_or(week == 5, week == 6)
    weekend = np.logical_or(weekend, week == 0)

    rain_weekday = np.mean( rain[weekday] )
    rain_weekend = np.mean( rain[weekend] )
    
    return rain_weekday, rain_weekend, rain_weekday-rain_weekend


data = np.loadtxt('krdu-rain-2001-2010.csv', delimiter=',')
rain = data[:,3]
week = get_day_of_week(data)
avg_rain = get_average_rain(week,rain)
delta = avg_rain[2]
print "average rain for midweek = %.4f" % avg_rain[0]
print "average rain for weekend = %.4f" % avg_rain[1]
print "the difference = %.4f" % delta

cnt = 0
N = 10000

for i in xrange(N):
    np.random.shuffle(week)
    avg_rain = get_average_rain(week,rain)
    if avg_rain[2] > delta:
        cnt = cnt + 1
p = float(cnt)/N
print "p value = %.4f" % p
