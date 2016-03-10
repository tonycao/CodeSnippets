P <- c(1:99)/100
EP <- rep(0, length(P))
N <- 30
Nt <- 1000# number of trials for each "P"
  
# adpot a beta prior
alpha <- 1
beta <- 1

ep <- rep(0, Nt)
for (i in 1:length(P)) {
  count <- 0
  for (j in 1:Nt) {
    # simulate from Bernoulli(p) with N=30
    rb <- rbinom(N, 1, P[i])
    # compute CI for p
    lci = qbeta(0.05, shape1=sum(rb)+alpha, shape2=N-sum(rb)+beta)
    uci = qbeta(0.95, shape1=sum(rb)+alpha, shape2=N-sum(rb)+beta)
    # compute "real" coverage for "p"
    if (lci<P[i] && uci > P[i] ) {
      count <- count+1
    }
  }
  EP[i] <- count/1000
}

plot(P,EP,type="l",main="Credible Interval for Bayesian coverage")
abline(h=0.90)