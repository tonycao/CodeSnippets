#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        vector<int> pathsum(triangle.size(), 0);
        for (int i = 0; i < triangle.size(); i++) {
            for (int j = i; j >= 0; j--) {
                if (j == 0) pathsum[j] = pathsum[j] + triangle[i][j];
                else if (j == i) pathsum[j] = pathsum[j - 1] + triangle[i][j];
                else pathsum[j] = min(pathsum[j], pathsum[j - 1]) + triangle[i][j];
            }
        }
        
        int minsum = INT_MAX; 
        for (int i = 0; i < triangle.size(); i++) {
            if (minsum > pathsum[i]) minsum = pathsum[i];
        }
        return minsum;
    }
};

int main() {
    vector<vector<int>> tri = {{-10}};
    Solution sol;
    cout << sol.minimumTotal(tri) << endl;
}