#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <iterator>
using namespace std;


bool cmp(pair<int, int> a, pair<int, int> b) {
	if (a.first != b.first) {
		return a.first > b.first;
	} else {
		return a.second < b.second;
	} 
}


void sortwithFrequence(vector<int> &A) {
	unordered_map<int, int> hashmap;
	for (int i = 0; i < A.size(); i++) {
		if (hashmap.find(A[i]) != hashmap.end()) {
			hashmap[A[i]]++;
		} else {
			hashmap[A[i]] = 1;
		}
	}
	vector<pair<int, int>> AF;
	for (int i = 0; i < A.size(); i++ ) {
		auto iter = hashmap.find(A[i]);
		AF.push_back(make_pair(iter->second, iter->first));
	}
	sort(AF.begin(), AF.end(), cmp);

	for (int i = 0; i < AF.size(); i++) {
		A[i] = AF[i].second;
		//cout << AF[i].first << " " << AF[i].second << endl;
	}
	//cout << endl;
}

int main() {
	vector<int> A = {1, 2, 3, 4, 2, 3, 3, 4};
	sortwithFrequence(A);
	for (int i = 0; i < A.size(); i++) {
		cout << A[i] << endl;
	}
}