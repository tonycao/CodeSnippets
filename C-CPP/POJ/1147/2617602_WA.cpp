#include <stdio.h>
#include <memory.h>

#define max 3000

int main()
{
    int n;
    int binary[max];
    int next[max];
    int one=0;
    int zero=0;
    scanf("%d",&n);
    int i;
    for(i=0; i < n; i++)
    {
         scanf("%d",&binary[i]);
         if(binary[i]==1) one++;
         else zero++;
    }
    for(i=0, n=0; i<zero; i++)
    {
         while(binary[n]) n++;
         next[i]=n;
    }
    for(i=zero,n=0; i<n; i++)
    {
         while(!binary[n]) n++;
         next[i]=n;
    }
    for(i=0; i<n; i++)
    {
         printf("%d ",binary[next[i]]);       
    }
    //scanf("%d",&n);
    return 0;
}