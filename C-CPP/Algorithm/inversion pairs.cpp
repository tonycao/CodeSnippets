#include <iostream>
using namespace std;

/* 归并求逆序对数, arr 存储最终有序结果
 * 在函数外申请一个临时数组作为参数传入
 * 避免递归不断创建临时数组的开销
 */

 int Merge(int * arr, int beg, int mid, int end , int * tmp_arr){
    memcpy(tmp_arr+beg, arr+beg, sizeof(int)*(end-beg+1));
    int i = beg;
    int j = mid + 1;
    int k = beg;
    int inversion = 0; // merge inversion pairs
    while(i <= mid && j <= end){
        if(tmp_arr[i] <= tmp_arr[j]){
            arr[k++] = tmp_arr[i++];
        }else{
            arr[k++] = tmp_arr[j++];
            inversion += (mid - i + 1);
        }
    }
    while(i <= mid){
        arr[k++] = tmp_arr[i++];
    }
    while(j <= end){
        arr[k++] = tmp_arr[j++];
    }
    return inversion;
 }

 int MergeInversion(int *arr, int beg, int end, int *tmp_arr){
    int inversions = 0;
    if(beg < end){
        int mid = (beg + end) >> 1;
        inversions += MergeInversion(arr, beg, mid, tmp_arr);
        inversions += MergeInversion(arr, mid+1, end, tmp_arr);
        inversions += Merge(arr, beg, mid, end, tmp_arr);
    }
    return inversions;
 }

 // test
 int testPoints[10] = {
    1, 4, 2, 9, 48,
    15, 13, 44, 6, 90
 };

 int main(){
    int arrcopy[10];
    memcpy(arrcopy, testPoints, sizeof(testPoints));

    printf("the num of inversions is: %d\n",
        MergeInversion(testPoints, 0, 9, arrcopy));
    return 0;
 }
