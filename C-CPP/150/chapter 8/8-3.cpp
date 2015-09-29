//Write a method that returns all subsets of a set.

#include <iostream>
#include <vector>
using namespace std;


vector<vector<int> > get_subsets(int a[], int n){ //O(n2^n)
    vector<vector<int> > subsets;
    int max = 1<<n;
    for(int i=0; i<max; ++i){
        vector<int> subset;
        int idx = 0;
        int j = i;
        while(j > 0){
            if(j&1){
                subset.push_back(a[idx]);
            }
            j >>= 1;
            ++idx;
        }
        subsets.push_back(subset);
    }
    return subsets;
}

vector<vector<int> > get_subsets1(int a[], int idx, int n) {
    vector<vector<int> > subsets;
    if(idx == n) {
        vector<int> subset;
        subsets.push_back(subset); //empty set
    }
    else {
        vector<vector<int> > rsubsets = get_subsets1(a, idx+1, n);
        int v = a[idx];
        for(int i = 0; i < rsubsets.size(); ++i) {
            vector<int> subset = rsubsets[i];
            subsets.push_back(subset);
            subset.push_back(v);
            subsets.push_back(subset);
        }
    }
    return subsets;
}

void print_subsets(vector<vector<int> > subsets) {
    for(int i = 0; i < subsets.size(); ++i) {
        vector<int> subset = subsets[i];
        for(int j = 0; j < subset.size(); ++j) {
            cout<<subset[j]<<" ";
        }
        cout<<endl;
    }
}

int main() {
    int a[] = {
        1, 2, 3, 4
    };
    vector<vector<int> > sub = get_subsets(a, 4);
    vector<vector<int> > sub1 = get_subsets1(a, 0, 4);
    print_subsets(sub);
    print_subsets(sub1);
    
    return 0;
}