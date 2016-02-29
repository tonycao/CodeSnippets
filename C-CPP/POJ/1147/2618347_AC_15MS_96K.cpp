#include <stdio.h>

#define max 3000

int main()
{
    int n;
    int k;
    int binary[max];
    //int first[max];
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
    for(i=0, k=0; i<zero; i++)
    {
         while(binary[k]) k++;
         next[i]=k;
         k++;
         //first[i]=0;
    }
    for(k=0; i<n; i++)
    {
         while(!binary[k]) k++;
         next[i]=k;
         k++;
         //first[i]=1;
    }    
    //printf("%d ",binary[next[0]]);
    int temp=next[0];
    for(i=0; i<n; i++)
    {
         printf("%d ",binary[temp]);
         temp=next[temp];       
    }
    //int c;
    //scanf("%d",&c);
    return 0;
}
