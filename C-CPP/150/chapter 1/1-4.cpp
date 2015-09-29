#include <iostream>
//#include <cstdio>
//#include <cstdlib>
#include <string>
#include <cstring>
#include <algorithm>

using namespace std;

bool isAnagram(string s, string t) {
	if (s == "" || t == "") return false;
	if (s.length() != t.length()) return false;

	int len = s.length();
	int c[256];
	memset(c, 0, sizeof(c));

	transform(s.begin(), s.end(), s.begin(), ::tolower);
	transform(t.begin(), t.end(), t.begin(), ::tolower);

	for (int i = 0; i < len; i++) {
		++c[(int)s[i]];
		//--c[(int)t[i]];
	}

	for (int i = 0; i < len; i++) {
		if(--c[(int)t[i]] < 0) return false;
	}

	//for (int i = 0; i < 256; i++) {
	//	if (c[i] != 0) return false;
	//}
	return true;
}

bool isAnagram2(string s, string t) {
	if (s == "" || t == "") return false;
	if (s.length() != t.length()) return false;
	
	transform(s.begin(), s.end(), s.begin(), ::tolower);
	transform(t.begin(), t.end(), t.begin(), ::tolower);

	sort(&s[0], &s[0]+s.length());
	sort(&t[0], &t[0]+t.length());

	if (s.compare(t) == 0) return true;
	else return false;
}

//need check the case of the string

int main() {

	string s = "test1";
	string t = "test11";

	string s2 = "teSt2";
	string t2 = "Test2";

	cout<< isAnagram(s, t) << endl;
	cout<< isAnagram2(s2, t2) << endl;
}