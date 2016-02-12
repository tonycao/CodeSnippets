#include <iostream>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

typedef map<string, int> My_Map;

struct print{
    void operator () (const My_Map::value_type &p){
        cout << p.second << " "
             << p.first << endl;
    }
};

int main(){
    My_Map my_map;
    for(string a_word; a_word!="end"; cin>>a_word ) my_map[a_word]++;
    for_each(my_map.begin(), my_map.end(), print()); // pay attention

    return 0;
}
