
#include <cstdio>
#include <string>

#define N 128
int matrix[N][N] = {0};

//http://blog.chinaunix.net/uid-26874207-id-4206383.html
void fun(int n)
{
    int i;
    int j;
    if (n<=0)
    {
        return;
    }
    if (n>2)
    {
        fun(n/2);
        for (i=1;i<=n/2;i++)
        {
            for (j=n/2+1;j<=n;j++)
            {
                matrix[i][j] = matrix[i][j-n/2] + n/2;
            }
        }
        for (i=n/2+1;i<=n;i++)
        {
            for (j=1;j<=n/2;j++)
            {
                matrix[i][j] = matrix[i-n/2][j+n/2];
            }
        }
        for (i=n/2+1;i<=n;i++)
        {
            for (j=n/2+1;j<=n;j++)
            {
                matrix[i][j] = matrix[i-n/2][j-n/2];
            }
        }
    }
    else
    {
        matrix[1][1] = 1;
        matrix[1][2] = 2;
        matrix[2][1] = 2;
        matrix[2][2] = 1;
    }
}

int main()
{
    int len = 4;
    fun(len);
    
    int i,j;
    for (i = 1;i <= len;i++)
    {
        for (j = 1; j <= len; j++)
        {
            printf("%d ",matrix[i][j]);
        }
        printf("\n");
    }
}


