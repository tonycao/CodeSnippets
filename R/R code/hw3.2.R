#hw3 1

data(studentdata)

for (i in c(2, 8, 9, 10)) {
  
  #if (type == typeof(studentdata[,i])) {
    print(i)
    hist(studentdata[studentdata[,11]=="water",i], xlab=names(studentdata)[i], ylab=paste(names(studentdata)[i]),
            main=paste('Histogram of' ,names(studentdata)[i], 'for students prefer drinking water'),
            col='slateblue')
    paste()
  #}
}
