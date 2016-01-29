class Solution {
public:
    int addDigits(int num) {
        //https://leetcode.com/discuss/52122/accepted-time-space-line-solution-with-detail-explanations
        return (num - 1) % 9 + 1;
    }
};