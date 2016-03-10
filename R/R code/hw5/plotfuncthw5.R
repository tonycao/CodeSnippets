load("ICPSR_34792/DS0001/HBS.rda")

#barchar and histgram description for basic demographical characteristics, gender and age:

plotfuncthw5=function(vect, title){
  if(is.numeric(vect)) {
    hist(vect, main=title)
  }
  else {
    frequency <- table(vect)
    prop <- frequency/sum(frequency)
    #print(prop)
    barplot(prop, main=title)
  }
}

plotfuncthw5(da34792.0001$Q1,"Gender")

plotfuncthw5(da34792.0001$Q3B,"Age")

#boxplot drawing:

# life satisfaction by Family Affluence
for( i in 1:length(unique(da34792.0001$Q6_COMP))){
  assign(paste0("data",i),subset(da34792.0001,
                                 Q6_COMP==unique(da34792.0001$Q6_COMP)[i]))
}

data<-list(data2,data3,data4,data5,data6,data7,data8)

for( i in 2:8){
  J<-unique(da34792.0001$Q6_COMP)[i]
  plot(get(paste0("data",i))$Q11,get(paste0("data",i))$Q7,xlab="Family        
       Affluence",ylab="Life Satisfaction",
       main=paste("Life Satisfaction by Family 
                  Affluence"),sub=strsplit(as.character(J),")")[[1]][2])
}

# life satisfaction by race 
for( i in 1:length(unique(da34792.0001$Q6_COMP))){
  assign(paste0("datarace",i),subset(da34792.0001,
                                 Q11==unique(da34792.0001$Q11)[i]))
}

datarace<-list(datarace4, datarace1, datarace2, datarace6, datarace3)

for(i in c(4, 1, 2, 6, 3)) {
  J<-unique(da34792.0001$Q11)[i]
  plot(get(paste0("datarace",i))$Q6_COMP, get(paste0("datarace", i))$Q7, xlab="
       Family Affluence", ylab="Life Satisfaction",
       main=paste("Life Satisfaction by Race"), sub=strsplit(as.character(J),")")[[1]][2])
}