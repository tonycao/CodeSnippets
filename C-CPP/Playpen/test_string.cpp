#include <iostream>

using namespace std;

string func() {
	return "test";
}
int main(){
	string c;
	c = func();
	cout << func() << endl;

	return 0;
}