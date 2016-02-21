// telephone number combination

#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
private:
	unordered_map<int, string> umap;

	void combination(string digits, int cur, string& str, vector<string> &res) {
		if (cur == digits.length()) {
			res.push_back(str);
			return;
		}

		string s = umap[digits[cur] - '0'];
		for (int i = 0; i < s.length(); i++) {
			str += s[i];
			combination(digits, cur+1, str, res);
			str.erase(str.end() - 1);
		}
	}
public:
	Solution() {
		umap[2] = "abc";
		umap[3] = "def";
		umap[4] = "ghi";
		umap[5] = "jkl";
		umap[6] = "mno";
		umap[7] = "pqrs";
		umap[8] = "tuv";
		umap[9] = "wxyz";
	}

	vector<string> letterCombinations(string digits) {
		vector<string> res;
		string str;
		if (digits.empty()) return res;
		combination(digits,  0, str, res);
		return res;
	}
};

int main() {
	Solution sol;
	string s("234");
	s.insert(s.end(), 1, '5');
	cout <<  s << endl;
	s.erase(s.end()-1);
	cout <<  s << endl;
	vector<string> res = sol.letterCombinations(s);
	for (int i = 0; i < res.size(); i++) {
		cout << res[i] << endl;
	}

	return 0;
}