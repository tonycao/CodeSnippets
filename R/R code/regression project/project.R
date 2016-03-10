#import data
library(lmtest) # testing linear regression
library(alr3)
#library(zoo)
library(MASS)   # box-cox transformation
library(grid)
library(faraway)
library(lawstat)
data<-read.table("projectdatafall2014.txt", header=T)
y<-data[,1]
x<-data[,2]


#data summary
print(summary(x))
print(sd(x))
print(summary(y))
print(sd(y))
par(mfrow=c(2,2))
boxplot(x, ylab="Rate")
boxplot(y, ylab="Solvent weight")
hist(x, freq=FALSE, xlab="Rate")
hist(y, freq=FALSE, xlab="Solvent weight")

#simple linear regression and scatterplot
slm<-lm(y~x)
print(summary(slm))
par(mfcol=c(1,1))
plot(x,y,main="scatter Plot", xlab="Rate", ylab="Solvent Weight")
abline(coef(slm),lty=2)

#Box-Cox transformation, estimate \lambda
par(mfrow=c(1,1))
boxcox(slm, plotit=TRUE)
boxcox(slm, plotit=TRUE, lambda=seq(1,2,by=0.01))

lambda<-1.4
ytrans<-(y^lambda-1)/lambda
slm2<-lm(ytrans~x)
print(summary(slm2))


#weighted linear model
residsl2<-residuals(slm)
absresidsl2<-abs(residsl2)
plot(x,absresidsl2)

wlm<-lm(absresidsl2~x)
w<-1/fitted(wlm)^2
wlm2<-lm(y~x, weights=w)
print(summary(wlm2))
print(confint(wlm2))

#quadratic model
qlm<-lm(y~x+I(x^2))
print(summary(qlm))
par(mfcol=c(2,3))
plot(fitted(qlm),residuals(qlm), xlab="Fitted", ylab="Residuals")
abline(h=0)
plot(fitted(qlm),abs(residuals(qlm)),xlab="Fitted",ylab="|Residuals|" ) 
qqnorm(residuals(qlm),ylab="Residuals")
qqline(residuals(qlm))
hist(residuals(qlm))
cook<-cooks.distance(qlm)
halfnorm(cook,3,ylab="Cooks dist")
boxplot(cook)

runs.test(residuals(qlm)) 
dwtest(qlm) 
bptest(qlm) 
shapiro.test(residuals(qlm))



# new model
Xnew<-sqrt(x)
Model4<-lm(y~Xnew)

#check the residual
plot(fitted(Model4),residuals(Model4),main="Residual Plot for Model4",xlab="Fitted Value",ylab="Residuals")
abline(h=0,lty=2,col=3)
print(summary(Model4))

#Box-cox TRANSFORMATION
boxcox(Model4)

lambda<-1.7
#ytrans<-(y^lambda-1)/lambda

# Model5
Ynew<-y^lambda
Model5<-lm(Ynew~Xnew)

#check the residual
plot(fitted(Model5),residuals(Model5),main="Residual Plot for Model5",xlab="Fitted Value",ylab="Residuals")
abline(h=0,lty=2,col=3)
print(summary(Model5))
qqnorm(residuals(Model5),ylab="Residuals")
qqline(residuals(Model5))

residsl2<-residuals(Model5)
absresidsl2<-abs(residsl2)
plot(Xnew,absresidsl2)

wlm<-lm(absresidsl2~Xnew)
w<-1/fitted(wlm)^2
wlm2<-lm(Ynew~Xnew, weights=w)
print(summary(wlm2))
print(confint(wlm2))
plot(fitted(wlm2),residuals(wlm2),main="Residual Plot for weighted Model5",xlab="Fitted Value",ylab="Residuals")
abline(h=0,lty=2,col=3)
print(summary(wlm2))