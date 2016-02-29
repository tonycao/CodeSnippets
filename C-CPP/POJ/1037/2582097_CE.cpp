#include <stdio.h>
#include <memory.h>
const int maxn=22;
long long ans[maxn][maxn][2];
int  i,j,m,n,s,t,way[maxn];
bool use[maxn];
long long k;
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
void writeans(int depth,long long num,int flag,int st)
{
    long long c=0;
    int i,j,nxtst;
    if (depth>n) {printf("\n");return;}
    if (depth!=1) printf(" ");
    for (i=2*st;i<=2*(n-depth+1)+1&& c<num;i++) 
    if (i%2==flag || flag==-1)
            c+=ans[depth][i/2][i%2];
    i--;
    printf("%d",pos(i/2));
    if (i%2==0) nxtst=1;else nxtst=i/2;
    writeans(depth+1,num-(c-ans[depth][i/2][i%2]),1-i%2,nxtst);
}     
void makeans()
{
    int i,j,k;
    memset (ans,0,sizeof(ans));
    ans[n][1][0]=1;ans[n][1][1]=1;
    for (i=n-1;i>=1;i--)
    for (j=1;j<=n-i+1;j++)
    {
       for (k=1;k<=j-1;k++) ans[i][j][0]+=ans[i+1][k][1];
       for (k=j+1;k<=n-i+1;k++) ans[i][j][1]+=ans[i+1][k-1][0];
    }
}        
    
int main()
{
    scanf("%d",&s);
    for (t=1;t<=s;t++)
    {
        scanf("%d %lld",&n,&k);
        makeans();
        memset (use,false,sizeof(use));
        writeans(1,k,-1,1);
    }
}         

