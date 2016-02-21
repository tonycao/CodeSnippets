// string transpose

#include <iostream>

using namespace std;

int main() {
	string s1("abcddaef");
	string s2("dadfebac");

	int i = 0;
	while(i < s2.length()) {
		if (s1[i] == s2[i]) {
			i++;
		}
		else {
			for (int j = i; j < s1.length() - 1; j++) {
				int tmp = s1[j];
				s1[j] = s1[j+1];
				s1[j+1] = tmp;
			}
		}
	}
	cout << s1 <<endl;
	cout << s2 << endl;
}