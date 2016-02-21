#include <iostream>
#include <cstring>
using namespace std;

class Solution {
public:
    bool isMatch(string s, string p) {
        int slen = s.length();
        int plen = p.length();
        bool mark[slen + 1][ plen + 1];
        memset(mark, 0, sizeof(mark));
        mark[0][0] = 1;
        cout << mark[0][0] << " ";
        for (int i = 1; i < plen; i++) {
            if (p[i] == '*')
                mark[0][i+1] = mark[0][i - 1];
            cout << mark[0][i] << " ";
        }

        cout << mark[0][plen] << endl<< endl;
        
        for (int i = 1; i <= slen; i++) {
            for (int j = 1; j <= plen; j++) {
                if (p[j - 1] == '.' || p[j - 1] == s[i - 1])
                    mark[i][j] = mark[i - 1][j - 1];
                else if (j > 1 && p[j - 1] == '*')
                    mark[i][j] = mark[i][j - 2] || (mark[i - 1][j] && (p[j - 2] == '.' || p[j - 2] == s[i - 1]));
            }
        }
        for (int i = 0; i < slen+1; i++) {
            for (int j = 0; j < plen+1; j++) {
                cout << mark[i][j] << " ";
            }
            cout << endl;
        }
        return mark[slen][plen];
    }
};

int main() {
    Solution sol;
    cout << sol.isMatch("aaa", "ab*ac*a") << endl << endl;
    cout << sol.isMatch("aaa", "aab*a") << endl;
    return 0;
}