#!/usr/bin/env python

rates = list()
s = list()
m = list()
f = list()
h = list()

def user_input(filename):
    #rates.append(0)
    s.append(0)
    m.append(0)
    f.append(0)
    h.append(0)

    filing_status = input('Enter filing status (S/M/F/H): ')
    total_income, total_deductions = input('Enter Total Income and Deductions: ').split()
    total_income = float(total_income)
    total_deductions = float(total_deductions)
    taxable_income = total_income - total_deductions

    infile = open(filename, "r")
    lines = infile.readlines()

    x = 1
    while x < len(lines):
        line = lines[x].strip().split()
        if x == 1:
            for rate in line:
                rates.append(float(rate))
        elif x == 4:
            for income in line:
                s.append(float(income))
        elif x == 7:
            for income in line:
                m.append(float(income))
        elif x == 10:
            for income in line:
                f.append(float(income))
        elif x == 13:
            for income in line:
                h.append(float(income))
        x += 3

    #print rates, s, m, f, h

    return filing_status, taxable_income

def calculate(filing_status, taxable_income):
    upper_index = 0
    total_tax = float(0)
    if filing_status == 'S':
        for income in s:
            if taxable_income > income:
                upper_index = s.index(income)
        for index in range(0, upper_index):
            total_tax += (s[index + 1] - s[index]) * rates[index]
        total_tax += (taxable_income - s[upper_index]) * rates[upper_index]
        return total_tax/100

    if filing_status == 'M':
        for income in m:
            if taxable_income > income:
                upper_index = m.index(income)
        for index in range(0, upper_index):
            total_tax += (m[index + 1] - m[index]) * rates[index]
        total_tax += (taxable_income - m[upper_index]) * rates[upper_index]
        return total_tax/100

    if filing_status == 'F':
        for income in f:
            if taxable_income > income:
                upper_index = f.index(income)
        for index in range(0, upper_index):
            total_tax += (f[index + 1] - f[index]) * rates[index]
        total_tax += (taxable_income - f[upper_index]) * rates[upper_index]
        return total_tax/100

    if filing_status == 'H':
        for income in h:
            if taxable_income > income:
                upper_index = h.index(income)
        for index in range(0, upper_index):
            total_tax += (h[index + 1] - h[index]) * rates[index]
        total_tax += (taxable_income - h[upper_index]) * rates[upper_index]
        return total_tax/100

#if __name__ == '__main__':
print ('Welcome to the CS1064 Tax Calculator program!')
filename = input('Enter the file storing the tax brackets: ')
request = 'yes'
while request == 'yes':
    filing_status, taxable_income = user_input(filename)
    total_tax = calculate(filing_status, taxable_income)
    print('Total Tax: ${:.2f}'.format(total_tax))
    request = input('Would you like to calculate another person\'s taxes? (yes/no): ').lower()


# <include a description of the purpose of this file/project/package>
#
# @author <Yin Yuan> (905667279)
# @date <27th, April>
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
