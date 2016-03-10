# RIDGE REGRESSION

# Model is E(Y) = 0 + 1 X1 + 1 X2 + e   with e~N(0,1)
# Three variables are measured: x1,x2,x3.  
#  x1 and x1 are U(0,1); x3=10 * X1 + unif(0,1).  
#   This causes corr(X1,X3)=sqrt(100/101)=0.995.
# We will fit OLS and ridge regressions to these data, 
#  use the data to select the "best" constant to add, 
#  and then evaluate the two regressions on a new test set.

# Ridge regression function, ridge.lm(), is on MASS package

library(MASS)

# Generating the data

set.seed(558562316)
N <- 20      # Sample size

x1 <- runif(n=N)
x2 <- runif(n=N)
x3 <- runif(n=N)
x3c <- 10*x1 + x3 # New variable
ep <- rnorm(n=N)
y <- x1 + x2 + ep 

# OLS fit of 3-variable model using independent x3
ols <- lm(y~ x1 + x2 + x3)
summary(ols)


# OLS fit of 3-variable model using correlated x3.
olsc <- lm(y~ x1 + x2 + x3c)
summary(olsc)


# Ridge regression using independent variables
ridge <- lm.ridge (y ~ x1+x2+x3, lambda = seq(0, .1, .001))
summary(ridge)
plot(ridge)

# Ridge regression using correlated variables
ridgec <- lm.ridge (y ~ x1+x2+x3c, lambda = seq(0, .1, .001))
plot(ridgec)
select(ridgec)

# Selection of constant is at endpoint.  Extend endpoint and try again
ridgec <- lm.ridge (y ~ x1+x2+x3c, lambda = seq(0, 1, .1))
plot(ridgec)
select(ridgec)

# Selection of constant is at endpoint.  Extend endpoint and try again
ridgec <- lm.ridge (y ~ x1+x2+x3c, lambda = seq(0, 10, .01))
plot(ridgec)
select(ridgec)

# Final model uses lambda=4.
ridge.final <- lm.ridge (y ~ x1+x2+x3c, lambda = 4)
ridge.final
summary(ridge.final)
# Create test data and compute predicted values for OLS and ridge.
#  There's no predict() method for "ridgelm" objects

test <- expand.grid(x1 = seq(.05,.95,.1), x2 = seq(.05,.95,.1), x3=seq(.05,.95,.1))
mu <- test$x1 + test$x2
test$x3c <- 10*test$x1 + test$x3
pred.ols <- predict(ols,newdata=test)   # y ~ X1 + X2 + X3
pred.olsc <- predict(olsc,newdata=test) # y ~ X1 + X2 + X3c
pred.ridge <- coef(ridge.final)[1] + coef(ridge.final)[2]*test[,1] + 
  coef(ridge.final)[3]*test[,2] + coef(ridge.final)[4]*test[,4]

MSPE.ols <- sum((pred.ols - mu)^2)/length(mu)
MSPE.olsc <- sum((pred.olsc - mu)^2)/length(mu)
MSPE.ridge <- sum((pred.ridge - mu)^2)/length(mu)

MSPE.ols
MSPE.olsc
MSPE.ridge


