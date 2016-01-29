class Solution {
public:
    int maxProfit(vector<int>& prices) {
        //1-d DP, Time ~ O(3N)
        if (prices.size() < 2) return 0;
        
        int n = prices.size();
        
        vector<int> lprofit(n, 0);
        vector<int> rprofit(n, 0);
        
        for (int i = 1, minprice = prices[0]; i < n; i++) {
            minprice = min(minprice, prices[i]);
            lprofit[i] = max(lprofit[i - 1], prices[i] - minprice);
        }
        
        for (int i = n - 2, maxprice = prices[n - 1]; i>=0; i--) {
            maxprice = max(prices[i], maxprice);
            rprofit[i] = max(rprofit[i + 1], maxprice - prices[i]);
        }
        
        int res = 0;
        for (int i = 0; i < n; i++) {
            res = max(res, lprofit[i] + rprofit[i]);
        }
        return res;
    }
};