p <- 0.01
x<-rbinom(1,30,0.01)

count<-0

p_hat<-x/30
sigma_hat<-sqrt(x/30*(1-x/30))
CI_lower<-p_hat-1.96*sqrt(sigma_hat)
CI_higher<-p_hat+1.96*sqrt(sigma_hat)


if (p > CI_lower & p < CI_higher) {
  count <- 1
} else count <- 0
