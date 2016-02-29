#include <stdio.h>
#include <memory.h>

int wi[50000],hi[50000];
int n, i,j,curr;
long int max, w, h, temp;

int main()
{
    memset(wi, 0, sizeof(wi));
    memset(hi, 0, sizeof(hi));
    scanf("%d",&n);
    while(n>=0)
    {
        for(i=0; i<n; i++)
        {
            scanf("%d %d", &wi[i], &hi[i]);
        }
        max = 0;
        w = 0;
        h = 0;
        for( i=0; i<n; i++)
        {
             w = 0;
             h = hi[i];
             for (j=i; j <n; j++)
             {
                 w += wi[j];
                 h = hi[j]<h?hi[j]:h;
                 //printf("w = %d,h = %d,mul = %d\n",w, h, w*h);
                 max = (w*h) >max?(w*h):max;
             }
             
        }
        printf("%ld\n", max);
        scanf("%d",&n);
    }
    return 0;
}