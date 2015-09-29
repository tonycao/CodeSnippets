/*
Write an algorithm which computes the number of trailing zeros in n factorial.
*/

#include <iostream>
using namespace std;

int NumZeros(int n) {
	if (n < 0) return -1;
	int count = 0;
	while((n /= 5) > 0) {
		count += n;
		cout<<count<<endl;
	}
	return count;
}

int main(){
	cout<<"tst"<< endl;
	int n = NumZeros(24);
	
	cout<<n<<endl;
	return 0;
}