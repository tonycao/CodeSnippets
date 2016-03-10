
library(alr3)
library(MASS)
library(zoo)
library(lmtest)

library(asuR)
library(lattice)
library(grid)
library(faraway)


#library(Design)
library(rms)
library(dprep)
library(grid)
library(faraway)
library(leaps)

#################

# Principal Component Regression
#install.packages("pls")
library(pls)

#A training set consisting of 21 NIR spectra of PET yarns, measured at 268 wavelengths, and 21
#corresponding densities. A test set of 7 samples is also provided. Many thanks to Erik Swierenga.

?yarn
names(yarn)

dim(yarn$NIR)
NIR=yarn$NIR
density=yarn$density
train=yarn$train

#win.graph()
#dev.new()
plot(NIR[1,],typ="n")
for (i in 1: 28) lines(NIR[i,],col=i,type="l")

# 
Y=density[train]
X=NIR[train,]

# firstly choose the number of PC to use based on PCA.
pc=prcomp(X)
eig.val=(pc$sdev)^2
prop=cumsum(eig.val/sum(eig.val))

#win.graph()
plot(prop,type="b")
ncomp=which(prop>=0.99)[1] # using the criterion 99% to determine the number of pcs to retain.

mod.pcr=pcr(Y ~ X, ncomp)
summary(mod.pcr)
names(mod.pcr)

mod.pcr$fitted.values # the y.hat for using 1, 2, 3 PCs, respectively.
b.hat=coef(mod.pcr)[,1,1] # b.hat=U*beta.hat


###Stepwise regression
data(meatspec)
meatspecA<-meatspec[1:172,]
model1<-lm(fat~., meatspec[1:172,])
summary(model1)$r.squared
model2<-step(model1)


### Ridge Regression
yc<-meatspec$fat[1:172]-mean(meatspec$fat[1:172])
mm<-apply(meatspec[1:172,-101],2,mean)
trainx<-as.matrix(sweep(meatspec[1:172,-101],2,mm))

gridge<-lm.ridge(yc~trainx, lambda=seq(0,5e-8,1e-9))
yc<-meatspec$fat[1:172]-mean(meatspec$fat[1:172])
mm<-apply(meatspec[1:172,-101],2,mean)
trainx<-as.matrix(sweep(meatspec[1:172,-101],2,mm))

gridge<-lm.ridge(yc~trainx, lambda=seq(0,5e-8,1e-9))

#LASSO

##Using lars
# install.packages("lars")

library(lars)

data(diabetes)
par(mfrow=c(2,2))
attach(diabetes)
object <- lars(x,y,type="lasso")  
plot(object)
object2 <- lars(x,y,type="lar")
plot(object2)
object3 <- lars(x,y,type="for") # Can use abbreviations
plot(object3)
object4 <- lars(x,y,type="stepwise") 
plot(object4)



### make predictions at the values in x, at each of the
### steps produced in object
#f
data(diabetes)
par(mfrow=c(2,2))
attach(diabetes)
object <- lars(x,y,type="lasso")  
plot(object)
object2 <- lars(x,y,type="lar")
plot(object2)
object3 <- lars(x,y,type="for") # Can use abbreviations
plot(object3)
object4 <- lars(x,y,type="stepwise") 
plot(object4)
