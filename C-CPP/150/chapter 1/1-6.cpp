#include <iostream>

using namespace std;

void swap(int &a, int &b) {
	int tmp = a;
	a = b;
	b = tmp;
}

void rotate(int a[][4], int n) { // counterclockwise
	for (int i = 0; i < n; i++)  //transpose
		for (int j = i + 1; j < n; j++) {
			swap(a[i][j], a[j][i]);
		}
	for (int i = 0; i < n/2; i++) //upside down
		for (int j = 0; j < n; j++) {
			swap(a[i][j], a[n-i-1][j]);
		}
}

void rotate2(int a[][4], int n) { // clockwise
	for (int i = 0; i < n/2; i++) {
		int first = i, last = n - i - 1;

		for (int j = first; j < last; j++) {
			int offset = j - first;

			int top = a[first][j];
			//left to top
			a[first][j] = a[last - offset][first];
			//bottom to left
			a[last - offset][first] = a[last][last - offset];
			//right to bottom
			a[last][last - offset] = a[j][last];
			//top to right
			a[j][last] = top;
		}
	}

}

int main(){
    int a[4][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };
    for(int i=0; i<4; ++i){
        for(int j=0; j<4; ++j)
            cout<<a[i][j]<<" ";
        cout<<endl;
    }
    cout<<endl;
    rotate(a, 4);
    for(int i=0; i<4; ++i){
        for(int j=0; j<4; ++j)
            cout<<a[i][j]<<" ";
        cout<<endl;
    }
	cout<<endl;
    rotate2(a, 4);
    for(int i=0; i<4; ++i){
        for(int j=0; j<4; ++j)
            cout<<a[i][j]<<" ";
        cout<<endl;
    }
    return 0;
}