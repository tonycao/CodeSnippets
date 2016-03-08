number_str = input("Number:")
the_sum = 0

while number_str!= ".":
    number = int(number_str)
    if number%2 ==1:
        print ("Error, only even numbers please.")
        number_str = input ("Number:")
        continue
    the_sum += number
    number_str = input("Number:")
    print ("The sum is:", the_sum)
 
