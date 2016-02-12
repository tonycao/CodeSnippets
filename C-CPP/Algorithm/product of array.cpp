#include <iostream>
#include <vector>
using namespace std;

vector<int> product(vector<int> A){
    int s1 = 1, s2 =1;
    vector<int> B(A.size(), 1);
    int n = A.size();
    //int i = 0;
    for (int i = 0; i < n; i++){
        B[i] *= s1;
        s1 *= A[i];
    }

    for (int i = n-1; i >=0; i--){
        B[i] *= s2;
        s2 *= A[i];
    }
    return B;
}
//wrong
vector<int> product2(vector<int> A){
    int s1 = 1, s2 =1;
    //vector<int> B(A.size(), 1);
    int n = A.size();
    //int i = 0;
    for (int i = 0; i < n; i++){
        A[i] *= s1;
        A[n-1-i] *= s2;

        s1 *= A[i];
        s2 *= A[n-1-i];
    }
    return A;
}

int main(){

    int tmp[]={3, 4, 5, 6, 7,8,9};
    vector<int> A(tmp, tmp+7);
    vector<int> B;
    B = product(A);
    for(int i = 0; i < A.size(); i++){
        cout<< B[i]<<" ";
    }
    cout<<endl;
    return 0;
}
