#include <iostream>
#include <cmath>
using namespace std;

class Solution {
public:
    int divide(int dividend, int divisor) {
        bool sign = (dividend > 0 && divisor < 0) || (dividend < 0 && divisor > 0);
        long long a = (long long)dividend;
        a = abs(a);
        cout << a << endl;
        long long b = (long long)divisor;
        b = abs(b);
        cout << b << endl;

        long long result = 0;
        while(a >= b) {
            long long c = b;
            for (int i = 0; a >= c; i++, c<<=1) {
                a -= c;
                result += 1 << i;
            }
        }
        cout << result << endl;
        cout << sign << endl;
        if (sign) return -result;
        else return result;
    }
};

int main() {
    Solution sol;
    long long result = sol.divide(-2147483648, -1);
    cout <<  result << endl;
    return 0;
}