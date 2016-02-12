#include <iostream>

using namespace std;

void inplaceSort(int A[], int B[], int n){
    if (n==0) return;
    for(int i = 0; i < n; i++){
        int tmpA = A[B[i]];
        A[B[i]] = A[i];
        A[i] = tmpA;
        int tmpB = B[B[i]];
        B[B[i]] = B[i];
        B[i] = tmpB;
    }
}

int main(){
    int sz = 6;
    int A[] = {2, 4, 7, 1, 9, 8};
    int B[] = {5, 4, 3, 2, 1, 0};
    inplaceSort(A, B, sz);
    for(int i = 0; i<sz; i++){
        cout<<A[i]<<" ";
    }
    cout<<endl;
    return 0;
}
