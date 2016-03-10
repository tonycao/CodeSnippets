xx <- seq(-5,5,len=100)

png("Plots/high_dimension-01.png", width=864, height=432)
par(mfrow=c(1,3), mgp=c(1.25,.5,0), mar=c(2.25, 2.1, 1, 1))
plot(xx,xx, lty="dashed", col="black", type="l", main="Ridge regression (lambda=2)", xlab="", ylab="")
lines(xx,xx/(1+2), col="orange", lwd=2)

plot(xx,xx, lty="dashed", col="black", type="l", main="Best subset", xlab="", ylab="")
lines(xx,xx*ifelse(abs(xx)<2, 0,1), col="orange", lwd=2)

plot(xx,xx, lty="dashed", col="black", type="l", main="Lasso (lambda=2)", xlab="", ylab="")
lines(xx,sign(xx)*pmax(abs(xx)-2,0), col="orange", lwd=2)
dev.off()


