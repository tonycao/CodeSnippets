
#frequency table function, two parameters, 'd' presents data, 'v' presents variable's column number
freq.table<-function(d,v){
  var<-d[,v]
  levels<-sort(unique(var))
  ft<-matrix(0,nrow=length(levels)+2,ncol=4,
             dimnames = list(c(levels,"missing","Total"),
                             c("Frequency","Percentage","Valid.Percentage","Cumulative.Percentage")))
  for (i in 1:(nrow(ft)-2)) {
    ft[i,1]=sum(!is.na(var[var==levels[i]]))
  }
  ft[nrow(ft)-1,1]=sum(is.na(var))
  ft[nrow(ft),1]=length(var)
  
  ft[,2]=ft[,1]/length(var)
  ft[,3]=ft[,1]/sum(ft[1:length(levels),1])
  ft[,4]=cumsum(ft[,3])
  ft[(nrow(ft)-1):nrow(ft),3:4]<-NA
  return(ft)
}