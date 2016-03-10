CD4.data <- read.table("../Data/cd4.data",
                       col.names=c("Time","CD4","Age","Packs",
                         "Drugs","Sex","Cesd","ID")) #READ IN DATA 
attach(CD4.data) ##attach data frame, now you can use just the names
o <- order(Time)

###First Figure
png("Plots/plot-07-00.png",width=432,height=432,pointsize=12)
###Running-mean and running-line 
o <- sample(1:length(Time),400) ##to make it fast for example look at only 400
plot(Time[o],CD4[o],pch=".",main="Running Mean")
b <- c(-2,1,3) - 0.5
e <- b + 1
for(i in 1:length(b)){  
  abline(v=c(b[i],e[i]),pch=2)
  oo <- o[Time[o]>=b[i] & Time[o]<=e[i]]
sapply(oo,function(i) points(Time[oo],CD4[oo],pch=1))
lines(range(Time[oo]),rep(mean(CD4[oo]),2))
}
aux <- ksmooth(Time[o],CD4[o],kernel="box",bandwidth=1,x.points=unique(Time[o])) ##box is default!
lines(aux$x,aux$y)
dev.off()

##kernel smoother
png("Plots/plot-07-01.png",height=432,width=432,pointsize=12) 
plot(Time[o],CD4[o],main="Kernel Smoother",pch=".")
aux <- ksmooth(Time[o],CD4[o],kernel="normal",bandwidth=1,x.points=unique(Time[o]))
lines(aux$x,aux$y)
dev.off()

png("Plots/plot-07-02.png",height=432,width=432,pointsize=12)
o <- sample(1:length(Time),400) ##to make it fast for example look at only 400
xx <- sort(Time[o])
aux11 <- ksmooth(xx,c(1,rep(0,length(o)-1)),kernel="normal",bandwidth=1,x.points=unique(xx)) 
plot(aux11$x,aux11$y,type="l",xlab="Time",ylab="Weights",main="Kernels",col=2)
rug(xx)
oo<- aux11$y>6.030458e-06
points(aux11$x[oo],aux11$y[oo],lty=2,pch="x",cex=0.5)
aux12 <- ksmooth(xx,c(1,rep(0,length(o)-1)),kernel="box",bandwidth=1,x.points=unique(xx))
lines(aux12$x,aux12$y,lty=2,col=2)
oo <- aux12$y>6.030458e-06
points(aux12$x[oo],aux12$y[oo],lty=2,pch="x",cex=0.5)
##
aux21 <- ksmooth(xx,c(rep(0,round(length(o)/2)),1,rep(0,length(o)-round(length(o)/2)-1)),kernel="normal",bandwidth=1,x.points=unique(xx))
lines(aux21$x,aux21$y,type="l",col=3)
oo<- aux21$y>6.030458e-06
points(aux21$x[oo],aux21$y[oo],lty=2,pch="x",cex=0.5)
aux22 <- ksmooth(xx,c(rep(0,round(length(o)/2)),1,rep(0,length(o)-round(length(o)/2)-1)),kernel="box",bandwidth=1,x.points=unique(xx))
lines(aux22$x,aux22$y,lty=2,col=3)
oo<- aux22$y>6.030458e-06
points(aux22$x[oo],aux22$y[oo],lty=2,pch="x",cex=0.5)
##
aux31 <- ksmooth(xx,c(rep(0,round(length(o)*.9)),1,rep(0,length(o)-round(length(o)*.9)-1)),kernel="normal",bandwidth=1,x.points=unique(xx))
lines(aux31$x,aux31$y,type="l",col=4)
oo<- aux31$y>6.030458e-06
points(aux31$x[oo],aux31$y[oo],lty=2,pch="x",cex=0.5)
aux32 <- ksmooth(xx,c(rep(0,round(length(o)*.9)),1,rep(0,length(o)-round(length(o)*.9)-1)),kernel="box",bandwidth=1,x.points=unique(xx))
lines(aux32$x,aux32$y,lty=2,col=4)
oo<- aux32$y>6.030458e-06
points(aux32$x[oo],aux32$y[oo],lty=2,pch="x",cex=0.5)
dev.off()

# loess
##three plots are exactly the same except for the degrees used.
png("Plots/plot-07-03.png",height=864,width=864,pointsize=12)
o <- order(Time)
spans <-c(.05,.25,.75,.95) 
par(mfrow=c(2,2),err=-1,oma=c(0,0,3,0)) ##err=-1 so that we get no warnings 
sapply(spans,function(span){
  plot(Time,CD4,pch=".",xlab="Time since zeroconversion",ylab="CD4",main=paste("span =",span),ylim=c(0,1500))##plots CD4 vs. Time 
  lines(Time[o],loess(CD4[o]~Time[o],span=span,degree=1)$fitted,col=4,lwd=2)
  })
mtext(side=3,"Degree=1",outer=T,cex=1.3,line=0)
dev.off()

png("Plots/plot-07-04.png",height=864,width=864,pointsize=12)
o <- order(Time)
spans <-c(.05,.25,.75,.95) 
par(mfrow=c(2,2),err=-1,oma=c(0,0,3,0)) ##err=-1 so that we get no warnings 
sapply(spans,function(span){
  plot(Time,CD4,pch=".",xlab="Time since zeroconversion",ylab="CD4",main=paste("span =",span),ylim=c(0,1500))##plots CD4 vs. Time 
  lines(Time[o],loess(CD4[o]~Time[o],span=span,degree=2)$fitted,col=4,lwd=2)
  })
mtext(side=3,"Degree=2, the default",outer=T,cex=1.3,line=0)
dev.off()

png("Plots/plot-07-05.png",height=864,width=864,pointsize=12)
o <- order(Time)
spans <-c(.05,.25,.75,.95) 
par(mfrow=c(2,2),err=-1,oma=c(0,0,3,0)) ##err=-1 so that we get no warnings 
sapply(spans,function(span){
  plot(Time,CD4,pch=".",xlab="Time since zeroconversion",ylab="CD4",main=paste("span =",span),ylim=c(0,1500))##plots CD4 vs. Time 
  lines(Time[o],loess(CD4[o]~Time[o],span=span,degree=0)$fitted,col=4,lwd=2)
  })
mtext(side=3,"Degree=0",outer=T,cex=1.3,line=0)
dev.off()
detach(CD4.data)

diabetes <- read.table("../Data/diabetes.dat",header=T)
attach(diabetes)
fit1 <- lm(log(C.Peptide)~Age+Base.Deficit)
fit2 <- loess(log(C.Peptide)~Age*Base.Deficit)


png("Plots/plot-07-07.png",height=432,width=432,pointsize=12)
par(mfrow=c(1,1),mai=c(0,0,0,0))
newAge <- seq(min(Age),max(Age),len=40)
newBase <- seq(min(Base.Deficit),max(Base.Deficit),len=40)
newcov <- expand.grid(Age=newAge,Base.Deficit=newBase)
surf <- matrix(predict(fit2,newcov),40,40)
persp(newAge,newBase,surf,xlab="Age",ylab="Base Deficit",zlab="Predicted",theta=-35,phi=30,shade=.35,col=5)
dev.off()
detach(diabetes)

# degrees of freedom
png("Plots/plot-06-01.png", width=864, height=432, pointsize=12)
n <- 100
x <- rnorm(n);y <- rnorm(n)
lambda <- seq(0.05,1,len=50)
df <- sapply(lambda,function(l) if(l==0) return(n) else return(sum(loess(y~x,span=l)$trace.hat)))
par(mfrow=c(1,2))
plot(lambda,df,main="Loess",type="l")
lambda <- seq(0.01,2,len=100)
df <- sapply(lambda,function(l) smooth.spline(x,y,spar=l,all.k=T)$df)
plot(lambda,df,main="Smoothing spline",type="l")
dev.off()

###different definitions of degrees of freedom
png("Plots/plot-06-02.png", height=432, width=432,pointsize=12)
n <- 100
x <- sort(runif(n,0,1))
Y <- diag(n)
lambda <- seq(.02,1,len=10)
df <- matrix(0,length(lambda),3)
for(i in 1:length(lambda)){
  l <- lambda[i]
  S <- apply(Y,1,function(yy) loess(yy~x,span=l)$fitted)
  aux1 <- sum(diag(S));aux2 <- sum(diag(S%*%t(S)))
  df[i,] <- c(aux1,aux2,2*aux1-aux2)
}
par(mfrow=c(1,1))
plot(lambda,df[,1],ylim=range(df),type="l",ylab="df",log="y")
lines(lambda,df[,2],lty=2)
lines(lambda,df[,3],lty=3)
legend(.7,range(df)[2]*.95,c("tr(S)","tr(SS')","2tr(S)-tr(SS')"),lty=c(1,2,3))
dev.off()

# strontium dataset
aux <- read.table("../Data/Sr.dat")
x <- aux[,1]; y <- aux[,2]

png("Plots/plot-06-00-01.png",height=432,width=432,pointsize=12)
plot(x,y,xlab="Time in millions of years", ylab="Strontium ratios")
abline(v=66.4)
dev.off()

pen <- c(0.1,.5,1,1.5)
png("Plots/plot-06-00-02.png",height=864,width=864,pointsize=12)
par(mfrow=c(2,2))
sapply(1:length(pen),function(i){
plot(x,y,xlab="Time in millions of years", ylab="Strontium ratios",main=paste("penalty=",as.character(pen[i])))
  smooth <- smooth.spline(x,y,spar=pen[i])
  lines(smooth$x,smooth$y,lty=i,lwd=1.5)
})
dev.off()

###might as well draw the columns of the smoothing spline
png("Plots/plot-06-03.png")
n <- 101
x <- sort(runif(n,0,1))
Y <- diag(n)
S <- apply(Y,1,function(yy) smooth.spline(x,yy,spar=.8,all.knots=T)$y)
par(mfrow=c(3,2))
for(i in seq(1,101,len=6))
  plot(x,S[i,],ylab=paste(i,"th row of S",sep=""),type="b")
dev.off()

n <- 30
x <- sort(runif(n,0,1))
##first linear to show example
X <- cbind(1,x)
S <- X%*%solve(t(X)%*%X)%*%t(X)
aux <- eigen(S,symmetric=T)
U <- aux$vector; D <- diag(aux$values) ###S should be UDU'

png("Plots/plot-06-04.png")
par(mfrow=c(1,2),oma=c(0,0,2,0))
plot(diag(D),xlab="",ylab="Eigenvalues")
par(mfrow=c(2,2))
par(mfg=c(1,2))
plot(x,U[,1],xlab="x",ylab="First Eigenvector")
par(mfg=c(2,2))
plot(x,U[,2],xlab="x",ylab="Second Eigenvector")
mtext("Simple linear regression",outer=T,side=3,line=0,cex=1.5)
dev.off()

###NOW for smoothing splines
n <- 30
x <- sort(runif(n,0,1))
png("Plots/plot-06-05.png")
Y <- diag(n)
S <- apply(Y,1,function(yy) smooth.spline(x,yy,spar=.6,all.knots=T)$y)
aux <- eigen(S,symmetric=T)
U <- aux$vector; D <- diag(aux$values) ###S should be UDU'
par(mfrow=c(1,1))
plot(diag(D),xlab="",ylab="Eigenvalues")
dev.off()

png("Plots/plot-06-06.png")
par(mfcol=c(5,2),mai=c(.3,.5,.1,.3),oma=c(0,0,2,0))
for(i in 1:10)
  plot(x,U[,i],xlab="x",ylab=paste(i,"th Eigenvector",sep=""),type="l")
mtext("Smoothing spline",outer=T,side=3,line=0,cex=1.5)
dev.off()

png("Plots/plot-06-07.png")
par(mfcol=c(5,2),mai=c(.3,.5,.1,.3),oma=c(0,0,2,0))
for(i in 11:20)
  plot(x,U[,i],xlab="x",ylab=paste(i,"th Eigenvector",sep=""),type="l")
mtext("Smoothing spline",outer=T,side=3,line=0,cex=1.5)
dev.off()


png("Plots/plot-06-08.png")
par(mfcol=c(5,2),mai=c(.3,.5,.1,.3),oma=c(0,0,2,0))
for(i in 21:30)
  plot(x,U[,i],xlab="x",ylab=paste(i,"th Eigenvector",sep=""),type="l")
mtext("Smoothing spline",outer=T,side=3,line=0,cex=1.5)
dev.off()

###REACT STUFF
n <- 48
x <- (1:n)/n
y <- scan("../Data/mouse-bt.dat")
U <- cbind(rep(1/sqrt(n),n),
           sapply(1:(n/2-1),function(k) sqrt(2/n)*cos(2*pi*k*x)),
           sapply(1:(n/2-1),function(k) sqrt(2/n)*sin(2*pi*k*x)),
           1/sqrt(n)*cos(pi*n*x))


png("Plots/plot-06-09.png")
par(mfrow=c(5,2),mai=c(.3,.5,.1,.3),oma=c(0,0,2,0))
for(i in 1:5){
  plot(x,U[,i+1],xlab="x",ylab=paste(i,"th FFT row",sep=""),type="l")
  plot(x,U[,n/2+i],xlab="x",ylab=paste(i,"th FFT row",sep=""),type="l")
}
dev.off()



##fft of data
aux <- fft(y)/sqrt(n)
z <- c(Re(aux[1]),
       as.vector(t(matrix(c(Re(aux[2:(n/2)]),Im(aux[2:(n/2)])),ncol=2))),
       Re(aux[n/2+1]))
##this functions recieves a fft and returns an estimate of f
ifft <- function(z){
  n <- length(z)
  aux <- complex(real=z[seq(2,n-1,2)],im=z[seq(3,n-1,2)])
  yhat <-Re(fft(c(z[1],aux,z[n],rev(Conj(aux))),inv=T)/sqrt(n))
}

png("Plots/plot-06-10.png")
par(mfrow=c(2,2))
for(m in c(1,4,8,23)){
  plot(x,y,main=paste(m,"non zero"))
  zhat <- z*c(rep(1,1+2*m),rep(0,n-2*m-1))
  lines(x,ifft(zhat))
}
dev.off()


###We need to define the average and PAV functions
average <- function(y, wt = rep(1, length(y)))
{
# compute a weighted average of a vector, y
        if(any(is.na(wt))) stop("NA's not allowed for wt")
        if(any(wt < 0))
                stop("wt must be a vector of NON-NEGATIVE weights")
        if(length(wt) != length(y)) stop(
                "y and wt must be vectors of the same length")
# if any observations have Infinite weight, return the simple
# (unweighted) average of only those observations (giving no
# weight to observations with finite weight)
        if(any(wt == Inf)) {
                wt[wt < Inf] <- 0
                wt[wt == Inf] <- 1
        }
# if all weights are zero, return the simple (unweighted)
# average of y
        if(sum(wt) == 0)
                wt <- rep(1, length(wt))
        return(sum((y * wt)/sum(wt)))
}


PAV <- function(y, wt = rep(1,p))
{
### This is a modification of Derick's PAV program
### (Weighted) Pool-Adjacent-Violators (PAV) algorithm
### for non-parametric monotonic (decreasing) regression of y on x
  n <- length(y)
  if(n != length(wt))
    stop("y, and wt must be vectors of equal length")
  yhat <- y       # initialize while loop
  j <- count <- 1
  k <- 2
  support <- vector("numeric", n)
  support[count] <- j
  while(k <= n) {
    while(yhat[j] < yhat[k]) {
      yhat[j:k] <- average(y[j:k], wt[j:k])
      if(yhat[support[count]] < yhat[k]) {
        j <- support[count]
        if(count > 1)
          count <- count - 1
      }
      else {
        k <- ifelse(k == n, k, k + 1)
      }
    }
    count <- count + 1
    support[count] <- j
    j <- k
    k <- k + 1
  }
  return(list(y = yhat, wt))
}
png("Plots/plot-06-11.png")
par(mfrow=c(2,2))
plot(x,y,xlab="Time",ylab="Temperature",type="n",main="Harmonic Model")
points(x,y,col=4)
m <- 4
yhat <- z*c(rep(1,1+2*m),rep(0,n-2*m-1))
lines(x,ifft(yhat),col=9)
plot(2:48,abs(z[-1]),xlab="coefficient of z",ylab="Absolute value",type="h")
points(2:(1+2*m),abs(z[2:(1+2*m)]),col=3)
points((2+2*m):n,abs(z[(2+2*m):n]),col=4,pch=4)
abline(h=0)
plot(x,y,xlab="Time",ylab="Temperature",type="n",main="REACT")
points(x,y,col=4)
sigma2 <- .1520197 ##we got this from somewhere else
g <- 1 - sigma2/z^2
fhat <- PAV(g, z^2)$y
fhat <- sapply(fhat, function(x) max(x, 0))
fit1 <- ifft(z*fhat)
lines(x,fit1,col=9)
plot(2:48,abs(z[-1]),xlab="coefficient of z",ylab="Absolute value",type="h")
points(2:n,abs(z[2:n]),col=3)
points(2:n,abs(z*fhat)[-1],col=4,pch=4)
abline(h=0)
dev.off()


png("Plots/plot-06-12.png")
Y <- matrix(scan("../Data/all-mouse-bt.dat"),48,12,byrow=T)
Y <- sweep(Y,2,apply(Y,2,mean))
par(mfrow=c(1,1))
plot(rep(x,12),as.vector(Y),xlab="Time",ylab="Temperature")

lines(x,apply(Y,1,mean),lwd=3)
lines(x,fit1-mean(fit1),col=3,lty=2,lwd=3)
lines(x,ifft(yhat)-mean(ifft(yhat)),col=4,lty=3,lwd=3)
legend(0.05,1.5,c("Average","REACT","Harmonic"),lty=c(1,2,3),col=c(1,3,4))
dev.off()

auxplot<- function(){
  par(mai=c(0.3,0.2,0.05,0.1))
  layout(matrix(c(1,1,1,1,2,2,2,2,3,3,4,4,5,6,7,8), nr=4, byrow = TRUE))
  for(i in 2:9)  plot(x[i,],type="l",yaxt="n")
}

nmr <- read.table("http://www.stats.ox.ac.uk/~silverma/ebayes/sprogsetc/nmrresults.s")
nmr1 <- nmr[,1]

png("Plots/plot-06-13.png")
plot(nmr1,type="l",ylab="NMR Spectrum")
dev.off()

library(wavethresh)
N <- 2^8
y=diag(N)

#haar wavelet
x<-matrix(0,N-1,N) #initialize
for(level in 0:(log2(N)-1)){
  Index = seq(2^level,2^(level+1)-1)
  x[Index,]=apply(y,1,function(z)accessC(wd(z,filter=1),level))
  }
png("Plots/plot-06-14.png")
auxplot()
dev.off()

#daubechies wavelet
x<-matrix(0,N-1,N) #initialize
for(level in 0:(log2(N)-1)){
  Index = seq(2^level,2^(level+1)-1)
  x[Index,]=apply(y,1,function(z)accessC(wd(z),level))
  }
png("Plots/plot-06-15.png")
auxplot()
dev.off()

#apply wavelet to nmr data
aux <- wd(nmr1)
png("Plots/plot-06-16.png")
plot(aux)
dev.off()

#compare methods
png("Plots/plot-06-17.png")
par(mfrow=c(2,2))
plot(nmr1,type="l",main="Original Data")
#get a parsimonious wavelet fit
aux.thresh<-threshold(aux)
wave.thresh<-wr(aux.thresh)
plot(wave.thresh,type="l",ylim=range(nmr1),main="wavelet threshold")
#smoothing spline
smoothspline <- smooth.spline(1:length(nmr1),nmr1)
plot(smoothspline$y,type="l",ylim=range(nmr1),main=paste("smoothing splines: df=",round(smoothspline$df)))
#loess
Loess <- loess(nmr1~c(1:length(nmr1)),span=1/20)
plot(Loess$fitted,type="l",ylim=range(nmr1),main="loess with span 5%")
dev.off()

#mouse data
y <- scan("../Data/mouse-bt.dat")
n <- 32
aux <- wd(y[1:n])
aux.thresh<-threshold(aux)
wave.thresh<-wr(aux.thresh)
png("Plots/plot-06-18.png")
plot(wave.thresh,type="l",xlab="Time",ylab="Body Temperature")
dev.off()
