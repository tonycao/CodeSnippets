phi <- sapply(1:10000, function(iter) {
  z <- cumsum(rnorm(1000))
  x <- z[1:999]
  y <- z[2:1000]
  return (sum(x*y)/sum(x*x))
})

hist(phi, xlim=c(.9, 1.1))
abline(v=mean(phi), col='red', lty=2)

model <- spautolm(ft.SID74 ~ 1, data=nc,
                  listw=nb2listw(neighbors, zero.policy=T))
summary(model)

z <- cumsum(rnorm(1000))
x <- z[1:999]
y <- z[2:1000]
model <- lm(y~x-1)
summary(model)


m <- matrix(data=cbind(rnorm(30, 0), 
                       rnorm(30, 2), rnorm(30, 5)), nrow=30, ncol=3)

apply(m, 2, mean)

apply(m, 2, function(x) length(x[x<0]))

apply(m, 2, is.vector)

sapply(1:3, function(x) x^2)

sapply(1:3, function(x) mean(m[,x]))

sapply(1:3, function(x, y) mean(y[,x]), y=m)


## permutation test
# make up some 'true' data
carrier<-rep(c(0,1), c(100,200))
null.y<-rnorm(300)
alt.y<-rnorm(300, mean=carrier/2)

t.test(null.y~carrier, var.equal=TRUE)
t.test(alt.y~carrier, var.equal=TRUE)

null.diff<-mean(null.y[carrier==1])-mean(null.y[carrier==0])
alt.diff<-mean(alt.y[carrier==1])-mean(alt.y[carrier==0])

one.test <- function(x,y) {
  xstar<-sample(x)
  mean(y[xstar==1])-mean(y[xstar==0])
}

many.truenull <- replicate(1000, one.test(carrier, null.y))
many.falsenull <- replicate(1000, one.test(carrier, alt.y))

hist(many.truenull)
abline(v=null.diff, lwd=2, col="purple")
mean(abs(many.truenull) > abs(null.diff))
hist(many.falsenull)
abline(v=alt.diff, lwd=2, col="purple")
mean(abs(many.falsenull) > abs(alt.diff))


## new test for bootstrap
spxibm <- as.matrix(read.table(
  "http://www.burns-stat.com/pages/Tutor/spx_ibm.txt",
  header=TRUE, sep='\t', row.names=1))

head(spxibm)

spxret <- spxibm[, 'spx']
ibmret <- spxibm[,'ibm']

spx.boot.sum <- numeric(1000) # numeric vector 1000 long
for(i in 1:1000) {
  this.samp <- spxret[ sample(251, 251, replace=TRUE) ]
  spx.boot.sum[i] <- sum(this.samp)
}
plot(density(spx.boot.sum), lwd=3, col="steelblue")
abline(v=sum(spxret), lwd=3, col='gold')


## bootstrapping smooths
spx.varsmu <- array(NA, c(251, 20)) # make 251 by 20 matrix
for(i in 1:20) {
  this.samp <- spxret[ sample(251, 251, replace=TRUE) ]
  spx.varsmu[,i] <- supsmu(1:251,
                           (this.samp - mean(this.samp))^2)$y
}
plot(supsmu(1:251, (spxret-mean(spxret))^2), type='l',
     xlab='Days', ylab='Variance')
matlines(1:251, spx.varsmu, lty=2, col='red')


# bootstrap regression coefficients
coef(lm(ibmret ~ spxret))

beta.obs.boot <- numeric(1000)
for(i in 1:1000) {
  this.ind <- sample(251, 251, replace=TRUE)
  beta.obs.boot[i] <- coef(lm(
    ibmret[this.ind] ~ spxret[this.ind]))[2]
}
plot(density(beta.obs.boot), lwd=3, col="steelblue")
abline(v=coef(lm(ibmret ~ spxret))[2], lwd=3, col='gold')


