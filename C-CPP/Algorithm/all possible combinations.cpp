// all possible combinations

#include <iostream>

using namespace std;

void display(int *arr, int n){
    cout << "{";
    for(int i = 0; i < n; i++){
        cout << arr[i];
        if(i<n-1) cout << ",";
    }
    cout << "}" << endl;
}

void combination(int n, int i, int kk){
    static int *arr = new int [kk];

    if(n == 0){
        display(arr, i);
    }else if(n > 0){
        int k;
        for(k = 1; k <= kk; k++){
            arr[i] = k;
            combination(n-k, i+1, k);
        }
    }
}

int main(){
    int n = 8;
    combination(n, 0, n-1);
    return 0;
}
