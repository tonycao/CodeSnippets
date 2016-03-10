library(scatterplot3d)
library(NbClust)
library(EMCluster)
library(base)
library(mclust)
library(cluster)
library(MASS)
library(mvtnorm)

####################
# problem 2

# plot the within group sum of squares vs number of clusters
wssplot <- function(data, nc=15, seed=1234){
  wss <- (nrow(data)-1)*sum(apply(data,2,var)) # total ss
  for (i in 2:nc){
    set.seed(seed)
    wss[i] <- sum(kmeans(data, centers=i)$withinss)
  }
  plot(1:nc, wss, type="b", xlab="Number of Clusters",
       ylab="Within groups sum of squares")
}


# load data
clusterset1 = read.table('ClusterSet1.txt')
#data <- scale(data) # standardize
scatterplot3d(clusterset1[,1], clusterset1[,2], clusterset1[,3], pch=19, cex.symbols=0.5, main="3D Scatterplot")

# choose number of k 
wssplot(clusterset1)  

#set.seed(1234)
#nc <- NbClust(data, min.nc=2, max.nc=15, method="kmeans")
#table(nc$Best.n[1,])

#barplot(table(nc$Best.n[1,]),
#        xlab="Numer of Clusters", ylab="Number of Criteria",
#        main="Number of Clusters Chosen by 26 Criteria")

clusters <- kmeans(clusterset1, 10, iter.max=500, nstart=35)   

clusplot(clusterset1, clusters$cluster, color=TRUE, shade=TRUE, labels=3, lines=0, plotchar=F, 
         main = paste('Cluster Plot (Cluster Set 1)'), sub='')

scatterplot3d(clusterset1[,1], clusterset1[,2], clusterset1[,3], pch=19, cex.symbols=0.5, color=clusters$cluster, main="3D Scatterplot")

clusterset1.pca <- prcomp(clusterset1,
                 center = TRUE,
                 scale. = TRUE) 

library(devtools)
install_github("ggbiplot", "vqv")
library(ggbiplot)

ggbiplot(clusterset1.pca, obs.scale = 1, var.scale = 1, 
              groups = factor(clusters$cluster), ellipse = TRUE, circle = TRUE) + 
              scale_color_discrete(name = '') + 
              theme(legend.direction = 'horizontal', 
              legend.position = 'top')


####################
# problem 3
#em.ic(data.matrix(clusterset1))
# Run the function to see how many clusters
# it finds to be optimal, set it to search for
# at least 1 model and up 20.
d_clust <- Mclust(as.matrix(clusterset1), G=1:20)
m.best <- dim(d_clust$z)[2]
cat("model-based optimal number of clusters:", m.best, "\n")
# 10 clusters
plot(d_clust)


## EM algorithm for GMM
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
## Terminate if log.like @ (t-1) - log.like @ (t) is below a threshold
log.like <- function(X, phi, N) {
  probs <- 
    with(phi, do.call(cbind,
                      lapply(1:N, function(i) alpha[i] * dmvnorm(X, mu[[i]], sig[[i]]))))
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

## run EM
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
    #if(plot) {
      #plot.em(X, phi, N)
      #if(save) {
      #  dev.copy(jpeg, sprintf("output/em-%02d-clusters-%02d.jpg", N, i))
      #  dev.off()
      #}
      #Sys.sleep(sleep)
    #}
    if((log.like(X, phi, N) - log.like(X, oldphi, N)) < 0.01)
      break
  }
  return(list(phi = phi, aic = 2*3*N - log.like(X, phi, N)))
}

em.output <- run.em(as.matrix(clusterset1), 10, sleep=0, max.iter=500)
ecolor <- apply(E.step(as.matrix(clusterset1), em.output$phi, 10), 1, which.max)
clusplot(clusterset1, ecolor, color=TRUE, shade=TRUE, labels=3, lines=0, plotchar=F, 
         main = paste('Cluster Plot (Cluster Set 1)'), sub='')
scatterplot3d(clusterset1[,1], clusterset1[,2], clusterset1[,3], pch=19, cex.symbols=0.5, color=ecolor, main="3D Scatterplot")

####################
# problem 4
d_dist <- dist(as.matrix(clusterset1))   # find distance matrix 
tree1 <- hclust(d_dist,method="complete") # apply hirarchical clustering and plot
tree2 <- hclust(d_dist,method="average")
plot(tree1)   
groups <- cutree(tree1, k=10) # cut tree into 5 clusters
# draw dendogram with red borders around the 5 clusters
rect.hclust(tree1, k=10, border="red")
plot(tree2)   
groups <- cutree(tree2, k=10) # cut tree into 5 clusters
# draw dendogram with red borders around the 5 clusters
rect.hclust(tree2, k=10, border="red")


####################
# problem 5
clusterset2 = read.table('ClusterSet2.txt')
# choose number of k 
wssplot(clusterset2)  
d_clust <- Mclust(as.matrix(clusterset1), G=1:20)
m.best <- dim(d_clust$z)[2]
cat("model-based optimal number of clusters:", m.best, "\n")
# 10 clusters
plot(d_clust)

clusterset2.pca <- prcomp(clusterset2, center = TRUE, scale. = TRUE) 
clusters2 <- kmeans(clusterset2, 10, iter.max=500, nstart=35) 
clusplot(clusterset2, clusters2$cluster, color=TRUE, shade=TRUE, labels=3, lines=0, plotchar=F, 
         main = paste('Cluster Plot (Cluster Set 2)'), sub='')

ggbiplot(clusterset2.pca, obs.scale = 1, var.scale = 1, 
         groups = factor(clusters2$cluster), ellipse = TRUE, circle = TRUE) + 
  scale_color_discrete(name = '') + 
  theme(legend.direction = 'horizontal', 
        legend.position = 'top')