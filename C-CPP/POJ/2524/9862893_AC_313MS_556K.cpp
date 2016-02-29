#include <iostream>

using namespace std;
const int Max_size = 50001;
int father[Max_size], rank[Max_size];
int maxNum;

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
        maxNum--;
    }
    else
    {
        father[fb] = fa;
        rank[fa] += rank[fb]; 
        maxNum--;
    }

}

int main()
{
    int Case = 1;
    int n, m;
    while(scanf("%d %d", &n, &m) !=EOF && n!= 0)
    {
        maxNum = n;
        initialize(n);
        int a, b;

        for (int i = 0; i< m; i++)
        {
            scanf("%d %d", &a, &b);
            Union(a,b);

        }
        printf("Case %d: %d\n", Case++, maxNum );
    }
    return 0;
}