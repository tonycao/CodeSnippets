import random
import math

def throw_dice():
    return random.randint(1, 6)


# returns the average of the numbers in list "numbers" 
def compute_average(numbers):
    sum = 0
    for num in numbers:
        sum += int(num)
        
    return sum / len(numbers)


    
# computes the variance of the numbers in list "numbers"
# must use compute_average()!
def compute_variance(numbers):
    mean = compute_average(numbers)
    variance = 0
    for num in numbers:
        variance += pow(num - mean, 2)
    return variance / len(numbers)

# computes the standard deviation of the elements in list "numbers"
# must use compute_variance()!
def compute_stddev(numbers):
    variance = compute_variance(numbers)
    return math.sqrt(variance)


# Main program. We'll be writing our program inside of a function this time.
# Write the code to test your other functions (compute_average, etc)
# inside of this function.
def main():
    seed = int(input("Enter seed: "))
    random.seed(seed)
    
    print("Generating 10 random numbers from 1 to 6...")
    random_numbers = [throw_dice() for x in range(0, 10)]

    # Your test code here, i.e. call the functions above.
    print("The 10 numbers are: ", end="")
    for element in random_numbers:
        print(element, " ", end= " ")
    
        
    print("The average is: ", end="")
    average = compute_average(random_numbers)
    print(average)
    
    print("The std. deviation is: ", end="")
    std = compute_stddev(random_numbers)
    print(std)
    
    print("The variance is: ", end="")
    var = compute_variance(random_numbers)
    print(var)



# This if statement us important, don't remove or move it.
# I'd just ignore it.
if __name__ == "__main__":
    main()

# <include a description of the purpose of this file/project/package>
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