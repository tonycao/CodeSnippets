#include <iostream>
#include <vector>

using namespace std;


class Solution {
public:
    bool isAdditiveNumber(string num) {
        int n = num.length();
        for (int i = 1; i < (n + 1) / 2; ++i) {
            for (int j = i + 1; j < n; ++j) {
                string s1 = num.substr(0, i);
                string s2 = num.substr(i, j - i);
                long long d1 = stoll(s1), d2 = stoll(s2);
                if ((s1.size() > 1 && s1[0] == '0') || (s2.size() > 1 && s2[0] == '0'))
                    continue;
                long long next = d1 + d2;
                string nexts = to_string(next);
                string now = s1 + s2 + nexts;
                while (now.size() < num.size()) {
                    d1 = d2;
                    d2 = next;
                    next = d1 + d2;
                    nexts = to_string(next);
                    now += nexts;
                }
                if (now == num) return true;
            }
        }
        return false;
    }
};

int main() {
    Solution sol;
    cout << sol.isAdditiveNumber("123") << endl;
}