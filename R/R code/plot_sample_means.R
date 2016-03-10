plot_sample_means <- function(f_sample, n, m=300,title="Histogram", ...) {
  
  # define a vector to hold our sample means
  means <- double(0)
  
  # generate 300 samples of size n and store their means
  for(i in 1:m) means[i] <- mean(f_sample(n,...))
  
  # scale sample means to plot against standard normal
  scaled_means <- scale(means)
  
  # set up a two panel plot
  par(mfrow=c(1,2))
  par(mar=c(5,2,5,1)+0.1)
  
  # plot histogram and density of scaled means
  hist(scaled_means, prob=T, col="light grey", border="grey", main=NULL, ylim=c(0,0.4))
  lines(density(scaled_means))
  
  # overlay the standard normal curve in blue for comparison
  curve(dnorm(x,0,1), -3, 3, col='blue', add=T)
  
  # adjust margins and draw the quantile-quantile plot
  par(mar=c(5,1,5,2)+0.1)
  qqnorm(means, main="")
  
  # return margins to normal and go back to one panel
  par(mar=c(5,4,4,2)+0.1)
  par(mfrow=c(1,1))
  
  # add a title
  par(omi=c(0,0,0.75,0))
  title(paste(title, ", n=", n, sep=""), outer=T)
  par(omi=c(0,0,0,0))
  
  # return unscaled means (without printing)
  return(invisible(means))
}
