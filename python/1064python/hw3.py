

odd_str = input("Please input an odd number:")

odd_int = int(odd_str)


print('Hill:')

for num in range(odd_int + 1):
    if num%2 != 0:
        print('*'*num)

print('\n')




print('Triangle:')

count = 0
row_num = (odd_int + 1 )/2


for num in range(odd_int + 1):
    if num%2 != 0:
        count +=1
        space = row_num - count
        print(' '* int(space) +  '*'*num)



print('\n')




print('Hour Glass:')



odd_int = int(odd_str)


count = 0

for num in range (odd_int+1):
    if num%2 !=0:
        print(' '* int((num+1)/2-1) +'*'*int(odd_int-count*2))
        count+=1

count = 0
row_num = (odd_int + 1 )/2


for num in range(odd_int + 1):
    if num%2 != 0:
        count +=1
        space = row_num - count
        print(' '* int(space) +  '*'*num)

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


        
