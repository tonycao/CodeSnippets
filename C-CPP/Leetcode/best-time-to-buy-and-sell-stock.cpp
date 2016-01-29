class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int profit = 0;
        if (prices.size() < 2) return profit;
        int minval = prices[0];
        for (int i = 1; i < prices.size(); i++) {
            minval = min(minval, prices[i]);
            profit = max(profit, prices[i] - minval);
        }
        return profit;
    }
};