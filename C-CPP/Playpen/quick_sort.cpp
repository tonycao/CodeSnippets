//
//  main.cpp
//  Algorithm_rehersal
//
//  Created by  on 13-12-2.
//  Copyright (c) 2013年 . All rights reserved.
//

#include <map>
#include <list>
#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <set>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

template<typename T>
struct random_pivot{
    random_pivot(){
        srand(time(NULL));
    }
    T operator()(T begin, T end) {
        return begin + (rand() % (end - begin));
    }
};

template<typename T>
T partition( T begin, T end, T pivot)
{
    swap(*pivot, *begin);
    pivot = begin;
    
    T head = begin;
    T tail = end - 1;
    while( head <= tail )
    {
        while( *tail >= *pivot && head <= tail ) tail--;
        if( *tail < *pivot && head <= tail )
        {
            swap(*pivot, *tail);
            pivot = tail;
            tail--;
        }
        
        while( *head <= *pivot && head <= tail ) head++;
        if( *head > *pivot && head <= tail )
        {
            swap(*pivot, *head);
            pivot = head;
            head++;
        }
    }
    return pivot;
}a

template<typename T, typename PF>
void __QuickSort(T begin, T end, PF pf)
{
    if( begin < end-1 )
    {
        T pivot = pf(begin, end);
        pivot = partition(begin, end, pivot);
        __QuickSort(begin, pivot, pf);
        __QuickSort(pivot+1, end, pf);
    }
}

template<typename T>
void QuickSort(T begin, T end)
{
    __QuickSort(begin, end, random_pivot<T>());
}


int main(int argc, const char * argv[])
{

    //  Test case for Quick Sort algorithm.
    
    vector<string> v(10);
    v[0]="Paris";
	v[1]="London";
	v[2]="Stockholm";
	v[3]="Berlin";
	v[4]="Oslo";
	v[5]="Rome";
	v[6]="Madrid";
	v[7]="Tallinn";
	v[8]="Amsterdam";
	v[9]="Dublin";
    
    vector<int> u = {3, 8, 10, 6, 7, 4, 2, 1, 9, 13, 11, 18, 23, 19, 12, 5, 14};
    
    cout << "u before qsort: " << endl;
    for( auto each: u)
    {
        cout << each << " ";
    }
    cout << endl;
    
    QuickSort(u.begin(), u.end());
    
    cout << "u after qsort: " << endl;
    for( auto each: u)
    {
        cout << each << " ";
    }
    cout << endl;
    
    return 0;
}

