
require(ggplot2)
require(reshape2)

theta<-c(-3,-2,-1,0,1,2,3,4)
L<-c(0.5,2,1,3,1,3,2,0.5)
p<-c(0.1,0.3,0.05,0.15,0.05,0.1,0.2,0.05)
pos<-c(0.026,0.312,0.026,0.234,0.026,0.156,0.208,0.012)

#dat = melt(c(theta, L, p, pos))

#ggplot(aes(x = theta, y = p), data = dat) +  
#  geom_point() + geom_line()


df <- data.frame(theta = theta, prior = p, likelihood = L, posterior = pos)
head(df)


g <- ggplot(df) +                    # basic graphical object
  geom_point(aes(x=theta,y=prior, colour="red", shape="prior"), size=5) +  # first layer
  geom_point(aes(x=theta,y=likelihood, colour="green", shape="likelihood"), size=5) + # second layer
  geom_point(aes(x=theta,y=posterior, colour="blue", shape="posterior"), size=5) +
  scale_colour_manual(name = "",labels=c("prior","likelihood","posterior"), values=c("red","green","blue")) +
  scale_shape_manual(name ="", labels=c("prior","likelihood","posterior"), values=c(19, 17, 15)) 

g <- g + ylab("probability") + xlab("theta")
g

plot(theta, L, type="b", xlab=expression(theta), ylab="", ylim=c(0,3), col="black")
lines(theta, p, type="b", pch=18, col="green")
lines(theta, pos, type="b", pch=20, col="red")
legend("topleft", legend = c("likelihood","prior","posterior"), col=c("black","green","red"), pch=c(1, 18, 20))

