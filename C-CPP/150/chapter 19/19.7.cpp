#include <iostream>
using namespace std;

bool g_Invalid = false;

int GetMaxSum(int a[], int n){
    if(a == NULL || n <= 0){
        g_Invalid = true;
        return 0;
    }
    g_Invalid = false;

    int max_sum = 1<<31;
    int cur_sum = 0;
    for(int i = 0; i < n; i++){
        if(cur_sum<=0)
            cur_sum = a[i];
        else
            cur_sum += a[i];

        if(cur_sum > max_sum)
            max_sum = cur_sum;
    }
    return max_sum;
}

int main(){
    int a[] = {2, -8, 3, -2, 4, -10};
    int max_sum = GetMaxSum(a, 6);
    if(g_Invalid)
        cout<< "Invalid Input!"<<endl;
    else
        cout<<max_sum<<endl;

    cout <<(int)(1<<31)<<endl;
    cout <<(int)(1<<1)<<endl;
    cout <<(int)(1<<2)<<endl;
    cout <<(int)(1<<3)<<endl;
    cout <<(int)(1<<4)<<endl;
    cout <<(int)(1<<10)<<endl;
    cout <<(int)(1<<20)<<endl;
    cout <<(int)(1<<30)<<endl;
    //cout <<(int)(1<<4)<<endl;
    return 0;
}
