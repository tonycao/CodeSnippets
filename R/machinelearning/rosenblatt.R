# a simple implementation of Rosenblatt's algorithm
# Input:
#    x: training covariates
#    y: label coding (assumed -1 and +1)
#    beta0: initial point for beta, can be single number or vector of size ncol(x)
#    tol: tolerance for convergence check
#    minepochs: minimum number of times to cycle all training points (training epochs)
#    maxepochs: maximum number of training epochs
#    verbose: print messages as iterations go
#
# Output: estimated weight vector (beta)

rosen <- function(x, y, beta0=1, tol=1e-8, minepochs=2, maxepochs=100, verbose=FALSE)
  {
    N <- nrow(x)
    p <- ncol(x)
    
    if (length(y) != N) {
      stop("The number of rows in x is not the length of y")
    }

    if (length(beta0==1))
      beta0=rep(beta0,p)

    if (length(beta0) != p) {
      stop("The dimension of beta0 is not the number of columns in x")
    }

    # make it stochastic!
    o <- sample(N)
    x <- x[o,]
    y <- y[o]
    
    itlim <- maxepochs * N
    itmin <- minepochs * N
    
    eps <- .Machine$double.xmax
    beta <- beta0

    i <- 0; 
    while ((eps > tol && i < itlim) || (i < itmin)) {
      beta0 <- beta
      ind <-  (i %% N) + 1
      # check if this point is misclassified
      d <- y[ind] * crossprod(beta, x[ind,])
      if (d < 0) {
        # it is, update beta
        beta <- beta0 + y[ind] * x[ind,]
      }

      # update epsilon
      eps <- sqrt(sum((beta0-beta)^2))/sqrt(sum(beta0^2))

      i <- i+1
      if (verbose)
        cat(sprintf("It: %d ind:%d d:%.4f eps: %.4f\n", i, ind, d, eps))
    }
    if (i==itlim)
      warning("Failed to converge")
    
    return(beta)
  }
