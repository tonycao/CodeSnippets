#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <vector>
using namespace std;

struct Item {
    int counter;
    char c;
    
    Item(): counter(0), c('\0') {};
    Item(int counter_, char c_) : counter(counter_), c(c_) {};
    Item(const Item &anotherItem): counter(anotherItem.counter), c(anotherItem.c) {};
};

struct ItemCompare {
    Item* prev;
    
    ItemCompare(Item* prevItem): prev(prevItem) {};
    
    bool operator() (const Item &item1, const Item &item2) {
        if (!prev) {
            return item1.counter < item2.counter;
        } else {
            if (prev->c == item1.c) {
                return true;
            } else if (prev->c == item2.c){
                return false;
            } else {
                return item1.counter < item2.counter;
            }
        }
    }
};

string shuffle(string str) {
    if (str.empty()) return str;
    
    unordered_map<char, Item> m;
    for_each(str.begin(), str.end(), [&](char c) {
        if (m.count(c)) {
            ++m[c].counter;
        } else {
            m[c] = Item(1, c);
        }
    });
    
    vector<Item> items;
    for (auto kv: m) {
        items.push_back(kv.second);
    }
    
    string result;
    Item* prev = NULL;
    
    while (!items.empty()) {
        make_heap(items.begin(), items.end(), ItemCompare(prev));
        
        result.push_back(items.front().c);
        
        if (!--items.front().counter) {
            pop_heap(items.begin(), items.end(), ItemCompare(prev));
            items.pop_back();
            prev = NULL;
        } else {
            prev = &(items.front());
        }
        
    }
    
    return result;
};

int main() {
    // your code goes here
    
    cout << shuffle("aabb") << endl;
    cout << shuffle("aaabb") << endl;
    cout << shuffle("aabbb") << endl;
    cout << shuffle("aabbbcc") << endl;
    cout << shuffle("aabbc") << endl;
    cout << shuffle("aabbcc") << endl;
    cout << shuffle("aabbbbcc") << endl;
    cout << shuffle("aabbbbc") << endl;
    return 0;
}
