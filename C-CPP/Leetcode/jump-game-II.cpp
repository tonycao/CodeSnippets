class Solution {
public:
    int jump(vector<int>& nums) {
        // Greedy: Time ~ O(N), Space ~ O(1)
        int n = nums.size();
        int step = 0, prev = 0, reach = 0; // prev is the farthest index that has been reached; max is the farthest can be reached
        for (int i = 0; i < n; i++) {
            if (prev < i) { // ready to jump
                if (reach == prev) return -1; // unreachable
                prev = reach;
                step++;
            }
            reach = max(reach, i + nums[i]);
        }
        return step;
    }
};