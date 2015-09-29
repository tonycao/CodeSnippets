class Solution {
public:
    int sqrt(int x) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        long long high = x;
        long long low = 0;
        if(x<=0) return 0;
        if(x==1) return 1;
        while(high-low > 1){
            long long mid = low + (high - low)/2;
            if (mid*mid <= x)
            {
                low = mid;
            }else high = mid;
        }
        return low;
    }
};

//algorithm 2
class Solution {
public:
    int sqrt(int x) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (x==0) {return 0;}
        if (x==1) {return 1;}

        double x0 = 1;
        double x1;
        while (true){
            x1 = (x0+ x/x0)/2;
            if (abs(x1-x0)<1){return x1;}
            x0=x1;
        }

    }
};

//1. 二分
//2. 牛顿法
