#include <stdio.h>
#include <memory.h>

int wi[50000],hi[50000];
int n, i;
int max, w, h, temp;

int main()
{
    memset(wi, 0, sizeof(wi));
    memset(hi, 0, sizeof(hi));
    scanf("%d",&n);
    while(n)
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
             if(i==0)
             {
                 w += wi[i];
                 h += hi[i];
                 max = w*h;
             }
             else
             {
                 if(hi[i]>hi[i-1])
                 {
                     w = wi[i];
                     h = hi[i];
                     temp = w*h;
                     max = temp > max  ? temp : max;
                 }
                 else
                 {
                     w += wi[i];
                     h = hi[i];
                     temp = w*h;
                     max = temp > max ? temp : max;
                 }
             }
        }
        printf("%d\n", max);
        scanf("%d",&n);
    }
    return 0;
}
