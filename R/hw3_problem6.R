library(Matrix)
N<-5000 # length of the chain
burn<-1000 # burn in length
X<-rnorm (100, mean=200, sd= sqrt(2))
theta<-matrix(0,N,2) # the chain, theta1=mu, theta2=phi
n<-100

mu0<-0
phi0<-5

theta[1,]<-c(mu0,phi0)

for (i in 2:N){
  theta[i,1]<-rnorm(1,mean=mean(X), sd=1/sqrt(n*theta[i-1,2]))
  theta[i,2]<-rgamma(1,shape=n/2, rate=0.5*sum((X-theta[i,1])^2))
}

#plot the trace plots
par (mfrow=c(1,2))
plot(theta[,1],type="l",ylab="mu",main="trace plot of mu")
plot(theta[,2],type="l",ylab="phi",main="trace plot of phi")
#dev.off()

b<-burn+1
mu.after.burn<-theta[b:N,1]
phi.after.burn<-theta[b:N,2]

#draw histograms for both of the marginal distribution.
par(mfrow=c(1,2))
hist(mu.after.burn, main="Histogram of mu after burn-in")
hist(phi.after.burn,main="Histogram of phi after burn-in")
#dev.off()