tstatistic=function(x,y){
  m=length(x)
  n=length(y)
  sp=sqrt(((m-1)*var(x)+(n-1)*var(y))/(m+n-2))
  t.stat=(mean(x)-mean(y))/(sp*sqrt(1/m+1/n))
  return(t.stat)
}