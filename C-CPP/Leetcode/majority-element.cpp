class Solution {
public:
    int majorityElement(vector<int> &num) {
        if (num.size() == 0) return -1;
        int prev = num[0], count = 0;
        for (int i = 1; i < num.size(); i++) {
            if (prev == num[i]) {
                count++;
            } else {
                if (count > 0) count--;
                else prev = num[i];
            }
        }
        return prev;
    }
};
