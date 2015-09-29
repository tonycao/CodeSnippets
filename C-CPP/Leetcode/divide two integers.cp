#include <iostream>
using namespace std;

class Solution {
public:
    int divide(int dividend, int divisor) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        long long a = abs((long long)dividend);
        long long b = abs((long long)divisor);

        long long ret = 0;
        while(a >= b){
            long long c = b;
            for (int i = 0; a>=c; ++i, c<<=1){
                cout<<c<<endl;
                a -= c;
                ret += 1<<i;
            }
        }

        return ((dividend^divisor) >> 31) ? (-ret) : ret;
    }
};

int main(){
    Solution sl;
    sl.divide(1453, 24);
    return 0;
}
