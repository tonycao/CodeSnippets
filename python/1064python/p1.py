
import math


m = input("Enter the month:")

if m == "March":
    m_int = 3
elif m == "April":
    m_int = 4
elif m == "May":
    m_int = 5
elif m == "June":
    m_int = 6
elif m == "July":
    m_int = 7
elif m == "August":
    m_int = 8
elif m == "September":
    m_int = 9
elif m == "October":
    m_int = 10
elif m == "November":
    m_int = 11
elif m == "December":
    m_int = 12
elif m == "January":
    m_int = 13
elif m == "February":
    m_int = 14


d = int(input("Enter the day:"))


y = int(input("Enter the year:"))
if m_int == 13 or m_int == 14:
    y = y - 1

z = d + math.floor (26 * (m_int+1) / 10) + y + math.floor(y/4) + 6 * math.floor(y/100) + math.floor(y/400)

w = ((z + 5) % 7) + 1

if w == 1:
    week = "Monday"
elif w == 2:
    week = "Tuesday"
elif w == 3:
    week = "Wednesday"
elif w == 4:
    week = "Thursday"
elif w == 5:
    week = "Friday"
elif w == 6:
    week = "Saturday"
elif w == 7:
    week = "Sunday"


print (week)



new = input("Would you like to enter another date(y/n):")
while new != "n":
    m = input("Enter the month:")

    if m == "March":
        m_int = 3
    elif m == "April":
        m_int = 4
    elif m == "May":
        m_int = 5
    elif m == "June":
        m_int = 6
    elif m == "July":
        m_int = 7
    elif m == "August":
        m_int = 8
    elif m == "September":
        m_int = 9
    elif m == "October":
        m_int = 10
    elif m == "November":
        m_int = 11
    elif m == "December":
        m_int = 12
    elif m == "January":
        m_int = 13
    elif m == "February":
        m_int = 14


    d = int(input("Enter the day:"))


    y = int(input("Enter the year:"))
    if m_int == 13 or m_int == 14:
        y = y - 1

    z = d + math.floor (26 * (m_int+1) / 10) + y + math.floor(y/4) + 6 * math.floor(y/100) + math.floor(y/400)

    w = ((z + 5) % 7) + 1

    if w == 1:
        week = "Monday"
    elif w == 2:
        week = "Tuesday"
    elif w == 3:
        week = "Wednesday"
    elif w == 4:
        week = "Thursday"
    elif w == 5:
        week = "Friday"
    elif w == 6:
        week = "Saturday"
    elif w == 7:
        week = "Sunday"



    print (week)

    new = input("Would you like to enter another date(y/n):")


# <include a description of the purpose of this file/project/package>
#
# @author <name and surname> (your VT PID)
# @date <the date>
#
# Virginia Tech Honor Code Pledge
# On my honor:
#
# - I have not discussed the Python language code in my program with
# anyone other than my instructor or the teaching assistants
# assigned to this course.
# - I have not used Python language code obtained from another student,
# or any other unauthorized source, either modified or unmodified.
# - If any Python language code or documentation used in my program
# was obtained from another source, such as a text book of coarse
# notes, that has been clearly noted with a proper citation in
# the comments of my program.
# - I have not designed this program in such a way as to defeat or
# interfere with the normal operation of the Web-Cat Server.
#
# <Yin Yuan>









