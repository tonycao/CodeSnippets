#include <iostream>
#include <string>
#include <cmath>
#include <vector>

using namespace std;

// return the longest common prefix of s and t
string lcp(string s, string t) {
	int n = min(s.size(), t.size());
	for (int i = 0; i < n; i++) {
		if (s[i] != t[i]) 
			return s.substr(0, i);
	}
	return s.substr(0, n);
}

// return the longest repeated string in s

// Time complexity: O(mnlogn), Space complexity: O(n)
string lrs(string s) {
	// form the n suffixes
	int n = s.size();
	vector<string> suffixes(n);
	for (int i = 0; i < n; i++) {
		suffixes[i] = s.substr(i, n - i);
	}

	// sort them
	sort(suffixes.begin(), suffixes.end());

	// find longest repeated substring by comparing adjacent sorted suffixes
	string lrs;
	for (int i = 0; i < n - 1; i++) {
		string x = lcp(suffixes[i], suffixes[i + 1]);
		if (x.size() > lrs.size()) 
			lrs = x;
	}
	return lrs;
}

int main() {
	//string test("banana");
	cout << lrs("banana") << endl;

	cout << lrs("testest") << endl;

	cout << lrs( "abcdefg") << endl;
}