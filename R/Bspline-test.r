library(splines)
x<-runif(100)
y<-sin(2*pi*x)+rnorm(100,0,0.2)



fit1=lm(y~bs(x,degree=1,knots=c(0.2,0.4,0.6)))
fit2=lm(y~bs(x,degree=2,knots=c(0.2,0.4)))
fit3=lm(y~bs(x,degree=3,knots=c(0.2,0.4,0.6)))
fit4=lm(y~bs(x,df=4))
fit5=lm(y~bs(x,df=20))


xpred<-seq(0.01,0.99,0.01)



plot(x,y)
lines(xpred, predict(fit1, data.frame(x=xpred)),col="red")
lines(xpred, predict(fit2, data.frame(x=xpred)),col="blue")
lines(xpred, predict(fit3, data.frame(x=xpred)),col="orange")
lines(xpred, predict(fit4, data.frame(x=xpred)),col="purple")
lines(xpred, predict(fit5, data.frame(x=xpred)),col="yellow")

