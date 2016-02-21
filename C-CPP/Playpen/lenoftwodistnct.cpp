#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

class Solution {
public:
	int lengthOfLongestSubstringTwoDistinct(string s) {
		int i = 0, j = -1, maxLen = 0;
		for (int k = 1; k < s.length(); k++) {
			if (s[k] == s[k - 1]) continue;
			if (j >= 0 && s[j] != s[k]) {
				maxLen = max(k - i, maxLen);
				cout << k << " " << i << " " << j << " " << maxLen << endl;
				i = j + 1;
			}
			j = k - 1;
		}
		return max((int)(s.length() - i), maxLen);
	}
	int lengthOfLongestSubstringKDistinct(string s, int t) {
		vector<int> count(256, 0);
		int i = 0, numDistinct = 0, maxLen = 0;
		for (int k = 0; k < s.length(); k++) {
			if (count[s[k]] == 0) numDistinct++;
			count[s[k]]++;
			while (numDistinct > t) {
				count[s[i]]--;
				if (count[s[i]] == 0) numDistinct--;
				i++;
			}
			maxLen = max(k - i + 1, maxLen);
		}
		return maxLen;
	}
};


int main() {
	Solution sol;
	string s("kececeba");
	cout << sol.lengthOfLongestSubstringTwoDistinct(s) << endl;
	cout << sol.lengthOfLongestSubstringKDistinct(s, 3) << endl;
	return 0;
}