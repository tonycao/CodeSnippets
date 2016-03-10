#project regression

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
library(stats)
library(pls)
library(lars)
library(glmnet)

# functions

# princepal component regression
pcr_func <- function(X, Y, beta){
  # firstly choose the number of PC to use based on PCA.
  pc=prcomp(X)
  eig.val=(pc$sdev)^2
  prop=cumsum(eig.val/sum(eig.val))
  
  #win.graph()
  #plot(prop,type="b")
  ncomp=which(prop>=0.99)[1] # using the criterion 95% to determine the number of pcs to retain.
  
  mod.pcr=pcr(Y ~ X, ncomp)
  #summary(mod.pcr)
  #names(mod.pcr)
  mse_beta = sum((coef(mod.pcr)[,1,1] - beta)^2) / length(beta)
  mse_y = sum((fitted(mod.pcr)[,1,1] - Y)^2)/length(Y)
  #MSE_FITT[i]<-sum((fitted(mod2)[,1,1]-y)^2)/n
  #MSE_COEF[i]<-sum((coef(mod2)[,1,1]-beta)^2)/n
  
  return(list("mse_y"=mse_y, "mse_beta"=mse_beta, ""))
}

#Stepwise regression
step_func <- function(X, Y, beta) {
  model1<-lm(Y~X)
  #summary(model1)$r.squared
  model2<-step(model1, direction="forward")
  mse_beta = sum((model2$coefficients - c(1,beta))^2) / length(beta)
  
  y_hat = model2$fitted.values
  mse_y = sum((y_hat - Y)^2)/length(Y)
  return(list("mse_y" = mse_y, "mse_beta" = mse_beta))
}


#ridge regression
ridge_func <- function(X, Y, beta) {
  
  # centering the data
  mm<-apply(X, 2, mean)
  Xc<-as.matrix(sweep(X, 2, mm))
  Yc<- Y - mean(Y)
  
  ridge.model<-lm.ridge(Yc~Xc, lambda=seq(0, 5e-8 ,1e-9))
  #lambda.ridge <- seq(0, 10 ,.01)[which.min(ridge.model$GCV)]
  #Lambda<-coef(ridge.model)[which.min(ridge.model$GCV),]
  Lambda<-ridge.model$lambda[ridge.model$GCV==min(ridge.model$GCV)]
  ridge.model2<-lm.ridge(Yc~Xc, lambda=Lambda)
  
  #X.matrix<-cbind(matrix(rep(1, length(y)), ncol=1), Xc)
  y_hat <- X%*% matrix(ridge.model2$coef, ncol=1)
  #y_hat <- sweep((Xc %*% ridge.model2$coef), 2, mm, "+")
                       
  mse_beta <- sum((ridge.model2$coef - beta)^2) / length(beta)
  mse_y <- sum((y_hat - Y)^2)/length(Y)
  return(list("mse_y" = mse_y, "mse_beta" = mse_beta))
  
}

#lasso
lasso_func <- function(X, Y, beta) {
  #lasso.fit = glmnet(X, Y)
  #cvfit = cv.glmnet(X, Y)
  #fitted.val = predict(cvfit, X, s = "lambda.min")
  lasso.model <- lars(X, Y, type="lasso")
  #lambda.lasso <- c(lasso.model$lambda,0)
  #beta <- coef(lasso.model)
  fitted.val <- X%*%coef(lasso.model)[lasso.model$RSS==min(lasso.model$RSS),]
  #fitted.val <- predict(lasso.model, as.matrix(X), s = 4, type="fit")$fit
  #fitted.val = predit(lasso.model, X)$fit
  mse_y <- sum((fitted.val - Y)^2)/length(Y)
  mse_beta <- sum((coef(lasso.model)[lasso.model$RSS==min(lasso.model$RSS),] - beta)^2) / length(beta)

  return(list("mse_y" = mse_y, "mse_beta" = mse_beta))
}

########
# case 1

n = 100
p = 8
beta = c(3, 1.5 ,0, 0, 2, 0, 0, 0)
mu = rep(0, n)
sigma = diag(n)

mse_step_beta = rep(0, n)
mse_pcr_beta = rep(0, n)
mse_rr_beta = rep(0, n)
mse_lasso_beta = rep(0, n)

mse_step = rep(0, n)
mse_pcr = rep(0, n)
mse_rr = rep(0, n)
mse_lasso = rep(0, n)

for (i in 1:100) {
  
    X1 = matrix(rnorm(p*n), ncol=p)
    beta = matrix(beta,ncol=1)
    epsilon = matrix(rnorm(n, 0, 3), ncol=1)
    
    Y1 = X1 %*% beta + epsilon

    output1 = step_func(X1, Y1, beta)
    mse_step[i] = output1$mse_y
    mse_step_beta[i] = output1$mse_beta
    output2 = pcr_func(X1, Y1, beta)
    mse_pcr[i] = output2$mse_y
    mse_pcr_beta[i] = output2$mse_beta
    output3 = ridge_func(X1, Y1, beta)
    mse_rr[i] = output3$mse_y
    mse_rr_beta[i] = output3$mse_beta
    output4 = lasso_func(X1, Y1, beta)
    mse_lasso[i] = output4$mse_y
    mse_lasso_beta[i] = output4$mse_beta
}

plot(mse_step)
plot(mse_step_beta)

#sum(mse_step) / n

plot(mse_pcr)
plot(mse_pcr_beta)

plot(mse_rr)
plot(mse_rr_beta)

plot(mse_lasso)
plot(mse_lasso_beta)


# case 2
p = 100

mse_step_beta = rep(0, n)
mse_pcr_beta = rep(0, n)
mse_rr_beta = rep(0, n)
mse_lasso_beta = rep(0, n)

mse_step = rep(0, n)
mse_pcr = rep(0, n)
mse_rr = rep(0, n)
mse_lasso = rep(0, n)

for (i in 1:100) {
  X2 = matrix(rnorm(p*n), ncol=p)
  beta2 = rep(NA, p)
  beta2[1:8] = c(3, 1.5, 0, 0, 2, 0, 0, 0)
  for (j in 9:p) {
    beta2[j] = rnorm(1)
  }
  #beta_j = rnorm(p - length(beta), 0, 1)
  #beta2 = c(beta, beta_j)
  epsilon = matrix(rnorm(n, 0, 3), ncol=1)
  Y2 = X2 %*% beta2 + epsilon

  #output1 = step_func(X2, Y2, beta2)
  #mse_step[i] = output1$mse_y
  #mse_step_beta[i] = output1$mse_beta
  output2 = pcr_func(X2, Y2, beta2)
  mse_pcr[i] = output2$mse_y
  mse_pcr_beta[i] = output2$mse_beta
  output3 = ridge_func(X2, Y2, beta2)
  mse_rr[i] = output3$mse_y
  mse_rr_beta[i] = output3$mse_beta
  output4 = lasso_func(X2, Y2, beta2)
  mse_lasso[i] = output4$mse_y
  mse_lasso_beta[i] = output4$mse_beta
}


plot(mse_step)
plot(mse_step_beta)

plot(mse_pcr)
plot(mse_pcr_beta)

plot(mse_rr)
plot(mse_rr_beta)

plot(mse_lasso)
plot(mse_lasso_beta)


# case 3
p = 200
mse_step_beta = rep(0, n)
mse_pcr_beta = rep(0, n)
mse_rr_beta = rep(0, n)
mse_lasso_beta = rep(0, n)

mse_step = rep(0, n)
mse_pcr = rep(0, n)
mse_rr = rep(0, n)
mse_lasso = rep(0, n)

for(i in 1:100) {

  X3 = matrix(rnorm(p*n), ncol=p)
  beta_j = rnorm(p - length(beta), 0, 1)
  beta3 = c(beta, beta_j)
  epsilon = matrix(rnorm(n, 0, 3), ncol=1)
  Y3 = X3 %*% beta3 + epsilon
  
  #output1 = step_func(X3, Y3, beta3)
  #mse_step[i] = output1$mse_y
  #mse_step_beta[i] = output1$mse_beta
  output2 = pcr_func(X3, Y3, beta3)
  mse_pcr[i] = output2$mse_y
  mse_pcr_beta[i] = output2$mse_beta
  output3 = ridge_func(X3, Y3, beta3)
  mse_rr[i] = output3$mse_y
  mse_rr_beta[i] = output3$mse_beta
  output4 = lasso_func(X3, Y3, beta3)
  mse_lasso[i] = output4$mse_y
  mse_lasso_beta[i] = output4$mse_beta

}

plot(mse_step)
plot(mse_step_beta)

plot(mse_pcr)
plot(mse_pcr_beta)

plot(mse_rr)
plot(mse_rr_beta)

plot(mse_lasso)
plot(mse_lasso_beta)
