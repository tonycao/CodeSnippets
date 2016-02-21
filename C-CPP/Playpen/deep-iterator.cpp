//#include "head.h"
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <exception>

using namespace std;

//const int TYPE_ITEM = 0;
//const int TYPE_NESTED = 1;
enum enumtype {TYPE_ITEM, TYPE_NESTED};

class myexception: public exception
{
	virtual const char* what() const throw()
	{
		return "My exception happened";
	}
} myex;


class Item {
public:
	int value;
	enumtype type;
	vector<Item *> children;

	Item(): type(TYPE_NESTED) {}
	Item(int v): type(TYPE_ITEM), value(v) {}
};

class Iterator {
private:
	stack<pair<Item *, int>> stk;
	Item *top = nullptr;
public:
	Iterator(Item * it) {
		stk.push(pair<Item *, int>(it, 0));
		//advanceToNext();
	}
	bool hasNext() {
		//return !stk.empty();
		//if (this->top != nullptr) return true;
		//if (!stk.empty()) return true;
		while (!stk.empty()) {
			auto it = stk.top();
			if (it.first->type == TYPE_ITEM) {
				return true;
			} else {
				if (it.second < it.first->children.size()) {
					int index = it.second;
					stk.top().second++;
					stk.push(pair<Item *, int>(it.first->children[index], 0));
				} else {
					stk.pop();
				}
				//return hasNext();
			}
		}
		return false;
	}
	int next() {
		//if (!hasNext()) {
		//	return -1;
		//}
		if (hasNext()) {
			auto it = stk.top();
			stk.pop();
			//int tmp = it.first->value;
			//top = nullptr;
			return it.first->value;;
		} else {
			try
			{
				throw myex;
			}
			catch (exception& e)
			{
				cout << e.what() << '\n';
			}
		}
		return -1;
	}
};



int main() {
	Item i1(1), i2(2), i3(3), i4(4), i5(5), i6(6), i7(7), i8(8), i9(9), i10(10);
	Item a45;
	a45.children.push_back(&i4);
	a45.children.push_back(&i5);

	Item a67;
	a67.children.push_back(&i6);
	a67.children.push_back(&i7);

	Item a345678;
	a345678.children.push_back(&i3);
	a345678.children.push_back(&a45);
	a345678.children.push_back(&a67);
	a345678.children.push_back(&i8);

	Item all;
	all.children.push_back(&i1);
	all.children.push_back(&i2);
	all.children.push_back(&a345678);
	all.children.push_back(&i9);
	all.children.push_back(&i10);

	Iterator iter(&all);
	int i = 0;
	//while (iter.hasNext()) {
	while (i < 11) {
		cout << iter.next() << endl;
		i++;
	}

	return 0;
}