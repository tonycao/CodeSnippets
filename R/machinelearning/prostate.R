# we'll use the prostate data set from "the book"
library(ElemStatLearn)
data(prostate)

# get information on dataset
?prostate

# attach dataset to refer to names
attach(prostate)

# let's dicotomize the response lpsa for this example
# we'll call it high if greater than median,
# and low otherwise
g <- factor(ifelse(lpsa > median(lpsa), "high", "low"))

# we'll use the first three predictors lcavol, lweight and age
# to model the classes

# plot these 3 and use color to indicate response
library(lattice)
splom(~prostate[,1:3], groups=g)

# linear regression on indicator
# make indicator
y <- ifelse(g=="high", 1, 0)

# fit linear regression
lm.fit <- lm(y~lcavol+lweight+age)

# get coefficients
lm.beta <- lm.fit$coef

# plot estimated linear model in lcavol and age
# for mean lweight
b <- -lm.beta[2]/lm.beta[4]
a <- (0.5 - lm.beta[1] - lm.beta[3]*mean(lweight))/lm.beta[4]

plot(lcavol, age, col=g)
abline(a,b)

# predict y
yhat <- predict(lm.fit)

# predict g
lm.ghat <- factor(ifelse(yhat > 0.5, "high", "low"))

# number of errors
sum(lm.ghat != g)

# error rate
mean(lm.ghat != g)

# confusion table
table(lm.ghat, g)

###############
# lda

# check if class conditional marginals look normal
densityplot(~lcavol+lweight+age, groups=g, scales=list(relation="free"))

library(MASS)
# fit lda
lda.fit <- lda(g~lcavol+lweight+age)

# predict classes
lda.ghat <- predict(lda.fit)$class

# number of errors
sum(lda.ghat != g)

# error rate
mean(lda.ghat != g)

# confusion table
table(lda.ghat, g)

# draw decision boundary for lcavol and age at mean lweight
GS <- 500
x1 <- seq(min(lcavol), max(lcavol), len=GS)
x2 <- seq(min(age), max(age), len=GS)
x <- expand.grid(x1, x2)
newdat <- data.frame(lcavol=x[,1], lweight=mean(lweight), age=x[,2])

lda.Ghat <- as.numeric(predict(lda.fit, newdata=newdat)$class)

contour(x1, x2, matrix(lda.Ghat, GS,GS), levels=c(1,2), add=TRUE, drawlabels=FALSE, col="red")

####
# qda
qda.fit <- qda(g~lcavol+lweight+age)

# predict classes
qda.ghat <- predict(qda.fit)$class

# number of errors
sum(qda.ghat != g)

# error rate
mean(qda.ghat != g)

# confusion table
table(qda.ghat, g)

# draw decision boundary
qda.Ghat <- as.numeric(predict(qda.fit, newdata=newdat)$class)
contour(x1, x2, matrix(qda.Ghat, GS,GS), levels=c(1,2), add=TRUE, drawlabels=FALSE, col="blue")

####
# logistic regression
lreg.fit <- glm(g~lcavol+lweight+age, family="binomial")

# predict probabilities
lreg.phat <- predict(lreg.fit, type="response")

# predict classes using 0.5 probability threshold
# the sign is turned because glm codes "high" as 0 and "low" as 1
lreg.ghat <- factor(ifelse(lreg.phat<0.5, "high", "low"))

# number of errors
sum(lreg.ghat != g)

# error rate
mean(lreg.ghat != g)

# confusion table
table(lreg.ghat, g)

lreg.beta <- lreg.fit$coef

# draw decision boundary at equal odds (prob. = 0.5)
b <- -lreg.beta[2]/lreg.beta[4]
a <- (-lreg.beta[1] - lreg.beta[3]*mean(lweight))/lreg.beta[4]
abline(a,b,col="green")

####
# tree
library(tree)
tree.fit <- tree(g~lcavol+lweight+age)
tree.cv <- cv.tree(tree.fit, K=5)
plot(tree.cv)

tree.fit2 <- prune.tree(tree.fit, best=3)

# plot tree representation
plot(tree.fit2, type="unif")
text(tree.fit2)

# plot partition
plot(lcavol, lweight, col=g)
abline(v=1.81)
segments(-2,3.69,1.81,3.69)
text(c(3,1,1), c(6,6,2.5), c("high","high","low"),cex=1.2)

# predict labels
tree.ghat <- predict(tree.fit, type="class")

# number of errors
sum(tree.ghat != g)

# error rate
mean(tree.ghat != g)

# confusion table
table(tree.ghat, g)

# this is handy
ghats <- cbind(lm.ghat, lda.ghat, qda.ghat, lreg.ghat, tree.ghat)
errors <- ghats != as.numeric(g)
error.rates <- data.frame(`error rate`=colMeans(errors))
row.names(error.rates) <- c("LM","LDA","QDA","L-Reg","Tree")

# this generates a table of error rates
# you can paste to a latex document
library(xtable)
xtable(error.rates, type="html")
