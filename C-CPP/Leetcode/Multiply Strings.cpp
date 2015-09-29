class Solution {
public:
    string multiply(string num1, string num2) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        int l1 = num1.size();
        int l2 = num2.size();
        vector<int> num(l1+l2, 0);

        for(int i = 0; i < l1; ++i){
            int n1 = num1[l1-1-i] - '0';
            int carry = 0;
            for (int j = 0; j < l2; ++j)
            {
                int n2 = num2[l2-1-j] - '0';
                carry = n1*n2 + carry + num[i+j];
                num[i+j] = carry%10;
                carry /= 10;
            }
            num[i+l2] = carry;
        }

        int i = l1+l2-1;
        while(i > 0 && num[i] == 0) --i;
        string result = "";
        while(i>=0) result += char(num[i--] + '0');

        return result;
    }
};
