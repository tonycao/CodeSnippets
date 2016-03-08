import csv

def addGradeDict(file):
    grade_dict = {}
    for row in file:
        #tmplist = row.strip().split()
        fullname = row[0]+', '+row[1]
        if fullname in grade_dict:
            continue
        else:
            grade_dict[fullname] = row[2::]
    return grade_dict

def computeWeight(weights, assignments, selected):
    total_weight = 0.0
    if selected == '':
        total_weight = sum(float(x) for x in weights)
    else:
        for i in range(len(assignments)):
            if assignments[i].lower().find(selected.lower()) != -1:
                total_weight += float(weights[i])
    return total_weight

def computeScore(weights, record, assignments, selected):
    total_score = 0.0
    total_score_selected = 0.0
    for i in range(len(assignments)):
        total_score += float(weights[i])*float(record[i])
        if assignments[i].lower().find(selected.lower()) != -1:
            total_score_selected += float(weights[i])*float(record[i])
    if selected == '':
        return total_score
    else:
        return total_score_selected

def printRecord(record, assignments, weights, selected, writefile):
    for i in range(len(assignments)):
        if assignments[i].lower().find(selected.lower()) != -1:
            print('{:16s}{:<15.1%}{:<5d}'.format(assignments[i], float(weights[i]), int(record[i])), file=writefile)

def generateReport(report, name, assign, outfilename, records, weights, assignments):
    w = open(outfilename, 'w')
    #total_weight = computeWeight(weights, assignments, '')
    total_weight_selected = computeWeight(weights, assignments, assign)
    #totalweighttest = sum(float(x) for x in weights[4::])

    if report == 'S':
        print('Summary Report', file=w)
        print('----------------------------------', file=w)

        count = len(records)
        average = 0.0
        #tweight = 0
        for key, val in records.items():
            total = 0.0
            total = computeScore(weights, val, assignments, assign)
            average += total
            print('{:15s}{:3.1%}/{:3.1%}{:8.1f}'.format(key, total/100, total_weight_selected, total/total_weight_selected), file=w)

        print('----------------------------------', file=w)
        print('{:15s}{:3.1%}/{:3.1%}{:8.1f}'.format('Class Average:', average/count/100, total_weight_selected, (average/count)/total_weight_selected), file=w)

    elif report == 'R':
        print("{}".format(name), file=w)
        print('----------------------------------', file=w)
        print('{:16s}{:14s}{:5s}'.format('Assignment', 'Weight', 'Grade'), file=w)
        #val = records[name]

        total_selected = 0.0
        count = len(records)
        average = 0.0
        for key, val in records.items():
            if key == name:
                total_selected = computeScore(weights, val, assignments, assign)
                printRecord(val, assignments, weights, assign, w)
            average += computeScore(weights, val, assignments, assign)
        print('----------------------------------', file=w)
        print('{:16s}{:3.1%}/{:3.1%}{:8.1f}'.format('Overall:', total_selected/100, total_weight_selected, total_selected/total_weight_selected), file=w)
        print('{:16s}{:3.1%}/{:3.1%}{:8.1f}'.format('Class Average:', average/count/100, total_weight_selected, (average/count)/total_weight_selected), file=w)

#if __name__ == '__main__':
# Read input file
print('Welcome to the CS1064 Grade Report program!')
filename = input('Enter the grades file: ')
f = open(filename, 'r')
r = csv.reader(f)
print('-------------------------------------------')

# Get assignments:
assignments = next(r, [])
assignments = assignments[2::]

# Get weights:
weights = next(r, [])
weights = weights[2::]
#totalweight = sum(float(x) for x in weights)

# Save recodes to dict
grade_dict = addGradeDict(r)

# Start loop
request = 'y'
while request == 'y':
    report = input('Generate a grade report for a single student(R)?\nOr summary for all students (S)?: ')
    print('-------------------------------------------')
    name = ''
    if report == 'R':
        name = input('Enter student name in the format Last, First: ')
    assign = input('Include only assignments containing (blank for all assignments): ')
    outfilename = input('Enter file name for report: ')

    generateReport(report, name, assign, outfilename, grade_dict, weights, assignments)
    print('Writing report to {}...'.format(outfilename))
    print('-------------------------------------------')

    request = input('Go again? (Y/N): ').lower()
    print('-------------------------------------------')


# generate grade reports for a student
#
# @author <Yin Yuan> (905667279)
# @date <3rd, May>
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
