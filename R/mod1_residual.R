library(car)
library(leaps)
library(lmtest)


data <- read.table("./project1_data.txt")
attach(data)


#set v7 as dummy variable, north=1, south=0
V8<-rep(NA,47)
for (i in 1:47){
  if (V7[i] == 'n')
    V8[i] =1
  else
    V8[i] = 0 
}
data[,8]<-V8

#scattor plot matrix
pairs(data[,-7])
#correlation matrix
cor(data[,-7])
#preliminarily check the distribution of each variable
boxplot(data[,c(-7,-8)])



#stepwise regression
leaps=regsubsets(V5~V1+V2+V3+V4+V6+V8,data=data)

plot(leaps, scale="adjr2")
plot(leaps, scale="bic")

#standard multiple linear regression
mod1<-lm(V5~V1+V2+V3+V4+V6+V8)
mod2<-lm(V5~V1+V2+V3+V4+V6)

fit <- lm.ridge(lpsa~.,prostate,lambda=seq(0,100,len=501))
plot(fit)


#residual diagnostic
residualPlots(mod1)

plot(mod2)

bptest(mod3)



#normalize the dataset

data_mat<-matrix(nrow=47,ncol=7)
colnames(data_mat)<-c("V1","V2","V3","V4","V5","V6","V8")
for (i in 1:7){
  if (i == 7){
    data_mat[,i]<-data[,i+1]
  }
  else data_mat[,i]<-data[,i]
}

maxs<-apply(data_mat,2,max)
mins<-apply(data_mat,2,min)

data_nor<-scale(data_mat,center=mins,scale=maxs-mins)

Dfrm<-data.frame(V1 = data_nor[,1],V2 = data_nor[,2],V3 = data_nor[,3],V4 = data_nor[,4],V5 = data_nor[,5],V6 = data_nor[,6],V8 = data_nor[,7])


#data after deleting outliers
data2<-data[-c(35,6,3),]
mod3<-lm(V5~V1+V2+V3+V4+V6,data=data2) #the ADJ R square increased to 0.8255



# robust regression

#library(foreign)
#library(MASS)

#mod_robust<- rlm(V5 ~ V1 + V2 + V3 + V4 + V6 + V8)
#summary(mod2)


#polynomial regression
mod4<-lm(V5 ~ V1 + V2^2 + V3 + V4^2 + V6,data=data2)


#weighted linear regression
mod5<-lm(V5~V1+V2+V3+V4+V6,data=data2,weights=mod3$res^-2)