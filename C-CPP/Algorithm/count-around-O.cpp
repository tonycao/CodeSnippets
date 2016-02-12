#include <iostream>

using namespace std;

int CountSuroundO(string s) 

{ 

	int n = s.size(); 
	if(n==0) return 0; 

	int start = 0; 
	int pos = s.find('X', start); 
	if(pos == string::npos) return 0; 
	int prelen = pos-start; 

	start = pos+1; 
	int maxlen = 0; 

	while(1) 
	{ 
		int pos = s.find('X', start); 
		if(pos == string::npos) pos = n; 
		int len = pos-start; 
		cout << pos << " " << start << " " << len << endl;
		maxlen = max(maxlen, len+prelen); 
		prelen = len; 
		start = pos+1; 
		if(pos == n) break; 
	} 

	return maxlen; 
} 

int main() {
	string in("OOOXOOOOXOXOOOOXOXXOOO0");
	cout << CountSuroundO(in) << endl;
}