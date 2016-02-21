#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int> > combinationSum3(int k, int n) {
        vector<vector<int> > res;
        vector<int> tmpsum;
        dfs(res, tmpsum, 1, k, n);
        return res;
    }
    
    void dfs(vector<vector<int> > &res, vector<int> &tmpsum, int cur, int k, int sum) {
        if (sum < 0) return;
        else {
            if (tmpsum.size() == k) {

                if (sum == 0) {
                    for (int i = 0; i < tmpsum.size(); i++) {
                        cout << tmpsum[i] << " ";
                    }
                    cout << endl;
                    res.push_back(tmpsum);
                }
                return ;
            }
            
            for (int i = cur; i <= 9; i++ ) {
                //cout << tmpsum.size() << endl;
                if (i <= sum) {
                    tmpsum.push_back(i);
                    dfs(res, tmpsum, i+1, k, sum-i);
                    tmpsum.pop_back();
                }
                else return ;
            }
        }
    }

/*vector<vector<int> > combinationSum3(int k, int n) {
    vector<vector<int> > result; vector<int> r;
    combinationSum3(result, r, 1, k, n);
    return result;
}

void combinationSum3(vector<vector<int> >& result, vector<int>& r, int level, int k, int n) {
    int sum = accumulate(r.begin(), r.end(), 0);
    if(k == r.size() && sum == n) {
        for (int i = 0; i < r.size(); i++) {
                        cout << r[i] << " ";
                    }
                    cout << endl;
        result.push_back(r);
    }
    else if(k > r.size()) {
        for(int i = level; i<= 9; i++) {
            if(sum + i > n)
                return;

            r.push_back(i);
            combinationSum3(result, r, i + 1, k, n);
            r.pop_back();
        }
    }
}*/
};

int main(){
    Solution sol;
    vector<vector<int> > res = sol.combinationSum3(2, 6);
    return 0;
}