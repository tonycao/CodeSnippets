
def decode(lines):
    result = list()
    str = ''
    for line in lines:
        line = line.strip().split()
        for i in range(0, int(len(line)/2)):
            str = str + chr(int(line[2*i]) + int(line[2*i+1])) 
        str = str + ' '
        #print(str)
            
        if line == []:
            #print(str)
            result.append(str)
            str = ''
            
    result.sort()
    return result


# start decoding
file_name = input('Enter filename:')
decode_file=open(file_name,'r')

lines = decode_file.readlines()
print('Decoded messages:')

result = decode(lines)
for line in result:
    print(line)
    
# <include a description of the purpose of this file/project/package>
#
# @author <Yin Yuan> (905667279)
# @date <29th, April>
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