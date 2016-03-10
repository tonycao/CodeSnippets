P <- c(1:99)/100
N <- 30    
EP <- rep(0, length(1:99)) 
Nt <- 1000 # number of trials for each "P"

# function for compute CI for "p"
binomCI=function(y, p, alpha1, alpha2) {
  z1<-abs(qnorm(alpha1))
  z2<-abs(qnorm(1-alpha2))
  nn<-length(y)
  phat<-sum(y)/nn
  se<-sqrt(phat*(1-phat)/nn)
  return(c(phat-z1*se, phat+z2*se))
}

for (i in 1:length(P)) {
  print(P[i])
  count<-0
  for (times in 1:Nt) {
    # generate random numbers with Bernoulli distribution
    rb<-rbinom(N, 1, P[i])
    # compute CI for "p"
    CI<-binomCI(rb, P[i], 0.05, 0.05)
    # count number of success
    if (CI[1]<=P[i] & CI[2]>=P[i]) {
      count<-count+1
    }
  }
  # record ratio of success
  EP[i]<-count/Nt
}

plot(P, EP, type="l", xlab="Prob of success", ylab="Real coverage prob")
abline(h=0.9)
