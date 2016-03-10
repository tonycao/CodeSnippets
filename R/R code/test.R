attach(iris)

for (i in 1:4){
  print(i)
  boxplot(iris[,i]~Species,xlab='Species',
          ylab=paste(names(iris)[i]),
          main=paste('Boxplots of',names(iris)[i],
          ' by species.'),col='slateblue',cex.lab=1.5)
  paste()
}