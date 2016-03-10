library(ElemStatLearn)
library(MASS)
library(lasso2)

data(prostate)

prednames <- names(prostate)[-(9:10)]
Form <- formula(paste("lpsa~", paste(prednames,collapse="+"), sep=""))

# 5-fold cross-validation
K <- 5

# assign each observation to a cv fold at random
folds <- rep(1:K, ceiling(nrow(prostate)/K))[1:nrow(prostate)]
folds <- sample(folds)

rss <- matrix(0, nr=K, nc=3)
colnames(rss) <- c("lm","ridge","lasso")

getrss <- function(y, yhat) mean((y-yhat)^2)

x <- as.matrix(prostate[,-(9:10)])
y <- prostate$lpsa

# linear regression
for (i in 1:K) {
  fit <- lm(Form, data=prostate[folds!=i,])
  yhat <- predict(fit, newdata=prostate[folds==i,])
  rss[i,1] <- getrss(y[folds==i], yhat)
}

# ridge
lambdas <- 2^seq(-7,7,0.5)
for (i in 1:K) {
  fit <- lm.ridge(Form, data=prostate[folds!=i,], lambda=lambdas)
  best.lam <- which.min(fit$GCV)

  scaledX <- sweep(x[folds==i,], 2, fit$xm)
  scaledX <- sweep(scaledX, 2, fit$scale, "/")

  beta <- fit$coef[,best.lam]
  yhat <- scaledX %*% beta + fit$ym
  rss[i,2] <- getrss(y[folds==i], yhat)
}

# lasso
for (i in 1:K) {
  fit <- l1ce(Form, data=prostate[folds!=i,], bound=seq(0.05,1,0.05))
  gcvres <- gcv(fit)
  best.bound <- gcvres[which.min(gcvres[,"gcv"]), "rel.bound"]

  fit <- l1ce(Form, data=prostate[folds!=i,], bound=best.bound)
  yhat <- predict(fit, newdata=prostate[folds==i,])
  rss[i,3] <- getrss(y[folds==i], yhat)
}

mrss <- colMeans(rss)
srss <- apply(rss, 2, sd)
