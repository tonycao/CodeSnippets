#include <iostream>
#include <list>
#include <iterator>
#include <algorithm>

using namespace std;

int main(){
    list<string> a_list;
    a_list.push_back("banana");
    a_list.push_front("apple");
    a_list.push_back("carrot");

    ostream_iterator<string> out_it(cout, "\n");

    copy(a_list.begin(), a_list.end(), out_it);
    reverse_copy(a_list.begin(), a_list.end(), out_it);
    copy(a_list.rbegin(), a_list.rend(), out_it);

    return 0;
}
