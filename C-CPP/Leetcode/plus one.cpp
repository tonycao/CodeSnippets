class Solution {
public:
    vector<int> plusOne(vector<int> &digits) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        int carry = 1;
        for(int i = digits.size()-1; i >=0; i--){
            int sum = digits[i] + carry;
            digits[i] = sum%10;
            carry = sum/10;
        }
        if(carry){
            digits.insert(digits.begin(),1);
        }
        return digits;
    }
};
