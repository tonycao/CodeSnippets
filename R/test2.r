# data<-read.table("/Users/tonycao/Desktop/dat.txt", header=T)
# 
# colnames(data)<-c("y","x1","x2","x3","x4")
# 
# head(data)
# attach(data)
# 
# I<-rep(1,48)
# X<-cbind(I,x1,x2,x3,x4)
# model1<-lm(y~X[,2:5])

setwd("~/")
library(gdata)
FA2004 <- read.xls("/Users/tonycao/Downloads/FA2004_13459_Spring2014.xlsx", sheet = 1, header = TRUE, skip = 1)

## Class figures
class <- factor(FA2004$Class, levels = c("Freshman","Freshman Honors",
                                        "Sophomore","Sophomore Honors","Junior","Junior Honors","Senior","Senior BS/MS"))
# class frequency
class.counts <- table(class)

# pie chart
pie(class.counts, main="FA 2004/13459 Spring 2014 Alan Weinstein, Class", 
    col = c("blue", "green", "gold", "firebrick1", "deeppink", "lightblue","purple", "brown"))

# bar plot
xx<-barplot(class.counts, main="FA 2004/13459 Spring 2014 Alan Weinstein, Class", 
            xlab="Class",ylim=c(0,250),col=c("blue", "green", "gold", "firebrick1", "deeppink", "lightblue","purple", "brown"))
text(x = xx, y = class.counts, label = class.counts, pos = 3, cex = 0.8, col = "black")
