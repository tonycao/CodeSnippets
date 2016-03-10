library(splines)
library(mgcv)
library(glmnet)
library(lars)
library(DAAG)
#install.packages("cvTools")
library(cvTools) #run the above line if you don't have this library

data <- read.table("./project1_data.txt")
attach(data)

# standardize 
#maxs <- apply(data, 2, max)
#mins <- apply(data, 2, min)

#apply(data, MARGIN = 2, FUN = function(X) (X - min(X))/diff(range(X)))
#scale(data, center = mins, scale = maxs - mins)

data2<-data[-c(35,6,3),]
y<-data2[,5]


side<-rep(NA,47)
for (i in 1:47){
  if (V7[i] == 'n')
    side[i] = 1
  else
    side[i] = 0 
}

mod1<-lm(V5~V1+V2+V3+V4+V6+side)
summary(mod1)

#mod2<-gam(V5~s(V1+V2+V3+V4+V6+side))
mod3<-lm(V5~V1+V2+V3+V4+V6,data=data2)


xs <- cbind(data2[,1], data2[,2], data2[,3], data2[,4], data2[,6])

# cross validation
# split data
ols_sspe <- 0
wls_sspe <- 0
lasso1_sspe <- 0
lasso2_sspe <- 0
ridge1_sspe <- 0
ridge2_sspe <- 0

for (i in 1:10) {
  print(i)
  k <- 3
  folds <- cvFolds(nrow(xs), K=k)
  
  for (j in 1:k) {
    
    # prepare traing and validation data sets
    train_x <- xs[folds$subsets[folds$which != j],]
    train_y <- y[folds$subsets[folds$which != j]]
    validation_x <- xs[folds$subsets[folds$which == j],]
    validation_y <- y[folds$subsets[folds$which == j]]
    
    # train models on training data
    ols_mod1   <- lm(train_y~train_x)
    wls_mod1   <- lm(train_y~train_x, weights=ols_mod1$res^-2)
    lasso_mod1 <- cv.glmnet(train_x, train_y, alpha = 1, type.measure = "mse", nfolds = 10)#, standardize=FALSE)
    ridge_mod1 <- cv.glmnet(train_x, train_y, alpha = 0, type.measure = "mse", nfolds = 10)#, standardize=FALSE)
    
    # test models on testing data
    y_hat_ols1 = cbind(rep(1, nrow(validation_x)), validation_x) %*% coef(ols_mod1)
    y_hat_wls1 = cbind(rep(1, nrow(validation_x)), validation_x) %*% coef(wls_mod1)
    #y_hat_ols1    <- predict(ols_mod1, data2[folds$subsets[folds$which == j], c(1,2,3,4,6)])
    #y_hat_wls1    <- predict(wls_mod1, validation_x)
    y_hat_lasso11 <- predict(lasso_mod1, validation_x, s = "lambda.min")
    y_hat_lasso12 <- predict(lasso_mod1, validation_x, s = "lambda.1se")
    y_hat_ridge11 <- predict(ridge_mod1, validation_x, s = "lambda.min")
    y_hat_ridge12 <- predict(ridge_mod1, validation_x, s = "lambda.1se")
    
    # SSPE
    ols_sspe <- ols_sspe + sum((y_hat_ols1 - validation_y)^2)
    wls_sspe <- wls_sspe + sum((y_hat_wls1 - validation_y)^2)
    lasso1_sspe <- lasso1_sspe + sum((y_hat_lasso11 - validation_y)^2)
    lasso2_sspe <- lasso2_sspe + sum((y_hat_lasso12 - validation_y)^2)
    ridge1_sspe <- ridge1_sspe + sum((y_hat_ridge11 - validation_y)^2)
    ridge2_sspe <- ridge2_sspe + sum((y_hat_ridge12 - validation_y)^2)
    
  }
  
}  

ols_sspe <- ols_sspe/20
wls_sspe <- wls_sspe/20
lasso1_sspe <- lasso1_sspe/20
lasso2_sspe <- lasso2_sspe/20
ridge1_sspe <- ridge1_sspe/20
ridge2_sspe <- ridge2_sspe/20