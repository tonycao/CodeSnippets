
n<-88
alpha=0.05
DECISION <- double(0)

for (i in 1:1000){
  x <- rnorm(n, mean=5, sd=1.5)
  y <- rnorm(m,mean=7,sd=1.5)
  DECISION[i] <- 0
  if (t.test(x,y)>qt(1-alpha/2,n+m-2)){
    DECISION[i] <- 1
  }
}

