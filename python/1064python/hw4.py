

while True:
    original_str = input('Enter Message:')
    shift_str = input ('Enter shift amount:')
    shift_int = int(shift_str)
    question = input('Encode(E) or Decode (D)?')
# senario of encode
    if question == 'E':
    #if the entered message contains 'e', then change it/them into zw.
        original_str2 = original_str.replace('e','zw')
    #add 'hokie' on the two side of the message
        original_str3 = 'hokie'+ original_str2 + 'hokie'
    #add 'hokie' in the middle of the message
        middle_number = int(len(original_str3)/2)
        changed_str = original_str3[:middle_number] + 'hokie' + original_str3[middle_number:]

#initialized encoded_str
        encoded_str = ''
    
        for char in changed_str:
        #the sinario of alpha and upper letter
            if char.isalpha():
                if char.isupper():
                #we firstly get letter's utf value and then standardize their uft value to be 0-25
                #the standardization is conducted by minus ord('A'), which equal to 65.
                    char_cal = ord(char)-ord('A')
                #char_cal is ranged from 0-25, char_cal_shift is calculated by the formular
                # (x+k)%26, here 'shift_int'is k. By doing this, we got the encoded new numbers.
                    char_cal_shift = (char_cal +shift_int)%26
                #add 65 to the new numbers, we got the corresponding utf number
                    char_cal_shiftback = char_cal_shift + ord('A')
                    #using the uft number we got the corresponding letters.
                    Echar = chr (char_cal_shiftback)

                #senario fo lower letter
    
                elif char.islower():
                    char_cal = ord(char)-ord('a')
                    char_cal_shift = (char_cal +shift_int)%26
                    char_cal_shiftback = char_cal_shift + ord('a')
                    Echar = chr (char_cal_shiftback)
            else:
                Echar = char
    
            encoded_str = encoded_str + Echar
        
        print('Result:',encoded_str)


    decoded_str = ''

    if question == 'D':
        for char in original_str:
        #test whether it is alpha
            if char.isalpha():
                if char.isupper():
                    D_char_cal = ord(char) - ord('A')
                    D_char_cal_shift = (D_char_cal - shift_int)%26
                    D_char_cal_shiftback = D_char_cal_shift + ord('A')
                    Dchar = chr(D_char_cal_shiftback)
                elif char.islower():
                    D_char_cal = ord(char) - ord('a')
                    D_char_cal_shift = (D_char_cal - shift_int)%26
                    D_char_cal_shiftback = D_char_cal_shift + ord('a')
                    Dchar = chr(D_char_cal_shiftback)

            else:
                Dchar = char
            decoded_str = decoded_str + Dchar

        decoded_str2 = decoded_str.replace('hokie','')
        decoded_str3 = decoded_str2.replace('zw','e')
   
        print('Result:',decoded_str3)

    ask_str = input('Go again?(Y/N):')

    if ask_str == 'N':
        break

# <include a description of the purpose of this file/project/package>
#
# @author <Yin Yuan> (905667279)
# @date <29/03/2015>
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

