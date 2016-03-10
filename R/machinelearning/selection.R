####
# regression subset selection in the prostate dataset
library(ElemStatLearn)
data(prostate)

covnames <- names(prostate[-(9:10)])
y <- prostate$lpsa
x <- prostate[,covnames]

form <- as.formula(paste("lpsa~", paste(covnames, collapse="+"), sep=""))
summary(lm(form, data=prostate[prostate$train,]))

set.seed(1)
train.ind <- sample(nrow(prostate), ceiling(nrow(prostate))/2)
y.test <- prostate$lpsa[-train.ind]
x.test <- x[-train.ind,]

y <- prostate$lpsa[train.ind]
x <- x[train.ind,]

p <- length(covnames)
rss <- list()
for (i in 1:p) {
  cat(i)
  Index <- combn(p,i)

  rss[[i]] <- apply(Index, 2, function(is) {
    form <- as.formula(paste("y~", paste(covnames[is], collapse="+"), sep=""))
    isfit <- lm(form, data=x)
    yhat <- predict(isfit)
    train.rss <- sum((y - yhat)^2)

    yhat <- predict(isfit, newdata=x.test)
    test.rss <- sum((y.test - yhat)^2)
    c(train.rss, test.rss)
  })
}

png("Plots/selection-plots-01.png", height=432, width=432, pointsize=12)
plot(1:p, 1:p, type="n", ylim=range(unlist(rss)), xlim=c(0,p), xlab="number of predictors", ylab="residual sum of squares", main="Prostate cancer data")
for (i in 1:p) {
  points(rep(i-0.15, ncol(rss[[i]])), rss[[i]][1, ], col="blue")
  points(rep(i+0.15, ncol(rss[[i]])), rss[[i]][2, ], col="red")
}
minrss <- sapply(rss, function(x) min(x[1,]))
lines((1:p)-0.15, minrss, col="blue", lwd=1.7)
minrss <- sapply(rss, function(x) min(x[2,]))
lines((1:p)+0.15, minrss, col="red", lwd=1.7)
legend("topright", c("Train", "Test"), col=c("blue", "red"), pch=1)
dev.off()

##
# ridge regression on prostate dataset
library(MASS)
lambdas <- seq(0,50,len=10)
M <- length(lambdas)
train.rss <- rep(0,M)
test.rss <- rep(0,M)
betas <- matrix(0,ncol(x),M)
for(i in 1:M){
  Formula <-as.formula(paste("y~",paste(covnames,collapse="+"),sep=""))
  fit1 <- lm.ridge(Formula,data=x,lambda=lambdas[i])
  betas[,i] <- fit1$coef
  
  scaledX <- sweep(as.matrix(x),2,fit1$xm)
  scaledX <- sweep(scaledX,2,fit1$scale,"/")
  yhat <- scaledX%*%fit1$coef+fit1$ym
  train.rss[i] <- sum((y - yhat)^2)
  
  scaledX <- sweep(as.matrix(x.test),2,fit1$xm)
  scaledX <- sweep(scaledX,2,fit1$scale,"/")
  yhat <- scaledX%*%fit1$coef+fit1$ym
  test.rss[i] <- sum((y.test - yhat)^2)
}

png(file="Plots/selection-plots-02.png", width=432, height=432, pointsize=12) 
plot(lambdas,test.rss,type="l",col="red",lwd=2,ylab="RSS",ylim=range(train.rss,test.rss))
lines(lambdas,train.rss,col="blue",lwd=2,lty=2)
best.lambda <- lambdas[which.min(test.rss)]
abline(v=best.lambda+1/9)
legend(30,30,c("Train","Test"),col=c("blue","red"),lty=c(2,1))
dev.off()


png(file="Plots/selection-plots-03.png", width=432, height=432, pointsize=8) 
plot(lambdas,betas[1,],ylim=range(betas),type="n",ylab="Coefficients")
for(i in 1:ncol(x))
  lines(lambdas,betas[i,],type="b",lty=i,pch=as.character(i))
abline(h=0)
legend("topright",covnames,pch=as.character(1:8))
dev.off()


#######
# lasso
library(lars)
lasso.fit <- lars(as.matrix(x), y, type="lasso", trace=TRUE)

png(file="Plots/selection-plots-04.png", width=432, height=432, pointsize=8) 
plot(lasso.fit, breaks=FALSE)
legend("topleft", covnames, pch=8, lty=1:length(covnames), col=1:length(covnames))
dev.off()

# this plots the cross validation curve
png(file="Plots/selection-plots-05.png", width=432, height=432, pointsize=12) 
lasso.cv <- cv.lars(as.matrix(x), y, K=10, type="lasso", trace=TRUE)
dev.off()




