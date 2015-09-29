#include <iostream>
#include <cstring>

using namespace std;

void zero(int a[][4], int m, int n) {
	bool row[m], col[n];
	memset(row, false, sizeof(bool)*m);
	memset(col, false, sizeof(bool)*n);

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (a[i][j] == 0) {
				row[i] = true;
				col[j] = true;
			}
		}
	} 

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if(row[i] || col[j]) a[i][j] = 0;
		}
	}
}

int main(){
	int a[4][4] = {
        {1, 2, 3, 4},
        {5, 0, 7, 8},
        {9, 10, 0, 12},
        {13, 14, 15, 16}
    };

    for(int i=0; i<4; ++i){
        for(int j=0; j<4; ++j)
            cout<<a[i][j]<<" ";
        cout<<endl;
    }
    cout<<endl;

    zero(a, 4, 4);

    for(int i=0; i<4; ++i){
        for(int j=0; j<4; ++j)
            cout<<a[i][j]<<" ";
        cout<<endl;
    }
    cout<<endl;

	return 0;
}