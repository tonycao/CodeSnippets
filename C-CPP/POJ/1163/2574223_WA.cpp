#include <stdio.h>
#include <memory.h>



int main()
{
    int a[100][100];
    int b[100][100];
    int sum1=0,sum2=0;
    int n;
    while(scanf("%d",&n))
    {
        memset(b, 0, sizeof(b));
        for(int i=0; i < n; i++ )
            for(int j=0; j <= i; j++)
                scanf("%d",&a[i][j]);
        b[0][0]=a[0][0];
        for(int k=1; k < n; k++)
            for(int l=0; l <= k; l++)
            {
                if(l < k)
                     sum1 = b[k-1][l] + a[k][l];
                if(l > 0)
                     sum2 = b[k-1][k-1] + a[k][l];
                if(sum1>sum2)
                    b[k][l]=sum1;
                else
                    b[k][l]=sum2;  
                    
            }
        int temp = 0;
        for(int m=0; m < n; m++)
        {
            if(temp<b[n-1][m])
                temp = b[n-1][m];
        }
        printf("%d",temp);
        return 0;                  
    }
        
}