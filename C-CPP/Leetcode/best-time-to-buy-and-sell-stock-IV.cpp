class Solution {
public:
    int maxProfit(int k, vector<int> &prices) {
        // method 1:
        //https://leetcode.com/discuss/26745/c-solution-with-o-n-klgn-time-using-max-heap-and-stack
        /*
        int n = prices.size();
        int ret = 0, v, p = 0;
        stack<pair<int, int>> vp_pairs;
        priority_queue<int> profits;
        
        
        while(p < n) {
            for (v = p; v < n - 1 && prices[v] >= prices[v+1]; v++) ;
            for (p = v + 1; p < n && prices[p] >= prices[p-1]; p++) ;
            
            while(!vp_pairs.empty() && prices[v] < prices[vp_pairs.top().first]) {
                profits.push(prices[vp_pairs.top().second-1] - prices[vp_pairs.top().first]);
                vp_pairs.pop();
            }
            
            while(!vp_pairs.empty() && prices[p-1] >= prices[vp_pairs.top().second - 1]) {
                profits.push(prices[vp_pairs.top().second - 1] - prices[v]);
                v = vp_pairs.top().first;
                vp_pairs.pop();
            }
            vp_pairs.push(pair<int, int>(v, p) );
        }
        while(!vp_pairs.empty()) {
            profits.push(prices[vp_pairs.top().second - 1] - prices[vp_pairs.top().first]);
            vp_pairs.pop();
        }
        
        for (int i = 0; i < k && !profits.empty(); i++) {
            ret += profits.top();
            profits.pop();
        }
        return ret;
        */
        
        // method 2: 2d dp, time~O(N^2)
        if (prices.size() <= 1 || k <= 0) return 0;
        int len = prices.size();
        
        // if k >= n/2 equal to as many transactions as you want
        
        if (k >= len / 2) {
            int profit = 0;
            for (int i = 1; i < len; i++) {
                int diff = prices[i] - prices[i - 1];
                if (diff > 0) profit += diff;
            }
            return profit;
        }
        
        // at most k transactions
        // d(i, j) = max{d(i, j - 1), max_{1<=l<=j} {d(i - 1, l - 1) - p[l] (buy) + p[j] (sell)}}
        /*
        tmpMax means the maximum profit of just doing at most i-1 transactions, 
        using at most first j-1 prices, and buying the stock at price[j] - this is used for the next loop.
        */
        
        /*vector<vector<int>> f(k + 1, vector<int>(len, 0));
        for (int i = 1; i <= k; i++) {
            int tmpmax = -prices[0];
            for (int j = 1; j < len; j++) {
                tmpmax = max(tmpmax, f[i-1][j - 1] - prices[j]);  // buy at j
                f[i][j] = max(f[i][j - 1], prices[j] + tmpmax); // profit = prices[j] + tmpmax
            }
        }
        return f[k][len - 1];
        */
        
        // method 3: more intuitive dp
        
        // balance - the balance with at most j transactions with item 0 to i
        // profit - the profit with at most j transactions with item 0 to i
        vector<int> balance(k + 1, INT_MIN), profit(k + 1, 0);
    
        for(int i = 0; i < len; ++i) {
            for(int j = 1; j <= k; ++j) {
                balance[j] = max(profit[j - 1] - prices[i], balance[j]); // whether to buy at prices[i]
                profit[j] = max(balance[j] + prices[i], profit[j]); // whether to sell at prices[i]
            }
        }
    
        return profit[k];
    }
};