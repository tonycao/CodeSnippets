# test

data<-read.table("/Users/tonycao/Table2.8_muzzle.dat", header=T)
#attach(data)
boxplot(data$Velocity ~ data$Area, main="boxplot of velocity by area", xlab="Area",ylab="Velocity")
Area.lv <- factor(data$Area)
data$Area.lv = Area.lv

contr.poly(4)
contrasts(data$Area.lv) = contr.poly(4)
summary(lm(Velocity~Area.lv))
