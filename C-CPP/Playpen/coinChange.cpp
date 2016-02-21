#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<int> dp(amount + 1, -1);
        dp[0] = 0;
        for (auto coin : coins) {
            if (coin <= amount)
                dp[coin] = 1;
        }
        for (int i = 1; i <= amount; ++i) {
            for (auto coin : coins) {
                if (coin <= i && dp[i - coin] >= 0) {
                    dp[i] = dp[i] > 0 ? min(dp[i], dp[i - coin] + 1) : dp[i - coin] + 1;
                }
            }
        }
        return dp[amount];
    }

};

int main() {
    vector<int> coins = {399, 413, 250, 207, 139};
    int amount = 248;

    Solution sol;

    cout << sol.coinChange(coins, amount) << endl;


}