
#function for mean, std, min and max
mycompute <- function(x) {
  sd   <- sd(x, na.rm=T)
  N    <- sum(table(x))
  mean <- summary(x)[4]
  min  <- summary(x)[1]
  max  <- summary(x)[6]
  
  result <- list("mean" = mean, "sd" = sd, "N" = N, "min" = min, "max" = max)
  return(result) 
}


#import data
#data<-read.csv(file ="C:/Users/laptop/ownCloud/Staff Folders/Yin Yuan/Data for Manuals/youthdata.csv",header = TRUE )
data<-read.csv(file ="/Users/Shared/Dropbox/CodeSnippets/R/youthdata.csv", header = TRUE )

#to check all the variables name, number of observations, number of variables, and type of variables in  the data file
str(data)

#attach the variables in the data file (then you can input the variable name directly)
attach(data)

#get statistics
closeness   <- mycompute(X.19closeness_sum)
religiosity <- mycompute(X.40religiosity_sum)
life        <- mycompute(X.33lifecondition_sum)
interest    <- mycompute(X.34interestinmedia_sum)

#compile the descriptives table
Dmat<-matrix(nrow=4,ncol=5)
Dmat[,1] <- c(closeness$N, religiosity$N, life$N, interest$N)
Dmat[,2] <- c(closeness$mean, religiosity$mean, life$mean, interest$mean)
Dmat[,3] <- c(closeness$sd, religiosity$sd, life$sd, interest$sd)
Dmat[,4] <- c(closeness$min, religiosity$min, life$min, interest$min)
Dmat[,5] <- c(closeness$max, religiosity$max, life$max, interest$max)

#name the col and row
colnames(Dmat) <- c("N","Mean","Std Dev","Minimum","Maximum")
rownames(Dmat) <- c("Closeness with parents","Religiosity","Life condition","Interest in social media")
