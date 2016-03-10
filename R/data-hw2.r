# load data
library(ElemStatLearn)
library(tree)
library(rpart)
library(glmnet)
library(boot)

spam <- read.table("spam.data.txt")
#data(spam)

## model 1: fit the data as good as possible, may overfitting
spam.tree <- tree(factor(V58) ~ ., data = spam, mindev = 0, minsize = 2)#, mindev=1e-6)#, minsize=10)
summary(spam.tree)
plot(spam.tree)
text(spam.tree, cex=.75) #all = T)

cv.model <-cv.tree(spam.tree, , FUN = prune.tree, K = 10)
for (i in 2:5) {
  cv.model$dev <- cv.model$dev + cv.tree(spam.tree, , FUN = prune.tree, K = 10)$dev
}
cv.model$dev <- cv.model$dev / 5
plot(cv.model)  
title("Cross-validation plot for pruning")
#cv.model$dev

## model 2: prune the tree

spam.pruned<-prune.tree(spam.tree, best = 10)
summary(spam.pruned)
plot(spam.pruned)
text(spam.pruned, cex=.75)
#plot(spam.cv)

## model 3: best fit
best.size <- sum(cv.model$dev<=min(cv.model$dev))  # which size is better?
spam.best <- prune.tree(spam.tree, best = best.size) #best.size)
summary(spam.best)
plot(spam.best)
text(spam.best, cex=.75)


#nfolds <- 10
#log.fit <- glm(V58 ~ ., family = binomial, data = spam)
#summary(log.fit)
#cv.err <- cv.glm(spam, log.fit, K = 10)$delta
#cv.err



x <- model.matrix(V58 ~ ., data = spam)

## logistic regression
log.fit = glmnet(x, y = as.factor(spam$V58), family = "binomial")
plot(log.fit, xvar = "dev", label = TRUE)
#grid()

cv.logfit = cv.glmnet(x, y = spam$V58, family = "binomial", type.measure = "class", nfolds = 10)
plot(cv.logfit)
cv.logfit$cvm[which(cv.logfit$lambda==cv.logfit$lambda.min)]
#cv.logfit$cvm[which(cv.lassofit$lambda==cv.lassofit$lambda.1se)]


## lasso logistic regression
lasso.fit<-glmnet(x, y = as.factor(spam$V58), alpha=1, family='binomial')
plot(lasso.fit, xvar="lambda")
#grid()

cv.lassofit <- cv.glmnet(x, y = spam$V58, family='binomial', alpha = 1, type.measure = "deviance", nfolds = 10)
plot(cv.lassofit)
cv.lassofit$cvm[which(cv.lassofit$lambda==cv.lassofit$lambda.min)]
#cv.lassofit$cvm[which(cv.lassofit$lambda==cv.lassofit$lambda.1se)]