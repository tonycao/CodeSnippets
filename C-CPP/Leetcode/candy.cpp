class Solution {
public:
    int candy(vector<int>& ratings) {
        //Greedy Algorithm: Time ~ O(3N), Space ~ O(N)
        const int n = ratings.size();
        vector<int> candy(n, 1);
        
        // method 1
        // scan from start from left and right respectively
        for (int i = 1; i < n; i++) {
            if (ratings[i] > ratings[i - 1])  // ascending
                candy[i] = candy[i - 1] + 1;
        }
        
        for (int i = n - 2; i >= 0; i--) {
            if (ratings[i] > ratings[i + 1] && candy[i] <= candy[i + 1])  // descending
                candy[i] = candy[i + 1] + 1;
        }
        
        
        // return with initial n candy
        return accumulate(&candy[0], &candy[0] + n, 0);
    }
};