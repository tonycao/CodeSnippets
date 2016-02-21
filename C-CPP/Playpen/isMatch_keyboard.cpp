#include <iostream>

using namespace std;


bool IsAMatch(string actual, string expected)
{
	char faultyKey = '\0';
	int i = 0, j = 0;
	for(; i < expected.length() && j < actual.length(); ++i)
	{
		if(actual.at(j) != expected.at(i))
		{
			if('\0' != faultyKey)
			{
				if(faultyKey != expected.at(i))
					return false;
			}
			else
			{
				faultyKey = expected.at(i);
			}
		}
		else
		{
			++j;
		}
	}

	cout << i << " " << j << endl;
	while(i<expected.length() && expected.at(i) == faultyKey)
		i++;
	cout << i << " " << j << endl;
	return (i == expected.length() && j == actual.length() )? true : false;
}

int main() {
	string act("164");
	string expect("1868488");
	string expect2("186847");
	cout << IsAMatch(act, expect) << endl;
	cout << IsAMatch(act, expect2) << endl;
	return 0;
}