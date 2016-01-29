class Solution {


public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
        
        if (nums.size() < 2 || k == 0 || t < 0) return false; // do not forget t < 1
        
        // method 1: use multiset
        /*int start = 0;
        multiset<long> windows;  // ordered set allow multiple instances
        for (int i = 0; i < nums.size(); i++) {
            if (i - start > k ) {
                windows.erase(windows.find(nums[start++]));
            }
            auto it = windows.lower_bound((long)nums[i] - (long)t);
            if (it != windows.end() && *it <= (long)nums[i] + (long)t) {
                return true;
            } 
            windows.insert(nums[i]);
        }
        return false;
        */
        
        // method 2: bucket sort
        
        map<long, long> bucketmap;
        for (int i = 0; i < nums.size(); i++) {
            long bucket = ((long)nums[i] - INT_MIN) / ((long)t + 1);
            if (bucketmap.find(bucket) != bucketmap.end() || 
               (bucketmap.find(bucket - 1) != bucketmap.end()  && nums[i] - bucketmap[bucket - 1] <= t) ||
               (bucketmap.find(bucket + 1) != bucketmap.end()  && bucketmap[bucket + 1] - nums[i] <= t))
               return true;
            
            if (bucketmap.size() >= k) {
                bucketmap.erase(((long)nums[i-k] - INT_MIN) / ((long)t+1));
            }
            bucketmap[bucket] = (long)nums[i];
        }
        return false;
    }
};