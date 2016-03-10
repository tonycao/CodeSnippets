library('MASS')
library(mvtnorm)

## Problem 1 Part a: 
sigma <- diag(2)
m1 <- mvrnorm(n=5, c(1, 0), sigma)
m2 <- mvrnorm(n=5, c(0, 1), sigma)
ms <- rbind(m1, m2)

csamples <- vector()
#csamples <- sample(1:10, 100, replace=TRUE) # floor(runif(100, min=1, max=11))

x <- matrix(, ncol = 2, nrow = 100)
for (i in 1:100) {
  csamples[i]  <- sample(1:10, 1, replace=TRUE)
  x[i,] <- mvrnorm(n = 1, ms[csamples[i],], sigma/5)
}

# class labels
#msamples[msamples<=5] <- 0
#msamples[msamples>5] <- 1
y <- csamples
y[y<=5] <- 0
y[y>5] <-1


GS <- 800 # put data in a Gs x Gs grid
XLIM <- range(x[,1])
tmpx <- seq(XLIM[1], XLIM[2], len=GS)

YLIM <- range(x[,2])
tmpy <- seq(YLIM[1], YLIM[2], len=GS)

newx <- expand.grid(tmpx, tmpy)

plot(x, col=y+1, xlab="X1", ylab="X2", main="Simulated data from Gaussian Mixture Model", xlim=XLIM, ylim=YLIM)
#abline(b,m)
#title("Linear regression")



## Problem 1 Part b 
# linear regression
X1 <- x[,1]
X2 <- x[,2]
linear.fit <- lm(y~X1+X2)
summary(linear.fit) # show results

m <- -linear.fit$coef[2]/linear.fit$coef[3]
b <- (0.5 - linear.fit$coef[1])/linear.fit$coef[3]

# prediction on grid
yhat <- predict(linear.fit, newdata=data.frame(X1=x[,1],X2=x[,2])); yhat <- as.numeric(yhat>0.5)
cols <- y+1

#plot(x, col=y+1, xlab="X1", ylab="X2", main="Simulated data from Gaussian Mixture Model", xlim=XLIM, ylim=YLIM)
abline(b,m)

# false positive and false negative rates
truepos <- sum(y[yhat==1])
falsepos <- sum(y[yhat==0])
falseneg <- sum(-y[yhat==1]+1)
trueneg <- sum(-y[yhat==0]+1)

FPR <- falsepos/(falsepos + trueneg)
FNR <- falseneg/(falseneg + truepos)

#print(paste("False Positive Rate: ", FPR) )
#print(paste("False Negtive Rate: ", FNR) )



## Problem 3 Bayes's Optimal Seperating Boundary

# Bayes classifier
# probability of Y given X
p <- function(x) {
  p0 <- mean(dnorm(x[1], m1[,1], 1/5) * dnorm(x[2], m1[,2], 1/5))
  p1 <- mean(dnorm(x[1], m2[,1], 1/5) * dnorm(x[2], m2[,2], 1/5))
  p1/(p0+p1)
}

#bayesrule <- apply(newx, 1, p)

#plot(x, xlab="X1", ylab="X2", xlim=XLIM, ylim=YLIM, type="n")
#points(x, col=colshat, pch=".")
#contour(tmpx, tmpy, matrix(round(bayesrule),GS,GS), levels=c(1,2), add=TRUE, col='blue', drawlabels=FALSE)
#points(x, col=cols)
#title("Bayes rule")
#dev.off()


# false positive and false negative rates
yhatbayes <- as.numeric(apply(x, 1, p)>0.5)
truepos <- sum(y[yhatbayes==1])
falsepos <- sum(y[yhatbayes==0])
falseneg <- sum(-y[yhatbayes==1]+1)
trueneg <- sum(-y[yhatbayes==0]+1)

FPRbayes <- falsepos/(falsepos + trueneg)
FNRbayes <- falseneg/(falseneg + truepos)

#print(paste("False Positive Rate: ", FPRbayes) )
#print(paste("False Negtive Rate: ", FNRbayes) )




f <- function(x, m) {
  out<-numeric(nrow(x))
  for (i in seq_len(nrow(m)))
    out<-out + dmvnorm(x, m[i,], diag(2)/5)
  out
}

# display coutours of the class-conditional densities
dens <- local({
  x <- y <- seq(-3, 4, len = 800)
  f1 <- outer(x, y, function(x, y) f(cbind(x, y), m1))
  f2 <- outer(x, y, function(x, y) f(cbind(x, y), m2))
  list(x = x, y = y, f1 = f1, f2 = f2)
})


# find which points are on the Bayes decision boundary
eq <- local({
  f1 <- dens$f1
  f2 <- dens$f2
  pts <- seq(-3, 4, len=800)
  eq <- which(abs((dens$f1 - dens$f2)/(dens$f1 + dens$f2)) < 5e-3, arr.ind = TRUE)
  eq[,1] <- pts[eq[,1]]
  eq[,2] <- pts[eq[,2]]
  eq
})


points(eq, pch=16, cex=0.3, col = 'green')


## Problem 4 m's are unknow, but subclass know
# estimate the 10 m's using data with MLE, which is the sample mean

mh <- matrix(0, 10, 2)
for (i in 1:10) {
  l <- which(csamples==i)
  mh[i,] <- colMeans(x[l,])
}

mh1 <- mh[1:5,]
mh2 <- mh[6:10,]

# Bayes classifier using mh

densmh <- local({
  x <- y <- seq(-3, 4, len = 800)
  f1 <- outer(x, y, function(x, y) f(cbind(x, y), mh1))
  f2 <- outer(x, y, function(x, y) f(cbind(x, y), mh2))
  list(x = x, y = y, f1 = f1, f2 = f2)
})


# find which points are on the Bayes decision boundary
eqmh <- local({
  f1 <- densmh$f1
  f2 <- densmh$f2
  pts <- seq(-3, 4, len=800)
  eq <- which(abs((densmh$f1 - densmh$f2)/(densmh$f1 + densmh$f2)) < 5e-3, arr.ind = TRUE)
  eq[,1] <- pts[eq[,1]]
  eq[,2] <- pts[eq[,2]]
  eq
})

points(eqmh, pch=16, cex=0.3, col = 'blue')

p2 <- function(x) {
  p0 <- mean(dnorm(x[1], mh1[,1], 1/5) * dnorm(x[2], mh1[,2], 1/5))
  p1 <- mean(dnorm(x[1], mh2[,1], 1/5) * dnorm(x[2], mh2[,2], 1/5))
  p1/(p0+p1)
}

yhatbayes2 <- as.numeric(apply(x, 1, p2)>0.5)
truepos <- sum(y[yhatbayes2==1])
falsepos <- sum(y[yhatbayes2==0])
falseneg <- sum(-y[yhatbayes2==1]+1) 
trueneg <- sum(-y[yhatbayes2==0]+1)

FPRbayes2 <- falsepos/(falsepos + trueneg)
FNRbayes2 <- falseneg/(falseneg + truepos)

#print(FPR, FNR, FPRbayes, FNRbayes, FPRbayes2, FNRbayes2)
