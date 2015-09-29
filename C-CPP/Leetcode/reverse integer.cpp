class Solution {
public:
    int reverse(int x) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        bool isNeg = ( x<0 )? true : false;
        x = abs(x);
        int rev = 0, digit = 0;
        while(x != 0){
            digit = x%10;
            rev = rev*10 + digit;

            x /= 10;
        }


        if (isNeg) rev *= -1;
        return rev;
    }
};
