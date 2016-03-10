require(glmnet)
data(Prostate, package = "lasso2")
## Split into training and test
n_obs = dim(Prostate)[1]
proportion_split = 0.5
train_index = sample(1:n_obs, round(n_obs * proportion_split))
y = Prostate$lpsa
X = as.matrix(Prostate[setdiff(colnames(Prostate), "lpsa")])
Xtr = X[train_index,]
Xte = X[-train_index,]
ytr = y[train_index]
yte = y[-train_index]
## Train models
ols = lm(ytr ~ Xtr)
lasso = cv.glmnet(Xtr, ytr, alpha = 1)
ridge = cv.glmnet(Xtr, ytr, alpha = 0)
## Test models
y_hat_ols = cbind(rep(1, n_obs - length(train_index)), Xte) %*% coef(ols)
y_hat_lasso = predict(lasso, s="lambda.min", Xte)
y_hat_ridge = predict(ridge, s="lambda.min", Xte)
## compare
sum((yte - y_hat_ols)^2)
sum((yte - y_hat_lasso)^2)
sum((yte - y_hat_ridge)^2)