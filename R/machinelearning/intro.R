library(MASS)

set.seed(1)
x <- mvrnorm(2000, mu=c(70,190), Sigma=matrix(c(3^2, .5*3*15, .5*3*15, 15^2), 2, 2))
png("Plots/intro-plots-01.png", width=432, height=432, pointsize=12)
par(mgp=c(1.25,.5,0), mar=c(2.25, 2.1, 1, 1))
plot(x, xlab="Height", ylab="Weight", cex=.5, col="darkblue")
abline(v=mean(x[,1]), h=mean(x[,2]), lty=2, col="red")
dev.off()

X0 <- 73
png("Plots/intro-plots-02.png", width=432, height=432, pointsize=12)
par(mgp=c(1.25,.5,0), mar=c(2.25, 2.1, 1, 1))
plot(x, xlab="Height", ylab="Weight", cex=.5, col="darkblue")
abline(v=mean(x[,1]), h=mean(x[,2]), lty=2, col="red")
abline(v=c(X0-.5,X0+.5), col="red", lwd=2)
X <- x[,1]
Y <- x[,2]
fit1 <- lm(Y~X)
points(X0, predict(fit1, newdata=list(X=X0)), col="orange", pch="A", cex=2)
dev.off()

png("Plots/intro-plots-03.png", width=432, height=432, pointsize=12)
par(mgp=c(1.25,.5,0), mar=c(2.25, 2.1, 1, 1))
plot(x, xlab="Height", ylab="Weight", cex=.5, col="darkblue")
abline(v=mean(x[,1]), h=mean(x[,2]), lty=2, col="red")
abline(v=c(X0-.5,X0+.5), col="red", lwd=2)
abline(fit1, col="orange", lwd=2)
points(X0, predict(fit1, newdata=list(X=X0)), col="orange", pch="A", cex=2)
dev.off()

# read in data
CD4.data <- read.table("../Data/cd4.data", col.names=c("Time", "CD4", "Age", "Packs", "Drugs", "Sex", "Cesd", "ID"))

# attach data frame, now you can refer to the variable names
attach(CD4.data)

png("Plots/intro-plots-04.png", width=432, height=432, pointsize=12)
par(mfrow=c(1,1))
plot(Time, CD4, pch=".", main="CD4 counts vs. Time", xlab="Time since zeroconversion", ylab="CD4")
dev.off()

                       
