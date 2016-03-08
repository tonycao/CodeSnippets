import string


#function of encode:
def encode(line, shift_amount):
    """encode the line"""
    count = 0
    encoded_str = ''
    for char in line:
        #count is the index of char, we need find the relationship between char
        # index number and the shift_amount index,'(count-1)%shift_amount' is 
        # used to get the index of shift_amount
        count += 1
        k = int(shift_amount[(count-1)%len(shift_amount)])
        if char.isalpha():
            if char.isupper():
                char_cal=ord(char)-ord('A')
                char_upper= chr(int((char_cal+k)%26)+ord('A'))
                encoded_str = encoded_str + char_upper
            elif char.islower():
                char_cal2=ord(char)-ord('a')
                char_lower=chr(int((char_cal2+k)%26)+ord('a'))
                encoded_str = encoded_str + char_lower
        else: encoded_str = encoded_str + char
    return encoded_str


#function of decode:
def decode(line, shift_amount):
    """decode the line"""
    count = 0
    decoded_str = ''
    for char in line:
        #count is the index of char, we need find the relationship between char
        # index number and the shift_amount index,'(count-1)%shift_amount' is 
        # used to get the index of shift_amount
        count += 1
        k = int(shift_amount[(count-1)%len(shift_amount)])
        if char.isalpha():
            if char.isupper():
                char_cal=ord(char)-ord('A')
                char_upper= chr(int((char_cal-k)%26)+ord('A'))
                decoded_str = decoded_str + char_upper
            elif char.islower():
                char_cal2=ord(char)-ord('a')
                char_lower=chr(int((char_cal2-k)%26)+ord('a'))
                decoded_str = decoded_str + char_lower
        else: decoded_str = decoded_str + char
    return decoded_str


while True:
    #set up variables
    file_name = input('Enter input file:')
    shift_amount = input('Enter shift amounts:')
    shift_amount = shift_amount.replace(' ', '')
    code_file = open(file_name,'r')

    question=input('Encode (E) or Decode (D)?')

    #senario of encode:
    #count=1

    if question == 'E':
    #add hokie at the beginning and end and middle of each line in the file
        for line in code_file:
            line = line.strip()
            line = line.replace('e','zw')
            line = 'hokie'+ line[:int(len(line))//2]+'hokie'+ line[int(len(line))//2:]+'hokie'
            #print(line)
            #call the function encode
            line_output = encode(line,shift_amount)
            print(line_output)
            #count+=1

    if question == 'D':
        for line in code_file:
            line_output = decode(line, shift_amount)
            line = line_output.replace('hokie','')
            line = line.replace('zw','e')
            line = line.strip()
            print(line)
            #count += 1


    ask_str = input('Go again?(Y/N):')

    if ask_str == 'N':
        break

# <include a description of the purpose of this file/project/package>
#
# @author <Yin Yuan> (905667279)
# @date <13/04/2015>
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