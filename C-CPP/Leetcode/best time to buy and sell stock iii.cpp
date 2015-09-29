class Solution {
public:
    int maxProfit(vector<int> &prices) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        int mprof = 0;
        if (prices.size() > 1){
            int maxprof = 0;
            vector<int> mp;
            mp.push_back(0);
            int st = *prices.begin();
            for(int i = 1; i<=prices.size(); i++){
                if(mprof < prices[i]-st) mprof = prices[i] - st;
                if(prices[i] < st) st = prices[i];
                mp.push_back(mprof);
            }
            mprof = 0;
            int ed = *(prices.end()-1);
            for(int i = prices.size()-2; i>= 0; i--){
                if(mprof < ed-prices[i] + mp[i]) mprof = ed - prices[i] + mp[i];
                if(prices[i] > ed) ed = prices[i];
            }
        }
        return mprof;
    }
};
