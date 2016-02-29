/*
  Author: Tony Cao
  Date: 28-08-07 17:41
  Description: 1037 on POJ
*/
#include <stdio.h>
#include <memory.h>

#define maxn 20

int s, n;
__int64 k;
__int64 ans[maxn][maxn][2];
bool use[20];


void make()
{
	int i, j, k;
	memset(ans, 0, sizeof(ans));
	ans[0][0][0]=1;
	ans[0][0][1]=1;
	for(i = 1; i < 20; i++)
	for(j = 0; j <= i; j++)
	{
		for(k = 0; k <= j-1; k++) ans[i][j][0] += ans[i-1][k][1];
		for(k = j + 1; k <= i; k++) ans[i][j][1] += ans[i-1][k-1][0];  
	}
}

int pos(int s)
{
    int i,n;
    i=0;n=0;
    while (n<s)
    {
        i++;
        if (!use[i]) n++;
    }
    use[i]=true;
    return i;
}          

void count(__int64 num, int depth, int flag, int init)
{
     __int64 c = 0;
     int i, nstinit;
     if(depth==0) {printf("\n");return;}
     if(depth!=n) printf(" ");
     for( i = 2*init; i <= 2*(depth-1)+1 && c<num; i++)
     {    if(i%2 == flag || flag==-1) 
              c += ans[depth-1][(i/2)][i%2];
     }
     i--;
     printf("%d", pos((i/2)+1));
      
     if(i%2 == 0) nstinit=0; else nstinit=(i/2);
     count(num-(c-ans[depth-1][(i/2)][i%2]),depth-1,1-i%2,nstinit);
}

int main()
{
    scanf("%d",&s);
    make();
    while(s--)
    {
        scanf("%d %I64d", &n, &k);
        memset(use, false, sizeof(use));
        count(k,n,-1,0);
    }
    return 0;    
}
