#include <iostream>
#include <iterator>
#include <set>
#include <assert.h>

using namespace std;

int main(){
    set<int> a_set;

    for (int i = 1; i <= 5; ++i){
        a_set.insert(60 - 10*i);
    }
    pair<set<int>::iterator, bool> ret = a_set.insert(20);  // return true if insert successfully
    assert(ret.second == false);

    int myints[] = {5, 10, 15};
    a_set.insert(myints, myints+3);

    copy(a_set.begin(), a_set.end(), ostream_iterator<int> (cout, "\n")); //set is in order

    return 0;
}
