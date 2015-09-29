/*
Given a sorted array of strings which is interspersed with empty strings, write a method to find the location of a given string.

Example: find “ball” in [“at”, “”, “”, “”, “ball”, “”, “”, “car”, “”,“”, “dad”, “”, “”] will return 4

Example: find “ballcar” in [“at”, “”, “”, “”, “”, “ball”, “car”, “”, “”, “dad”, “”, “”] will return -1

*/

#include <iostream>

using namespace std;

int search(string s[], int n, string key) {
	if (key == "") return -1;
	int low = 0, high = n - 1;

	while (low <= high) {
		int mid = low + (high - low) / 2;
		int t = mid;
		while (s[t] == "" && t <= high) ++t;
		if (t > high) high = mid - 1;
		else {
			if (s[t].compare(key) == 0) return t;
			else if (s[t].compare(key) < 0) low = t + 1;
			else high = mid - 1;
		}
	}
	return -1;
}

int main(){
    string s[13] = {
        "at", "", "", "", "ball", "", "", "car", "", "", "dad", "", ""
    };
    cout<< search(s, 13, "ball") << endl;
    cout<< search(s, 13, "at") << endl;
    cout<< search(s, 13, "car") << endl;
    return 0;
}