#include <iostream>
#include <queue>

using namespace std;

int main(){
    long n, k, x, y, i;
    priority_queue<int, vector<int>, less<int> > maxpq; //max heap

    cin>>n>>k;

    for(i = 0; i < k; i++){
        cin >> x;
        maxpq.push(x);
    }
    for(; i< n; i++){
        cin >> x;
        if (x!=-1){
            if(x < maxpq.top()){
                y = maxpq.top();
                maxpq.pop();
                maxpq.push(x);
            }
        }
        else{
            x = maxpq.top();
            cout << x;
        }
    }
    for(i = 0; i<k; i++){
        cout << maxpq.top()<<" ";
        maxpq.pop();
    }
    cout << endl;
    return 0;
}
