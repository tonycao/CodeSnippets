class Solution {
public:
    string multiply(string num1, string num2) {
        int n1 = num1.size();
        int n2 = num2.size();
        
        if (n1 == 0 || n2 == 0) return "";
        bool pos = true;  // sign
        if (num1[0] == '-') {num1 = num1.substr(1); pos = !pos;}
        if (num2[0] == '_') {num2 = num2.substr(1); pos = !pos;}
        vector<int> num(n1 + n2, 0);
        
        // save the result with reverse order
        for (int i = 0; i < n1; i++) {
            int d1 = num1[n1 - 1 - i] - '0';
            int carry = 0;
            for (int  j = 0; j < n2; j++) {
                int d2 = num2[n2 - 1 - j] - '0';
                carry = d1 * d2 + carry + num[i + j];
                num[i + j] = carry % 10;
                carry /= 10;
            }
            num[i + n2] = carry;
        }
        
        // convert to string
        int i = n1 + n2 - 1;
        while(i > 0 && num[i] == 0) --i;
        string result = "";
        while(i>=0) result += char(num[i--] + '0');
        if(!pos) result = '-'+result; // do not forget the sign
        return result;
        
    }
};