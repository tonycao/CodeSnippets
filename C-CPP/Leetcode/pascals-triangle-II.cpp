class Solution {
public:
    vector<int> getRow(int rowIndex) {
        //Time ~ O(k), Space ~ O(k)
        vector<int> res;
        for (int i = 0; i <= rowIndex; i++) {
            for (int j = i-1; j >= 0 ; j--) { // rolling array, from back to front to avoid rewrite the values
                res[j] = res[j] + res[j-1];
            }
            res.push_back(1);
        }
        return res;
    }
};