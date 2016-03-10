# a little experiment with kernels and digits

library(ElemStatLearn)
data(zip.train)

load(url("http://www.biostat.jhsph.edu/~hcorrada/PracticalML/Data/zip_indices.rda"))

getd <- function(x,y,sigma=1) sweep(y,2,x)^2/sigma
getk <- function(d) exp(-rowSums(d))
sigmas <- c(1,10,100)

x <- zip.train[train.inds,-1][1:10,]
g <- zip.train[train.inds,1][1:10]


png("Plots/svm-01.png", width=864,height=864)
par(mfrow=c(4,1))
im <- do.call(rbind, lapply(1:10, function(i) zip2image(zip.train[train.inds,], i)))
image(im, col=gray(256:0/256), zlim=c(0,1), xlab="",ylab="")

d <- vector("list", length(sigmas))
k <- matrix(0, nr=nrow(x)-1, nc=length(sigmas))

for (i in seq_along(sigmas)) {
  d[[i]] <- getd(x[1,], x[-1,], sigma=sigmas[i])
  k[,i] <- getk(d[[i]])

  tmp <- cbind(g[-1],d[[i]])
  im <- do.call(rbind, lapply(1:9, function(i) zip2image(tmp, i)))
  image(im, col=gray(256:0/256), zlim=c(0,1), xlab="", ylab="",main=sprintf("sigma=%d", sigmas[i]))

}
dev.off()

png("Plots/svm-02.png", width=432, height=432)
par(mfrow=c(3,1))
xlabs <- paste(as.character(g[-1]),1:9,sep=":")
for (i in seq_along(sigmas)) {
  o <- order(k[,i])
  plot(k[o,i],type="h",xaxt="n", main=sprintf("sigma=%d", sigmas[i]), ylab="K")
  axis(1,at=1:nrow(k),labels=xlabs[o])
}
dev.off()

x <- zip.train[train.inds,-1]
g <- factor(zip.train[train.inds,1][-1])

k <- matrix(0, nr=nrow(x)-1, nc=3)
for (i in seq_along(sigmas)) k[,i] <- getk(getd(x[1,], x[-1,], sigma=sigmas[i]))

library(RColorBrewer)
mycol <- brewer.pal(n=3, "Dark2")

png("Plots/svm-03.png", width=432,height=432)
par(mfrow=c(3,1))
for (i in seq_along(sigmas)) {
  o <- order(k[,i])
  plot(k[o,i], type="h", xaxt="n", main=sprintf("sigma=%d", sigmas[i], ylab="K"), col=mycol[as.numeric(g)[o]], ylab="K")
  legend("topleft", levels(g), lty=1, col=mycol)
}
dev.off()





