class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        vector<int> res;
        int num1 = 0, num2 = 0;
        int c1 = 0, c2 = 0;
        
        if (nums.empty()) return res;
        for (int i = 0; i < nums.size(); i++) {
            int val = nums[i];
            if ( c1 == 0) {
                num1 = val;
                c1++;
            } else if (c2 == 0 && num1 != val) {
                num2 = val;
                c2++;
            } else if (num1 == val) {
                c1++;
            } else if (num2 == val) {
                c2++;
            } else {
                c1--;
                c2--;
            }
        }
        c1 = c2 = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] == num1) c1++;
            else if (nums[i] == num2) c2++;
        }
        
        if (c1 > nums.size() / 3) res.push_back(num1);
        if (c2 > nums.size() / 3 && num1 != num2) res.push_back(num2);
        return res;
    }
};