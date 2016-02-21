#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <string>
using namespace std;

/* //example 1
bool is_greater_than_5(int value)
{
	return (value > 5);
}

int main()
{
	vector<int> numbers { 1, 2, 3, 4, 5, 10, 15, 20, 25, 35, 45, 50 };
	auto greater_than_5_count = count_if(numbers.begin(), numbers.end(), is_greater_than_5);
	auto greater_than_5_count_lambda = count_if(numbers.begin(), numbers.end(), [](int x) { return (x > 5); });
	cout << "The number of elements greater than 5 is: "
	     << greater_than_5_count_lambda << "." << endl;
}*/

/* // example 2
void printnumber(int y) {
	cout << y << endl;
}

struct printnumberclass {
	void operator() (int y) { cout << y << endl; }
} printnumberobject;

int main()
{
	vector<int> numbers { 1, 2, 3, 4, 5, 10, 15, 20, 25, 35, 45, 50 };
	//for_each(numbers.begin(), numbers.end(), printnumber);
	for_each(numbers.begin(), numbers.end(), [](int y)
	{
		cout << y << endl;
	});
}*/

/*// example 3
int main()
{
	// The user would introduce different values for divisor
	int sum = 0;
	int divisor = 3;
	vector<int> numbers { 1, 2, 3, 4, 5, 10, 15, 20, 25, 35, 45, 50 };
	//for_each(numbers.begin(), numbers.end(), [divisor] (int y)
	//for_each(numbers.begin(), numbers.end(), [=] (int y)
	for_each(numbers.begin(), numbers.end(), [divisor, &sum] (int y)
	{
		if (y % divisor == 0)
		{
			cout << y << endl;
			sum += y;
		}
	});
	cout << sum << endl;
}*/

// example 4
void run_within_for_each(std::function<void (int)> func)
{
	vector<int> numbers{ 1, 2, 3, 4, 5, 10, 15, 20, 25, 35, 45, 50 };

	for_each(numbers.begin(), numbers.end(), func);
}

int main()
{
	int a = 0, b = 0;
	auto func1 = [](int y)
	{
		cout << y << endl;
	};

	auto func2 = [](int z)
	{
		cout << z * 2 << endl;
	};

	run_within_for_each(func1);
	run_within_for_each(func2);
	cout << to_string(10) + "->" + to_string(20) << endl;
}






