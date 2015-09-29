#include <iostream>
#include <vector>

using namespace std;

vector<string> perm(string s) {

	vector<string> result;

	if (s == "") {
		result.push_back("");
		return result;
	}

	string tmp = s.substr(0, 1);

	vector<string> subresult = perm(s.substr(1));
	for (int i = 0; i < subresult.size(); i++) {
		string subs = subresult[i];
		for (int j = 0; j <= subs.length(); j++) {  // <= pay attention, if lose =, will not return any result
			string cur = subs;
			result.push_back(cur.insert(j, tmp));
		}
	}
	return result;
}

int main() {
	string test = "abcd";
	vector<string> result = perm(test);

	for (int i = 0; i < result.size(); i++) {
		cout << result[i] << endl; 
	}
	return 0;
}