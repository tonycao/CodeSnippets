#include <iostream>
#include <map>
using namespace std;




class TestClass
{
private:
    MyMap myMap;

public:
    TestClass(void);
    string TestFunc(string input);
};

typedef string(TestClass::*myFunc)(string);
typedef map<string, myFunc> MyMap;
