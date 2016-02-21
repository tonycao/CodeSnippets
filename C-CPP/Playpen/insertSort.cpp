#include <iostream>
using namespace std;

void Insertion_sort(int a[], int n) {
    int tmp;
    for (int i = 1; i < n; i++) {
        tmp = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] > tmp) {
            a[j+1] = a[j];
            j--;
        }
        a[j+1] = tmp;
    }
}

int main() {
    int a[] = { 3, 4, 6, 9, 11, 2};
    Insertion_sort(a, 6);
    for (int i = 0; i < 6; i++) {
        cout << a[i] << " ";
    }
    cout << endl;
    return 0;
}