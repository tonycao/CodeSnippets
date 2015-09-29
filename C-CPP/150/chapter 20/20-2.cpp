/*
Write a method to shuffle a deck of cards. It must be a perfect shuffle - 
	in other words, each 52! permutations of the deck has to be equally likely. 
		Assume that you are given a random number generator which is perfect.
*/

#include <iostream>
#include <cstdlib>

using namespace std;

void swap(int &a, int &b){
    int tmp = a;
    a = b;
    b = tmp;
}

void RandomShuffle(int a[], int n){
    for(int i = 0; i < n; i++){
        int j = rand()%(n-i) + i;
        swap(a[i], a[j]);
    }
}

int main(){
    srand((unsigned)time(0));
    int n = 9;
    int a[] = { 1, 2, 3, 4, 5, 6, 7, 8,9 };
    RandomShuffle(a, n);
    for(int i = 0; i<n; i++)
        cout<< a[i]<<endl;
    return 0;
}
