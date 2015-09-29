class Solution {
public:
    int maxProfit(vector<int> &prices) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        int res = 0;
        if(prices.size() < 2) return res;
        for(int i = 1; i < prices.size(); i++){
            if(prices[i] > prices[i-1]){
                res += prices[i] - prices[i-1];
            }
        }
        return res;
    }
};
