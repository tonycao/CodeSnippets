#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>
#include <unordered_map>

using namespace std;

class compare {
public:
    bool operator()(const pair<string, int> x,const pair<string, int> y) const {
        return x.second > y.second;
    }
};

class compare_val { // comparison object with an argument passed by value
public:
    compare_val(int s_) : s(s_) {};
    bool operator()(const int x,const int y) const { return s*(x-y)>0; } // returns x>y if s>0, else x<y
    int s;
};


int main() {
    
    fstream fs("test.txt", ios::in);
    unordered_map<string, int> wordmap;
    
    if (fs.is_open()) {
        while(!fs.eof()) {
            string tmp;
            fs >> tmp;
            if (wordmap.find(tmp) != wordmap.end()) {
                wordmap[tmp]++;
            } else {
                wordmap[tmp] = 1;
            }
        }
    
    }
    fs.close();
    
    vector<pair<string, int>> wordfreq;
    for (auto iter = wordmap.begin(); iter != wordmap.end(); iter++) {
        wordfreq.push_back(make_pair(iter->first, iter->second));
    }
    
    sort(wordfreq.begin(), wordfreq.end(), compare());
    
    for (int i = 0; i < wordfreq.size(); i++) {
        cout << wordfreq[i].first << " " << wordfreq[i].second << endl;
        //cout << i;
    }
    
    
}