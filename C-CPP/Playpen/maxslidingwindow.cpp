#include <iostream>
#include <vector>
#include <utility>
#include <queue>

using namespace std;

class Solution {
public:
    /**
     * @param nums: A list of integers.
     * @return: The maximum number inside the window at each moving.
     */
    vector<int> maxSlidingWindow(vector<int> &nums, int k) {
        // write your code here
        vector<int> res(nums.size() - k + 1);
        priority_queue<pair<int,int> > pq;
        for (int i = 0; i < k; i++) {
            pq.push(make_pair(nums[i], i));
        }
        
        for (int i = k; i < nums.size(); i++) {
            pair<int, int> p = pq.top();
            res[i-k] = p.first;
            while(p.second <= i - k) {
                pq.pop();
                p = pq.top();
            }
            pq.push(make_pair(nums[i], i));
        }
        res[nums.size() - k] = pq.top().first;
        return res;
    }
};

int main() {
    Solution sol;
    vector<int> nums = {1, 3, 7, 7, 2};
    //nums.push_back(2);
    int k = 3;
    vector<int> res = sol.maxSlidingWindow(nums,k);
    for (int i = 0; i < res.size(); i++) {
        cout << res[i] << endl;
    }
    return 0;
}