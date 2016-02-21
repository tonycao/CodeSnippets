#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class MedianFinder {
public:

    // Adds a number into the data structure.
    void addNum(int num) {
        minheap.push(-num); // adding one negative sign
        maxheap.push(-minheap.top());
        minheap.pop();

        if (maxheap.size() > minheap.size()) {
            minheap.push(-maxheap.top());
            maxheap.pop();
        }
    }

    // Returns the median of current data stream
    double findMedian() {
        return maxheap.size() < minheap.size()
            ? -minheap.top()
            : -(minheap.top() - maxheap.top()) / 2.0;
    }
public:
    priority_queue<long> maxheap, minheap;
    //priority_queue<int, vector<int>, greater<int>> minheap;
    
};

int main() {
    MedianFinder mf;
    mf.addNum(1);
    cout <<mf.findMedian() << endl;
    mf.addNum(2);
    cout <<mf.findMedian() << endl;
    cout << mf.maxheap.size() << " " << mf.minheap.size() << endl;
}