/* 
 *   Union Find Set
 *   by Tian cao
 */

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
    return 0;
}
