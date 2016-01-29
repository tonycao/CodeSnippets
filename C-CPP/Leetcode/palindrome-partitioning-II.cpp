class Solution {
public:
    int minCut(string s) {
        //DP: Time ~ O(N^2) 
        int n = s.length();
        vector<int> f(n + 1); // minmum cut between [i, n - 1]
        vector<vector<bool> > p(n, vector<bool>(n, false));
        
        // worst case: cutting by each char
        for (int i = 0; i <= n; i++) {
            f[i] = n - 1 - i;
        }
        
        for (int i = n - 1; i >= 0; i--) {
            for (int j = i; j < n; j++) {
                if (s[i] == s[j] && (j - i < 2 || p[i + 1][j - 1])) {
                    p[i][j] = true;
                    f[i] = min(f[i], f[j + 1] + 1);
                }
            }
        }
        return f[0];
    }
};