#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<string> restoreIpAddresses(string s) {
        vector<string> result;
        string ip;
        dfs(s, 0, 0, ip, result);
        return result;
    }
    
    void dfs(string s, int start, int step, string ip, vector<string> &result) {
        cout << s << " " << start << " " << step << " "<< ip << endl;
        if (start == s.length() && step == 4) {
            
            ip.resize(ip.size() - 1);
            result.push_back(ip);
            cout << s << " " << start << " " << step << " "<< ip << endl;
            return;
        }
        
        if (s.size() - start > (4 - step) * 3) return; // prune tree
        if (s.size() - start < (4 - step)) return;
        
        int num = 0;
        for (int i = start; i < start + 3; i++) {
            num = num * 10 + (s[i] - '0');
            //cout << num << endl;
            if (num <= 255) {
                ip += s[i];
                dfs(s, i + 1, step + 1, ip + '.', result);
            }
            if (num == 0) break;
        }
    }
};

int main() {
    Solution sol;
    string s("0000");
    vector<string> str = sol.restoreIpAddresses(s);
    for (int i = 0; i < str.size(); i++) 
        cout << str[i] << " ";
    cout<< endl;
    return 0;
}