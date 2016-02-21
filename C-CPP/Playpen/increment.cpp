#include<iostream>

using namespace std;

int inc(int i) {
	if ((i & 0x1) == 0) {
		return i | 0x1;
	}
	return inc(i >> 1) << 1;
}

int main() {
	int i = 4987;
	cout << inc(i) << " " << inc(inc(i)) << endl;
}