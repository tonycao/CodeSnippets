#include <iostream>
#include <set>
#include <iterator>

using namespace std;

int main(){
    const int N = 10;
    int a[N] = {4, 1, 1, 1, 1, 1, 0, 5, 1, 0};
    int b[N] = {4, 4, 2, 4, 2, 4, 0, 1, 5, 5};

    multiset<int> A(a, a+N);
    multiset<int> B(b, b+N);

    multiset<int> C;
    cout << "Set A: ";
    copy(A.begin(), A.end(), ostream_iterator<int>(cout, " "));
    cout << endl;

    cout << "Set B: ";
    copy(B.begin(), B.end(), ostream_iterator<int>(cout, " "));
    cout << endl;

    cout << "Union: ";
    set_union(A.begin(), A.end(), B.begin(), B.end(), ostream_iterator<int>(cout, " "));
    cout << endl;

    cout << "Intersection: ";
    set_intersection(A.begin(), A.end(), B.begin(), B.end(), ostream_iterator<int>(cout, " "));
    cout << endl;

    set_difference(A.begin(), A.end(), B.begin(), B.end(), inserter(C, C.end())); // pay attention
    cout << "Set C (difference of A and B): ";
    copy(C.begin(), C.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    return 0;

}
