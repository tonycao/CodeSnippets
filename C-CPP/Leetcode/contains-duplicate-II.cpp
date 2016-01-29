class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        unordered_map<int, int> hmap;
        for (int i = 0; i < nums.size(); i++) {
            auto iter = hmap.find(nums[i]);
            if(iter != hmap.end() && i - iter->second <= k ) {
                return true;
            }
            hmap[nums[i]] = i;
        }
        return false;
    }
};