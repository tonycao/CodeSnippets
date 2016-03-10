#hw3.3

flag = 0
x0 = 0
esp = .00000001

while(flag == 0) {
  x = x0 - (3*exp(x0) - 4*cos(x0))/(3*exp(x0) + 4*sin(x0))
  tolerance = abs(x-x0)
  if (tolerance <= esp) {
    flag = 1
  }
  else {
    x0 = x
  }
}

print(x)