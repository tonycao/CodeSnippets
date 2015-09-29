/*You are given two sorted arrays, A and B, and A has a large enough buffer at 
the end to hold B. Write a method to merge B into A in sorted order.
*/

#include <iostream>
using namespace std;

void swap(int &a, int &b){
    a = a^b;
    b = a^b;
    a = a^b;
}
void merge(int a[], int begin, int mid , int end){
    for(int i=begin; i<=mid; ++i){
        if(a[i]>a[mid+1]){
            swap(a[i], a[mid+1]);
            for(int j=mid+1; j<end; ++j){
                if(a[j]<=a[j+1]) break;
                swap(a[j], a[j+1]);
            }
        }
    }
}

void merge1(int a[], int b[], int n, int m){
    int k = n + m - 1;
    int i = n - 1, j = m - 1;
    while(i>=0 && j>=0){
        if(a[i] > b[j]) a[k--] = a[i--];
        else a[k--] = b[j--];
    }
    while(j>=0) a[k--] = b[j--];
}
int main(){
    int a[10] = {
        8, 9, 11, 15, 17
    };
    int b[5] = {
        1, 2, 3, 4, 5
    };
    merge1(a, b, 5, 5);
    for(int i=0; i<10; ++i)
        cout<<a[i]<<" ";
    return 0;
}