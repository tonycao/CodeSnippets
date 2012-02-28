#include <iostream>

using namespace std;
const int Max_size = 10000;
int father[Max_size], rank[Max_size];

//initialize UnionFindSet
void initialize(int n)
{
    int i;
    for(i = 0; i < n; i++)
    {
        father[i] = i;
        rank[i] = 1;
    }
    return ;
}

int Find(int x)
{
    if(father[x] != x)
    {
        father[x] = Find(father[x]);
    }
    return father[x];
}

//non-recursive Find
/*
   int Find(int x)
   {
   while(father[x] != x)
   {
   x = father[x];
   }
   return x;
   }
 * */

void Union(int a, int b)
{
    int fa = Find(a);
    int fb = Find(b);
    if(fa == fb)
    {
        return ;
    }
    if(rank[fa] <= rank[fb])
    {
        father[fa] = fb;
        rank[fb] += rank[fa];
    }
    else
    {
        father[fb] = fa;
        rank[fa] += rank[fb]; 
    }

}

int main()
{
    int n, m;
    while(scanf("%d %d", &n, &m) !=EOF && n!= 0)
    {
        initialize(n);
        for (int i = 0; i< m; i++)
        {
            int count, a, b;
            scanf("%d %d", &count, &a);
            for(int j = 1; j < count; j++)
            {
                scanf("%d", &b);
                Union(a,b);
            }
        }
        printf("%d\n", rank[Find(0)] );
    }
    return 0;
}
