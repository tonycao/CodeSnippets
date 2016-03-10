#simulate 100 points, x~N( mean= 200, precise=0.5)
data<-rnorm(n=100, m=200, sd=sqrt(2))

#computing sample mean and sample variance
sample_mean<-sum(data)/100

#for one time
#initial_mean<-rnorm(n=1,mean=sample_mean,sd=1/500)
#rgamma(n=1, shape=100/2, rate=sum((data-initial_mean)^2)/2)


# gibbs sampler (loop)
com_mean<-rep(NA,10000)
com_phi<-rep(NA,10000)
com_mean[1]<-0
com_phi[1]<-5

for (i in 2:10000){
  com_mean[i]<-rnorm(n=1,mean=sample_mean,sd=1/(100*com_phi[i-1]))
  com_phi[i]<-rgamma(n=1,shape=100/2,rate=sum((data-com_mean[i])^2)/2)
}

hist(com_mean[2:10000],breaks=c((-100:100)/400+200))