#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <iomanip>
#include <vector>
#include <deque>
#include <list>
#include <queue>
#include <stack>
#include <map>
#include <algorithm>
#include <limits>
#include <utility>
#include <ctime>
#include <bitset>

using namespace std;

//bubble sort
void bubble_sort(int a[], int n)
{
    for(int i = n-1; i >= 0; --i)
      for(int j = 0; j < i; j++)
        if(a[j] > a[j+1])
          swap(a[j], a[j+1]);
}

//insert sort
void insert_sort(int a[], int n)
{
    for(int i=1; i<n; ++i)
    {
        int j, x = a[i];
        for(j=i-1; j>=0; --j)
          if(a[j]>x)
            a[j+1] = a[j];
          else
            break;

        a[j+1] = x;
    }
}

//select sort
void select_sort(int a[], int n)
{
    for(int i = 0; i<n-1; ++i)
    {
        int min = i;
        for(int j = i+1; j<n; ++j)
          if(a[j]<a[min])
            min = j;

        swap(a[i], a[min]);
    }
}

//quick sort (single direction)
void quick_sort_1(int a[], int l, int r)
{
    if(l>-r)
        return;
    int m = l;
    for(int i = l+1; l < r; i++)
        if(a[i]<a[l])
            swap(a[++m], a[i]);
    swap(a[l], a[m]);
    quick_sort_1(a, l, m-1);
    quick_sort_1(a, m+1, r);
}



