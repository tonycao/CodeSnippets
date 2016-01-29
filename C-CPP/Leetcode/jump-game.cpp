class Solution {
public:
    bool canJump(vector<int>& nums) {
        //Greedy algorithm: Time ~ O(N), Space ~ O(1)
        //if (nums.size() <= 1) return true;
        int n = nums.size();
        int reach = 0;
        for (int i = 0; i <= reach && reach < n; i++) {
            reach = max(reach, i + nums[i]);
        }
        return reach >= n - 1;
    }
};