#include <iostream>
#include <map>
using namespace std;


//typedef map<string, myFunc> MyMap;
class Test;

typedef string(Test::*myFunc)(string);
typedef map<string, myFunc> MyMap;
MyMap myMap;

class Test
{

//private:
//    MyMap myMap;

public:
    Test(void);
    string TestFunc(string input);
};

//#include "Test.h"

Test::Test(void)
{

}

string Test::TestFunc(string input)
{
	//cout << input << endl;
	return input;
}

int main() {
	string str("test!!!");
	Test test;
	myMap["test"] = &Test::TestFunc;
	myFunc myf = myMap["test"];
	cout << (test.*myf)("Hello World!") << endl;
	return 0;
}