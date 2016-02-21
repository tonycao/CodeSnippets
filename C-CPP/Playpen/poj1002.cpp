#include <iostream>
#include <iomanip>
#include <algorithm>
#include <map>
#include <vector>

using namespace std;
char s[31];

int main() {
	long int n; 
	cin >> n;
	int nums[n];
	//map<int, int> nummap;
	//vector<int> nums;
	for (int i = 0; i < n; i++) {
		//int k = 7;
		int sum = 0;
		cin >> s;
		//cout << s <<endl;
		for(int j = 0, k = 7; k > 0; j++) {
			//char input;
			
	        if(s[j] >='0'&& s[j]<='9')
	        {
	            sum *= 10; k--;
	            sum += (s[j]-'0');
	        }
	        else if(s[j] >='A'&& s[j] <'Z')
	        {
	            sum *= 10; k--;
	            sum += ((s[j] -'A'- (s[j] >'Q'))/3+2);
	        }
		}
		//cout << sum <<endl;
		nums[i] = sum;
	}
	
	sort(nums, nums+n);
	bool dup = false;
	for (int i = 0; i < n-1; i++) {
		int count = 1;
		
		while( nums[i] == nums[i+1]) {
			count++;
			i++;
		}
		if (count > 1) {
			
			dup = true;
			cout << setw(3) << setfill('0') << nums[i]/10000; 
			cout << "-" << setw(4) << setfill('0') << nums[i] % 10000 ;
			cout << " " << count << endl;
		}
	}
	if (!dup) cout << "No duplicates."<<endl;
	return 0;
}

