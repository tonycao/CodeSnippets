#include <iostream>
#include <cstdio>

using namespace std;

int main() {
	FILE *in;
	char buff[512];

	if(!(in = popen("ls -sail", "r"))){
		return 1;
	}

	while(fgets(buff, sizeof(buff), in)!=NULL){
		cout << buff;
	}
	pclose(in);

	return 0;
}
