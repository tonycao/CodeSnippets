
# sample size
n = 100

# number of samples
m = 500

means <- double(0)

for(i in 1:m) 
  # randomly sample n points from uniform distribution
  # compute sample mean of the n points
  # sample m times
  means[i] = mean(runif(n))

# scale sample means to plot against standard normal
normalized_means <- scale(means)

par(mfrow=c(1,2))
par(mar=c(5,2,5,1)+0.1)

# plot histogram and density of scaled means
hist(normalized_means, prob=T, col="light grey", border="grey", main=NULL, ylim=c(0,0.4))
lines(density(normalized_means), col='blue', lty=1)

# overlay the standard normal curve in blue for comparison
curve(dnorm(x,0,1), -3, 3, col='green', add=T, lty=2)

#title(main="Simulation for Central Limit Theorem", font.main=4)

legend(0.5, 0.4 , c("Sample Means","normal dist"), cex=0.8, 
       col=c("green","blue"), lty=1:2);

# Create box around plot
box()

par(mar=c(5,1,5,2)+0.1)
qqnorm(means, main="")

# return margins to normal and go back to one panel
par(mar=c(5,4,4,2)+0.1)
par(mfrow=c(1,1))

# add a title
par(omi=c(0,0,0.75,0))
title(paste("Sample Means (uniform distribution)", ", n=", n, sep=""), outer=T)
par(omi=c(0,0,0,0))