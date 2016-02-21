#include <iostream>
#include <map>
#include <unordered_map>
#include <iterator>

using namespace std;

class uber {
public:
	void put(int key, int value, int vtime) {
		auto iter = hashmap.find(key);
		if ( iter == hashmap.end()) {
			hashmap[key] = {{vtime, value}};
		} else {
			iter->second.insert(make_pair(vtime, value));
		}
	}
	int get(int key, int vtime) {
		auto iter = prev(hashmap[key].lower_bound(vtime));
		//cout << key << ":" << tmp.lower_bound(vtime)->first << ":" << tmp.lower_bound(vtime)->second << endl;
		//cout << key << ":" << tmp.upper_bound(vtime)->first << ":" << tmp.upper_bound(vtime)->second << endl;
		//return hashmap[key].lower_bound(time)->second;
		return iter->second;
	}

	void iterate() {
		for (auto iter : hashmap) {
			for (auto iter2 = (iter.second).begin(); iter2 != (iter.second).end(); iter2++) {
				cout << iter2->first << ":"<< iter2->second << " ";
			}
			cout << endl;
		}
	}

private:
	unordered_map<int, map<int, int>> hashmap;
};

int main() {
	uber test;
	test.put(1, 1, 1);
	test.put(1, 2, 10);
	test.put(1, 4, 11);
	test.put(1, 11, 21);
	test.put(2, 6, 4);
	test.put(2, 12, 11);
	test.put(2, 5, 2);
	test.put(3, 7, 9);
	test.put(3, 9, 12);

	test.iterate();
	

	cout << test.get(1, 5) << endl;
	cout << test.get(1, 9) << endl;
	cout << test.get(1, 15) << endl;
	cout << test.get(2, 5) << endl;

}
