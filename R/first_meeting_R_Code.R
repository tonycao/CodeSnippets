require(gdata)
data<-read.xls("/Users/Shared/Dropbox/CodeSnippets/R/0th Order without names.xlsx",sheet=1,header=TRUE)
#delete the observation didn't give response

data1<-data[data$Response=="Responded",]
summary(data1$Response)
summary(data$Response)

#recode the "Block8" five questions
#question1
data1$tech_skill<-NA
data1$tech_skill[data1$B1=="Yes"]<-1
data1$tech_skill[data1$B1=="No"]<-0
table(data1$tech_skill)
barplot(table(data1$tech_skill),xlab=levels(data$tech_skill),ylab="Frequencies",main="Do you think your involvement in LISA helped you gain technical skills in statistics?")

#question2
data1$non_tech_skill<-NA
data1$non_tech_skill[data1$B2=="Yes"]<-1
data1$non_tech_skill[data1$B2=="No"]<-0
table(data1$non_tech_skill)
barplot(table(data1$non_tech_skill),xlab=levels(data$non_tech_skill),ylab="Frequencies",main="Do you think your involvement in LISA helped you gain non-technical skills in statistics?")

#question3
data1$career<-NA
data1$career[data1$B3=="Yes"]<-1
data1$career[data1$B3=="No"]<-0
table(data1$career)
barplot(table(data1$career),xlab=levels(data$career),ylab="Frequencies",main="Do you think your involvement in LISA helped your professional career?")

#question4
data1$desire_stat<-NA
data1$desire_stat[data1$B4=="Yes"]<-1
data1$desire_stat[data1$B4=="No"]<-0
table(data1$desire_stat)
barplot(table(data1$desire_stat),xlab=levels(data$desire_stat),ylab="Frequencies",main="Do you think your involvement in LISA increased your desire to apply statistics to solve problems?")


#question5
data1$posi_impact<-NA
data1$posi_impact[data1$B5=="Yes"]<-1
data1$posi_impact[data1$B5=="No"]<-0
table(data1$posi_impact)
barplot(table(data1$posi_impact),xlab=levels(data$posi_impact),ylab="Frequencies",main="Do you think your involvement in LISA increased the chance that your work has a positive impact on your organization?")


#Technical impacts
#data1$t1<-NA
#data1$t1[data1$T1=="Strongly Disagree"]<-0
#data1$t1[data1$T1=="Disagree"]<-1
#data1$t1[data1$T1=="Neither Agree nor Disagree"]<-2
#data1$t1[data1$T1=="Agree"]<-3
#data1$t1[data1$T1=="Strongly Agree"]<-4

#recode of the scale variable loop

for (i in 1:10){
  
  data1[[paste('t',i, sep='')]]<-NA
  data1[[paste('t',i, sep='')]][data1[[paste('T',i,sep='')]]=="Strongy Disagree"]<-0
  data1[[paste('t',i, sep='')]][data1[[paste('T',i,sep='')]]=="Disagree"]<-1
  data1[[paste('t',i, sep='')]][data1[[paste('T',i,sep='')]]=="Neither Agree nor Disagree"]<-2
  data1[[paste('t',i, sep='')]][data1[[paste('T',i,sep='')]]=="Agree"]<-3
  data1[[paste('t',i, sep='')]][data1[[paste('T',i,sep='')]]=="Strongly Agree"]<-4
}

for(i in 1:10) {
  assign(paste('table',i, sep='.'), table(data1[[paste('t',i,sep='')]]))
}

total_sum<-0
for(i in 1:5){
  sum<-(table(data1[[paste('t',i,sep='')]])[i])*i
  sum
  total_sum<-total_sum+sum
}

cor(data1$tech_skill,data1$t1,method="pearson",use="complete.obs")

tech_vector<-cbind(data1$tech_skill,data1$t1)

