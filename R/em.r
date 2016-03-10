## EM algorithm implementation
## Joshua Moller-Mara
require(MASS)
require(mvtnorm)

## Probability of each cluster for each point
E.step <- function(X, phi, N) {
  h <- with(phi, do.call(cbind,
                      lapply(1:N, function(i)
                      dmvnorm(X, mu[[i]], sig[[i]]))))
  h/rowSums(h)                       #Normalize
}

## Given the probability of each cluster for each point, we try to
## find the values of mu, sigma, and alpha that maximize the likelihood
M.step <- function(X, h, N) {
  covs <- lapply(1:N, function(i) cov.wt(X, h[,i]))
  mu <- lapply(covs, "[[", "center")
  sig <- lapply(covs, "[[", "cov")
  alpha <- colMeans(h)
  list(mu = mu, sig = sig, alpha = alpha)
}

## log.likelihood
## Given points and parameters, how well does our model fit?
## This also gives us a terminating condition for the EM algorithm.
## We stop if we don't improve all that much.
## This is also used for AIC for model selection (choosing a value of k)
log.like <- function(X, phi, N) {
  probs <- 
    with(phi, do.call(cbind,
                      lapply(1:N, function(i)
                        alpha[i] * dmvnorm(X, mu[[i]], sig[[i]]))))
  sum(log(rowSums(probs)))
}

#Function to plot current data
## Also visualize clusters using contours
plot.em <- function(X, phi, N){
  xpts <- seq((rr <- range(X[,1]))[1], rr[2], length.out=50)
  ypts <- seq((rr <- range(X[,2]))[1], rr[2], length.out=50)
  plot(X)
  for(i in 1:N) {
    mixture.contour <-
      with(phi, outer(xpts,ypts,function(x,y)
        alpha[i]*dmvnorm(cbind(x,y),mean=mu[[i]],sigma=sig[[i]])))
    contour(xpts, ypts, mixture.contour, nlevels=5, col=i+1, add=TRUE, lwd=3)
  }
}

## Terminate if log.like @ (t-1) - log.like @ (t) is below a threshold

## Here we actually run EM.
## X is our data set
## N is the number of points
## This EM algorithm implementation should be able to handle values of X with any dimension.
## However, it only can plot 2D data.
run.em <- function(X, N, plot = TRUE, sleep = 0.5, max.iter = 30, save=FALSE) {
  covs <- replicate(N, list(cov.wt(X[sample(nrow(X), 30),])))
  mu <- lapply(covs, "[[", "center")
  sig <- lapply(covs, "[[", "cov")
  alpha <- rep(1/N, N)
  phi <<- list(mu = mu, sig = sig, alpha = alpha)
  
  for(i in 1:max.iter) {
    oldphi <- phi
    h <<- E.step(X, phi, N)
    phi <<- M.step(X, h, N)
    if(plot) {
      plot.em(X, phi, N)
      if(save) {
        dev.copy(jpeg, sprintf("output/em-%02d-clusters-%02d.jpg", N, i))
        dev.off()
      }
      Sys.sleep(sleep)
    }
    if((log.like(X, phi, N) - log.like(X, oldphi, N)) < 0.01)
      break
  }
  return(list(phi = phi, aic = 2*3*N - log.like(X, phi, N)))
}


##
## Example clustering
## 

sample.data <- 
  do.call(rbind, replicate(sample(5,1), list(rmvnorm(n=1000, rnorm(2, sd=30), diag(rgamma(2, 50))))))

plot(sample.data)

##
## Run EM for 1 to 6 clusters
## Output which value of k has the best fit
## 
(aics <- sapply(1:6, function(i) run.em(sample.data, i, sleep=0, max.iter=30)$aic))
which.min(aics)
nrow(sample.data)

##
## Same as above, but fit values of k multiple times
## 
(aics <- sapply(1:10, function(i) min(replicate(5, run.em(sample.data, i, sleep=0)$aic))))
which.min(aics)
nrow(sample.data)


##
## Example used in the blog
## 

two.cluster.data <- 
  rbind(rmvnorm(n=1000, mean=c(0,0), diag(2)*10),
        rmvnorm(n=1000, mean=c(3,0), matrix(c(5,2,2,1),2,2)))

run.em(two.cluster.data, 2, sleep=0, max.iter=100)

## Try a k-means clustering
## color it
km <- kmeans(two.cluster.data, 2, iter.max = 30)
plot(two.cluster.data, ylab="", xlab="", col = c("red", "blue")[km$cluster])

## Try EM mixture model clustering
## and color it
em.output <- run.em(two.cluster.data, 2, sleep=0, max.iter=100)
ecolor <- apply(E.step(two.cluster.data, em.output$phi, 2), 1, which.max)
plot(two.cluster.data, ylab="", xlab="", col = c("red", "blue")[ecolor])