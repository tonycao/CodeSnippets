#include <iostream>
using namespace std;
int main(int argc, char *argv[]) {
    int a = 0;
    int b = (++a) + (++a) + (++a);
    cout<<b;
    return 0;
}