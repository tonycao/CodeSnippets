#include <stdio.h>
#include <string.h>

int i, j, k, l, n, c[1010][3], m, r, pos;
int t[1010][1010], lt[1010], f[1010];

main()
{


    while(scanf("%d%d",&n,&r)&&n&&r)
    {
        for (i = 1; i <= n; i ++){scanf("%d",&c[i][0]);c[i][1] = 
c[i][0];c[i][2] = 1;}
        memset(lt,0,sizeof(lt));
        f[r] = -1;
        for (i = 0; i < n-1; i ++)
        {
            scanf("%d%d",&j,&k);
            t[j][lt[j]] = k;
            lt[j]++;
            f[k] = j;
        }
        while (1)
        {
            pos = 0;
            for (j = 1; j <= n; j ++)
            if (j!=r&&c[j][2] != 0)
            {
                if (pos == 0 || c[pos][1] * c[j][2] < c[pos][2]*c[j][1]){pos 
= l = j;}
            }
            if (pos == 0) break;
            
            c[f[l]][0] += c[f[l]][2] * c[l][1]+c[l][0]; 
            c[f[l]][1] += c[l][1];
            c[f[l]][2] += c[l][2];
            
            c[l][0] = c[l][1] = c[l][2] = 0;
        }
        printf("%d\n",c[r][0]);
    }
}