class Solution {
public:
    int largestRectangleArea(vector<int>& height) {
        // use 
        // Stack: Time ~ O(N), Space ~ O(1) 
        stack<int> stk;
        height.push_back(0); // to enforce to compute the last result
        int res = 0;
        int i = 0;
        while (i < height.size()) {
            if (stk.empty() || height[stk.top()] < height[i]) {
                stk.push(i++);
            } else {
                int tmp = stk.top();
                stk.pop();
                res = max(res, height[tmp] * (stk.empty() ? i : i - stk.top() - 1));
            }
        }
        return res;
    }
};