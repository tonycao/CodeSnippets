#include <cstdio>
#include <stack>

using namespace std;

typedef __int64 i64;

int n;
int h[100100];
int index[100100];
int width[100100];

int main()
{
    int i, j;
    while(scanf("%d", &n) && n)
    {
        for(i = 1; i <= n; i++)
            scanf("%d", h + i);
        h[0] = h[n + 1] = 0;
        i64 ret = 0;
        for(i = j = 1; i <= n + 1; i++)
        {
            int cur = h[i];
            while(h[j - 1] > cur)
            {
                i64 area = (i64)(i - index[j - 1] + width[j - 1] - 1) * h[j - 1];
                if(area > ret)
                    ret = area;
                --j;
            }
            if(cur >= h[j - 1])
            {
                h[j] = cur;
                width[j] = i - index[j - 1];
                index[j++] = i;
            }
        }
        printf("%I64d\n", ret);
    }

    return 0;
}