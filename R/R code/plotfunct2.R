plotfunct2=function(vect, title){
  
  if(is.numeric(vect)) {
    hist(vect, main=title)
  }
  else {
    prop <- CrossTable(vect)
    barplot(prop$prop.row, main=title)
  }
}