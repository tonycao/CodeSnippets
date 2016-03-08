import string

swapstr = "Hello World!"
result = ""

for c in swapstr:
    if c.islower():
        result += c.upper()
       
    elif c.isupper():
        result += c.lower()
    else:
        result += c
        
print(result)

string1 = input("Enter a string: ")
string2 = input("Enter a string: ")

string1_changed = string1[1:-1]
string2_changed = string2[1:-1]

string3 = string1_changed + string2_changed
print(string3)

new_string3 = ""
for char in string3:
    if char.isalpha():
        new_string3 = new_string3 + char*3
        
print(new_string3)


# 6)
#function of encode:
def ROT13(line):
    """encode the line"""
    #shift_amount = 13
    count = 0
    encoded_str = ''
    for char in line:
        #count is the index of char, we need find the relationship between char
        # index number and the shift_amount index,'(count-1)%shift_amount' is 
        # used to get the index of shift_amount
        count += 1
        k = 13
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
    
string = input("Enter message: ")
string = string.strip()
result = ROT13(string)
print(result)
str = ROT13(result)
print(str)

# 7)
string1 = input("Enter a long string: ")
length = len(string1)
ntweet = int((length - 1) / 132) + 1;

for i in range(ntweet):
    print("({0:2d}/{1:2d})  ".format(i+1, ntweet), end="")
    if (i+1)*132 < length:
        print(string1[i*132 : (i+1) * 132])
    else:
        print(string1[i*132 : :])
    

