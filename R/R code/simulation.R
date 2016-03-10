phi <- sapply(1:10000, function(iter) {
  z <- cumsum(rnorm(1000))
  x <- z[1:999]
  y <- z[2:1000]
  return(sum(x*y)/sum(x*x))
})

hist(phi, xlim=c(.9,1.1))
abline(v=mean(phi), col='red', lty=2)

z <- cumsum(rnorm(1000))
x <- z[1:999]
y <- z[2:1000]
model <- lm(y~x-1)
summary(model)