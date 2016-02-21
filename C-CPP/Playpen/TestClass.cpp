#include "TestClass.h"

TestClass::TestClass(void)
{
    //myMap.insert("test", &TestFunc);
    myMap["test"] = &TestFunc;
}

string TestClass::TestFunc(string input)
{
	return "";
}