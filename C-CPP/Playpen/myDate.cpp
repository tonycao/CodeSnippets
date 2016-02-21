#include <iostream>
#include "myDate.h"
using namespace std;

myDate first = {.year = 1900, .day = 1, .month = 1};

int main() {
	cout << first.year << " " << first.day << " " << first.month << endl;
	return 0;
}