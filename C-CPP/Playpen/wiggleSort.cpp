#include <iostream>
#include <vector>
using namespace std;

void wiggleSort(vector<int> &a) {
	int n = a.size();
	int flag = 1;
	for (int i = 0; i < n - 1; i++) {
		if (flag*a[i] > flag*a[i + 1]) {
			int tmp = a[i];
			a[i] = a[i + 1];
			a[i + 1] = tmp;
		}
		flag *= -1;
	}
}

void wiggleSort2(vector<int> &a) {
	int n = a.size();
	bool flag = true;
	int current = a[0];
	for (int i = 0; i < n - 1; i++) {
		if ((flag && (current > a[i + 1])) || (!flag && (current < a[i + 1])) ) {
			a[i] = a[i + 1];
		} else {
			a[i] = current;
			current = a[i + 1];
		}
		flag = !flag;
	}
	a[n - 1] = current;
}


int main() {
	vector<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	wiggleSort(a);

	for (int i = 0; i < a.size(); i++) {
		cout << a[i] << " ";
	}
	cout << endl;

	vector<int> b = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	wiggleSort2(b);
	
	for (int i = 0; i < b.size(); i++) {
		cout << b[i] << " ";
	}
	cout << endl;
	return 0;
}