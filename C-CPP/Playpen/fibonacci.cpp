// C++ program for printing vertical order of a given binary tree
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
using namespace std;

void multiply(int F[][2], int M[][2]) {
    int x = F[0][0] * M[0][0] + F[0][1] * M[1][0];
    int y = F[0][0] * M[0][1] + F[0][1] * M[1][1];
    int z = F[1][0] * M[0][0] + F[1][1] * M[1][0];
    int w = F[1][0] * M[0][1] + F[1][1] * M[1][1];

    F[0][0] = x;
    F[0][1] = y;
    F[1][0] = z;
    F[1][1] = w;
}

void power(int F[][2], int n) {
    if (n <= 1) return ;
    int M[2][2] = {{1, 1}, {1, 0}};

    power(F, n / 2);
    multiply(F, F);
    if (n % 2 != 0)
        multiply(F, M);
}

int fibonacci3(int n) {
    int F[2][2] = {{1, 1}, {1, 0}};
    if (n <= 1 ) return n;
    power(F, n - 1);
    return F[0][0];
}

int fibonacci2(int n) {
    if (n <= 1) return n;
    return fibonacci2(n - 1) + fibonacci2(n - 2);
}

int fibonacci(int n, vector<int> &fib) {
    if (n <= 1) return n;
    fib[0] = 0;
    fib[1] = 1;
    for (int i = 2; i <= n; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }
    return fib[n];
}

// Driver program to test above functions
int main()
{
    int n = 11;
    vector<int> fib(n);
    cout << fibonacci(n, fib) << endl;
    cout << fibonacci2(n) << endl;
    cout << fibonacci3(n) << endl;
    return 0;
}
