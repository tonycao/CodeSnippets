odd_str = input("Please input an odd number:")

odd_int = int(odd_str)


count = 0

for num in range (odd_int+1):
    if num%2 !=0:
        print(' '* int((num+1)/2-1) +'*'*int(odd_int-count*2))
        count+=1
