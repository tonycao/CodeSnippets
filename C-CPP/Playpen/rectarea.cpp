#include <iostream>
using namespace std;

class Solution {
public:
    int computeArea(int A, int B, int C, int D, int E, int F, int G, int H) {
        int w = min(C, G) - max(A, E) < 0 ? 0 : min(C, G) - max(A, E);
        cout << w << endl;
        int h = min(D, H) - max(B, F) < 0 ? 0 : min(D, H) - max(B, F);
        cout << h << endl;
        int res =  (C - A) * (D - B) + (G - E) * (H - F);
        int overlap = (w == 0 || h == 0 ? 0 : w * h);
        cout << res << " "<< overlap<<endl;
        return res;
    }
};

int main() {
	Solution sol;
	sol.computeArea(-2, -2, 2, 2, -3, 3, -4, 4);
	return 0;
}