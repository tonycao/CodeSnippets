#include <iostream>
#include <vector>
#include <climits>
using namespace std;

class Range {
private:
    int min;
    int max;
    bool empty;
public:
    Range(): min(INT_MAX), max(INT_MIN), empty(true){}

    bool contains(int a) {
        if (a >= min && a <= max){
            return true;
        } 
        return false;
    }

    void insert(int a) {
        if (a < min) {
            min = a;
        } 
        if (a > max) {
            max = a;
        }
        empty = false;
    }

    int getMin() {
        return min;
    }

    int getMax() {
        return max;
    }

    bool isEmpty() {
        return empty;
    }
};

int solution(vector<int>& A, int X, int D)
{
        if (D >= X-1) return true;

        int nBins = X / D + 1;
        vector<Range> ranges(nBins);
        ranges[0].insert(0);
        ranges[nBins-1].insert(X-1);

        int nImpassableGaps = nBins-1;

        for (int i = 0; i < A.size(); ++i) {
                int iBin = A[i]/D;        // index of the current bin

                // If the new element does not increase range, then it has no impact on result.
                if (ranges[iBin].contains(A[i]))
                        continue;

                // Get MIN of the next range, and MAX of the previous range
                // Special treatment for 0 and N-1th bin
                int nextMin = (iBin == nBins-1)?INT_MAX:ranges[iBin+1].getMin();
                int prevMax = (iBin == 0)?INT_MIN:ranges[iBin-1].getMax();

                // Decide if the current bin is reachable from the next and previous range.
                bool cannotReachNext = (ranges[iBin].isEmpty())?true:ranges[iBin].getMin() - prevMax > D;
                bool cannotReachPrev = (ranges[iBin].isEmpty())?true:nextMin - ranges[iBin].getMax() > D;

                // If iBin-1 and iBin were not connected previously
                // but now they are (because of the newly added
                // element), reduce nImpassbleGap
                if (cannotReachNext && A[i] - prevMax <= D) {
                        nImpassableGaps--;
                }

                if (cannotReachPrev && nextMin - A[i] <= D) {
                        nImpassableGaps--;
                }
                ranges[iBin].insert(A[i]);
                if (nImpassableGaps == 0) return i;
        }
        return -1;
}

int main() {
    vector<int> A = {1, 3, 1, 4, 2, 5};
    int X = 7;
    int D = 3;
    cout << solution(A, X, D) << endl;

}