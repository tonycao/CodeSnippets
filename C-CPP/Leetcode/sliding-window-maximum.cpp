class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        //http://articles.leetcode.com/2011/01/sliding-window-maximum.html
        // deque: Time~O(n)
        vector<int> res;
        if (k == 0) return res;
        
        /*
        deque<int> Q;
        
        for (int i = 0; i < nums.size(); i++) {
            
            while(!Q.empty() && nums[i] >= nums[Q.back()])
                Q.pop_back();
            while(!Q.empty() && Q.front() <= i - k) 
                Q.pop_front();
            Q.push_back(i);
            if (i >= k - 1) res.push_back(nums[Q.front()]);
        }
        //res.push_back(nums[Q.front()]);
        return res;
        */
        
        /*
        // multi-set: Time~O(nlogk)
        multiset<int> w;
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            if (i >= k) w.erase(w.find(nums[i-k]));
            w.insert(nums[i]);
            if (i >= k - 1) res.push_back(*w.rbegin()); // return max val from multiset
        }
        return res;
        */
        
        // priority-queue: Time~O(nlogn)
        priority_queue<pair<int, int>> w;
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            while(!w.empty() && w.top().second <= i - k) w.pop();
            w.push(make_pair(nums[i], i));
            if (i >= k - 1) res.push_back(w.top().first);
        }
        return res;
    }
};