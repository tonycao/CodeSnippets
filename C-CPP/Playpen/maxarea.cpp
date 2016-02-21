#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int maximalSquare(vector<vector<char> >& matrix) {
        int m = matrix.size();
        if (m == 0) return 0;
        int n = matrix[0].size();
        if (n == 0) return 0;
        
        int maxA = 0;
        vector<vector<int> > area(m, vector<int>(n, 0));
        for (int i = 0; i < m; i++) {
            area[i][0] = matrix[i][0] == '1';
            maxA = max(maxA, area[i][0]);
            cout << area[i][0] << endl;
            for (int j = 1; j < n; j++) {
                if (i == 0) {
                    area[i][j] = matrix[i][j] == '1' ? 1 : 0;
                } else {
                    area[i][j] = matrix[i][j] == '1' ? min(area[i - 1][j], min(area[i - 1][j - 1], area[i][j - 1]))+1 : 0;
                }
                maxA = max(maxA, area[i][j]);
                cout << maxA << endl;
            }
        }
        
        return maxA*maxA;
    }
};

int main() {
    Solution sol;
    vector<vector<char> > matrix(1, vector<char>(1, '1'));
    cout << matrix.size() << endl;
    //cout << matrix[0].size() << endl;
    cout << sol.maximalSquare(matrix) << endl;
    return 0;
}