class Solution {
public:
    int maxProfit(vector<int> &prices) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        int sz = prices.size();
        int min = 0;
        int maxDiff = 0;
        for(int i = 0; i < sz; i++){
            if(prices[i] < prices[min]) min = i;
            int diff = prices[i] - prices[min];
            if(diff > maxDiff) maxDiff = diff;
        }
        return maxDiff;
    }
};
