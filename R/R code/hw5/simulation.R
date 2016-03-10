## simulation for x~N(5, 16), CI for mean when variance is 4
mu<-5
sigma<-2
n<-200
nsim<-1000

l<-rep(0, nsim)
r<-rep(0, nsim)


for (i in 1:nsim) {
  set.seed(i)
  x<-rnorm(n, mu, sigma)
  l[i]<-mean(x)-qnorm(0.975)*sqrt(sigma^2/n)
  r[i]<-mean(x)+qnorm(0.975)*sqrt(sigma^2/n)
}

# CI coverage
print(mean((l<=mu)&(r>=mu)))
# CI length
print(mean(r)-mean(l))

## simulation for x~N(5, 16), CI for mean when variance is unknow
mu<-5
sigma<-2
n<-200
nsim<-1000

for (i in 1:nsim) {
  set.seed(i)
  x<-rnorm(n, mu, sigma)
  l[i]<-mean(x)-qt(0.975,n-1)*sqrt(var(x)/n)
  r[i]<-mean(x)+qt(0.975,n-1)*sqrt(var(x)/n)
}

# CI coverage
print(mean((l<=mu)&(r>=mu)))
# CI length
print(mean(r-l))

## simulation for x~N(5, 16), CI for variance
mu<-5
sigma<-2
n<-200
nsim<-1000

for (i in 1:nsim) {
  set.seed(i)
  x<-rnorm(n, mu, sigma)
  l[i]<-(n-1)*var(x)/qchisq(0.975,n-1)
  r[i]<-(n-1)*var(x)/qchisq(0.025,n-1)
}

# CI coverage
print(mean((l<=sigma^2)&(r>=sigma^2)))
# CI length
print(mean(r-l))