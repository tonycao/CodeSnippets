#include <iostream>
#include <cstdio>

using namespace std;


void pwdcheck2(string c)
{
	int i , len= c.length();
	int ret1 = 0, ret2 = 0;
	
	for(i=0;i<len;i++)
	{
		char ch = c[i];
		if (ch >= 'a' && ch <= 'z')
			ret1 = 1;
		if (ch >= '0' && ch <= '9')
			ret2 = 1;
	}
	if (ret1)
		cout << "contains lower" << endl;
	if (ret2)
		cout << "contains number" << endl;
}

void pwdcheck3(string c)
{
	int len = c.length();
	int ret = 0,i,j;
	
	for(i=0;i<len;i++)
	{
		for (j=i+1;j<len;j++)
		{
			if (c[i] == c[j])
			{
				if (!c.substr(i, j - i).compare( c.substr(j, j - i)))
				  ret = 1;
			}
		}
	}	
	if (ret==1)
		cout << "contains repetition" << endl;
}
int main()
{
	string c("xyabcabc2kl");
	pwdcheck3(c);
	pwdcheck2(c);

	string test("12abc312c310cb");
	pwdcheck3(test);
	pwdcheck2(test);
}