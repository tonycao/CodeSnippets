import math
principal_str = input("Please enter the principal:")
principal_flo = float(principal_str)

year_str = input("Please enter the number of year:")
year_int = int(year_str)

rate_str = input("Please enter the interest:")
rate_flo = float(rate_str)
rate = rate_flo/100


balance = principal_flo * (1 + rate)** year_int

print("The final balance is:", balance)
