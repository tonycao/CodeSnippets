class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        /*set<int> dup;
        if (nums.size() <= 1) return false;
        for (int i = 0; i < nums.size(); i++){
            if (dup.find(nums[i]) != dup.end()) return true;
            else dup.insert(nums[i]);
        }
        return false;*/
        int size = nums.size();
        sort(nums.begin(), nums.end());
        //nums.erase(unique(nums.begin(), nums.end()), nums.end());
        //return size != nums.size();
        for (int i = 1; i < size; i++) {
            if (nums[i] == nums[i - 1]) return true;
        }
        return false;
    }
};