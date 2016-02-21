#include <iostream>
#include <algorithm>

using namespace std;

void TabulateFunctionValues(double function(double)) {
 	for(double i = kLowerBound; i <= kUpperBound; i += kStepSize)
 	cout << "f(" << i << ") = " << function(i) << endl;
}
void TabulateFunctionValues(Reciprocal function) {
 	for(double i = kLowerBound; i <= kUpperBound; i += kStepSize)
 	cout << "f(" << i << ") = " << function(i) << endl;
}
void TabulateFunctionValues(Arccos function) {
 	for(double i = kLowerBound; i <= kUpperBound; i += kStepSize)
 	cout << "f(" << i << ") = " << function(i) << endl;
}


class LowerBoundHelper {
	 public:
	 explicit LowerBoundHelper(int lower) : lowestValue(lower) {}
	 int operator() (int bestSoFar, int current) {
	 return current >= lowestValue && current < bestSoFar?
	 current : bestSoFar;
	 }
	 private:
	 const int lowestValue;
};

template <typename UnaryFunction>
void TabulateFunctionValues(UnaryFunction function) {
 	for(double i = kLowerBound; i <= kUpperBound; i += kStepSize)
 		cout << "f(" << i << ") = " << function(i) << endl;
 }



