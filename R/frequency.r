#frequency table

#data<- c(sample(10:20, 44, TRUE))

Fre_gender<-table(data,  exclude=NULL)


# valid case percentage
Per_gender<-prop.table(Fre_gender)

validPer_gender<-prop.table(table(data))

percentage<-(Per_gender*100)
percentage<-paste(round(100*Per_gender,2),"%",sep="")

tmp<-Per_gender

#cbind(validPer_gender, 0)
table<-cbind(Fre_gender,percentage, validPer_gender)
