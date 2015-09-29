class Solution {
public:
    string addBinary(string a, string b) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        int la = a.size();
        int lb = b.size();
        string sum = la > lb ? a:b;
        int carry = 0;
        for (int i = 0; i < sum.size(); ++i)
        {
            char ca = i<la?a[la-i-1]:'0';
            char cb = i<lb?b[lb-i-1]:'0';
            int bit = ca -'0' + cb - '0' + carry;
            carry = bit/2;
            sum[sum.size()-i-1]=bit%2+'0';
        }
        if (carry) sum = '1'+sum;
        return sum;
    }
};
