#hw3 1

data(studentdata)

for (i in 1 : length(studentdata)) {
  type <- 'double'
  if (type == typeof(studentdata[,i])) {
    print(i)
    boxplot(studentdata[,i]~Gender, xlab='Gender', ylab=paste(names(studentdata)[i]),
            main=paste('Boxplots of' ,names(studentdata)[i], 'in studendata'),
            col='slateblue')
    paste()
  }
}
