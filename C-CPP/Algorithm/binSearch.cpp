#include <iostream>

using namespace std;

// iterative
int binSearch(int array[], int n, int v){
    int left = 0, right = n-1;
    while(left <= right){
        int mid = left + (right-left)/2;
        if(array[mid] > v){
            right = mid - 1;
        }else if(array[mid] < v){
            left = mid + 1;
        }else{
            return mid;
        }
    }
    return -1;
}

// recursive
int binSearch2(int array[], int low, int high, int v){
    int mid = low + (high - low)/2;
    //
    if(low < high){ // pay attention here
        if(array[mid] > v){
            return binSearch2(array, low, mid, v);
        }else if(array[mid] < v){
            return binSearch2(array, mid+1, high, v);
        }else{
            return mid;
        }
    }else if(low == high){    //deferred termination: return the first index of the target value
        if(array[mid] == v){
            return mid;
        }else{
            return -1;
        }
    }else{
        return -1;
    }
}

int main(){
    int array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 12, 19, 21};
    int m = binSearch(array, sizeof(array)/sizeof(array[0]), 19);
    int n = binSearch2(array, 0, sizeof(array)/sizeof(array[0])-1, 19);
    cout<< "m = " << m <<endl;
    cout<< "n = " << n <<endl;

    return 0;
}
