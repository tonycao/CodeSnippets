#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;


double getMedian(vector<int> &a, priority_queue<int, vector<int>, less<int>> &maxq, priority_queue<int, vector<int>, greater<int>> &minq) {
    maxq.push(a[0]);
    for (int i = 1; i < a.size(); i++) {
        if (maxq.size() > minq.size()) {
            if (a[i] < maxq.top()) {
                minq.push(maxq.top());
                maxq.pop();
                maxq.push(a[i]);
            } else {
                minq.push(a[i]);    
            }
        } else { //if (maxq.size() <= minq.size()) {
            if (a[i] < maxq.top()) {
                maxq.push(a[i]);    
            } else {
                maxq.push(minq.top());
                minq.pop();
                minq.push(a[i]);    
            }
        } 
        /*else { // maxq.size() == minq.size()
            if (a[i] < maxq.top()) {
                maxq.push(a[i]);    
            } else {
                minq.push(a[i]);
            }
        }*/
    }
    
    if (a.size() % 2 == 0) return (maxq.top() + minq.top())/2.0;
    if (a.size() % 2 == 1) return maxq.top();
}


int main()
{
    priority_queue<int, vector<int>, less<int>> maxq; // maxheap
    priority_queue<int, vector<int>, greater<int>> minq; // minheap
    vector<int> a = {1, 2, 4, 5, 5, 6, 7, 8, 9, 11, 11, 12, 20, 13, 21, 10};
    
    double med = getMedian(a, maxq, minq);
    
    
    cout << a.size() << " " << med << endl;
    //cout << double(nums[0] + nums[nums.size()-1])/2.0 << endl;
    return 0;
}
