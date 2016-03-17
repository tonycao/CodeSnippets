# initalize parameters
t = 100
lambda = 0.5 # rate for possion process
alpha = 2 # decrasing coefficient
dmin = 100 # min val for shock
dmax = 200 # max val for shock

# shock D is a uniform(dmin, dmax) thus expectation is (dmin + dmax) / 2
# R. V. D(t) = sum_1^Nt Di exp(-alpha(t-Si))
# Si from S = sort(runif(N, min = 0, max = t))
# do snum times simulations, and each time we sample samplenum many Dt to compute expectation of it.
snum = 100
samplenum = 1000
Dt = rep(NA, nrow =1, ncol = samplenum)
EXPDt = rep(NA, nrow =1, ncol = snum)

Expsim = function(snum, samplenum, lambda, t, alpha, dmin, dmax)
{
  Dt = rep(NA, nrow =1, ncol = samplenum)
  EXPDt = rep(NA, nrow =1, ncol = snum)
  
  for (j in 1:snum){
    for (i in 1:samplenum){
      Nt = rpois(1, lambda = lambda * t)
      Si = sort(runif(Nt, min = 0, max = t))
      Di = runif(Nt, min = dmin, max = dmax) #rexp(Nt, rate = Pulsrate)
      Dt[i] = sum(Di * exp(-alpha * (t - Si)))
    }
    EXPDt[j] = mean(Dt)
  }
  return(EXPDt)
}

# expectation based on theorem
Exptheor = lambda * (dmin + dmax) / (2 * alpha) * (1 - exp(-alpha * t))
# Difference
Expsi =  Expsim(snum, samplenum, lambda, t, alpha, dmin, dmax)
Diff = Expsi - Exptheor
# plot result
plot(Expsi, typ='l',main = 'expectation in simulation')
abline(h = Exptheor, col = 'red')

plot(Diff, typ='l',main = 'Difference')
abline(h = 0, col = 'blue')
