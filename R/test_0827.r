#import data
youthdata<-read.csv(file ="/Users/Shared/Dropbox/CodeSnippets/R/youthdata.csv",header = TRUE )

#attach the variables in the data file (then you can input the variable name directly)
attach(youthdata)

#str(youthdata)

results=aov(X.40religiosity_sum ~ X.8aFather_rec, data=youthdata)
summary(results)
oneway.test(X.40religiosity_sum ~ X.8aFather_rec, var.equal=TRUE)
oneway.test(X.40religiosity_sum ~ X.8aFather_rec)


leveneTest(X.40religiosity_sum ~ factor(X.8aFather_rec), data=youthdata)
