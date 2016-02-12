#include <iostream>

using namespace std;

void BubbleSort(int a[],int n)
{
    int i,j;
    int temp;
    for(i = 0; i < n-1; i++)
        for(j = 0; j < n-i-1; j++)
            if(a[j] > a[j+1])
            {
                temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
            }
}

int main(){
    int a[] = {4, 3 ,6, 19, 6, 22};
    int n = 6;
    BubbleSort(a, n);
    for(int i = 0; i<n; i++){
        cout<<a[i]<<endl;
    }
    return 0;
}
