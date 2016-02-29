#include<stdio.h>
#include <memory.h>
int main()
{
    int a[100][100];
    int b[100][100];
    int n;
    int sum1,sum2;
    int max =-1;
    while(scanf("%d",&n) != EOF)
  {  
    memset(b,0,sizeof(b));
    max = -1;
   for(int p = 0; p<n; p++)
    for(int k = 0; k<=p; k++)
     scanf("%d",&a[p][k]);
     
    b[0][0]=a[0][0]; 
   for(int i =1;i<n;i++)
    for(int j = 0; j<=i; j++)
     {
       sum1 = 0; sum2 = 0;
       if(j<i)
         sum1 = b[i-1][j]+a[i][j];
       if(j>0)
          sum2 = b[i-1][j-1]+a[i][j];
          
       if(sum1>sum2)
       b[i][j] =sum1;
       else b[i][j] =sum2;         
     } 
    for(int index = 0; index <n; index++)
      if(max<b[n-1][index]) max =b[n-1][index];
     
    printf("%d\n",max);
 }
   
}