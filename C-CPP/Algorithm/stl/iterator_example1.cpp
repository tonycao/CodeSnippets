#include <iostream>
#include <vector>
#include <string>
#include <iterator>

using namespace std;

int main(int argc, char *argv[]){
    vector<string> projects;

    for(int i = 1; i < argc; ++i){
        projects.push_back(string(argv[i]));
    }

    // auto is 11x standard
    for(vector<string>::iterator j = projects.begin(); j != projects.end(); ++j){
        cout<< *j<< endl;
    }

    // fill a vector with values read from standard input.
    vector<int> v;
    for(istream_iterator<int> i = cin; i != istream_iterator<int>(); ++i)
        v.push_back(*i);
    copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
    cout << endl;

    // fill vector with values read from stdin using std::copy()
    //v.clear();
    //copy(istream_iterator<int> (cin), istream_iterator<int>(), back_inserter(v));
    //copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
    //cout << endl;

    //copy a file to cout via a loop


    return 0;
}
