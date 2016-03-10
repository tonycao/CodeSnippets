#get data
library(faraway)
data(fpe)
attach(fpe)

#fit the 1st multiple linear model
mod1<-lm(A2~A+B+C+D+E+F+G+H+J+K+N)
mod1_fit<-mod1$fitted.values
mod1_e<-mod1$residuals


#check the constant variance assumption
e2<-abs(mod1_e)
par(mfrow=c(1,2))
plot(A2,e2)
plot(B,e2)

par(mfrow=c(1,2))
plot(C,e2)
plot(D,e2)

par(mfrow=c(1,2))
plot(E,e2)
plot(F,e2)

par(mfrow=c(1,2))
plot(G,e2)
plot(H,e2)

par(mfrow=c(1,2))
plot(J,e2)
plot(K,e2)

par(mfrow=c(1,2))
plot(N,e2)
plot(mod1_fit,e2)

# Method2, weighted by 1/EI^2

mod2<-lm(A2~A+B+C+D+E+F+G+H+J+K+N, weights=1/(EI^2))

#Method3
square_e<-(mod1_e)^2

#here we choose A to fit the linear model with the residual square

mod3<-lm(square_e~A)
w1<-fitted(mod3)
mod4<-lm(A2~A+B+C+D+E+F+G+H+J+K+N, weights=w1)

mod <- mod1
#iteration
for (i in 1:20) {
  eta<-mod$fit
  mod<-lm(mod$res^2~A)
  gamma0<-summary(mod)$coefficients[1]
  gamma1<-summary(mod)$coefficients[2]
  w<-abs(1/(gamma0+gamma1*A))
  mod<-lm(A2~A+B+C+D+E+F+G+H+J+K+N, weights=w)
  cat(i,coef(mod),"\n")  
}