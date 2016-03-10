#length of vector
lv = 1000

# test 1
DECISION <- double(0)
n <- 88
m <- 88
alpha = 0.05

for(i in 1:lv) {
  x <- rnorm(n, mean=5, sd=1.5)
  y <- rnorm(m, mean=5, sd=1.5)
  t.stat <- tstatistic(x, y)
  n.reject = 0
  if (abs(t.stat) > qt(1-alpha/2, n+m-2)) {
    n.reject = 1
  }
  DECISION[i] <- n.reject
}

prop = sum(DECISION)/lv
print(prop)

# test 2
DECISION2 <- double(0)

for(i in 1:lv) {
  x <- rnorm(n, mean=5, sd=1.5)
  y <- rnorm(m, mean=7, sd=1.5)
  t.stat <- tstatistic(x, y)
  n.reject = 0
  if (abs(t.stat) > qt(1-alpha/2, n+m-2)) {
    n.reject = 1
  }
  DECISION2[i] = n.reject
}

prop2 = sum(DECISION2)/lv
print(prop2)