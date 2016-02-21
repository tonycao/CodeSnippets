#include <iostream>
#include <map>
#include <vector>
#include <stack>
#include <string>
#include <climits>
#include <cmath>

using namespace std;

typedef int (* op)(int, int);

class RPN{

public:
	
	
	//set<string> opSet;
	RPN() {
		addOperator("+", &add);
		addOperator("-", &minus);
		addOperator("*", &multiplication);
		addOperator("/", &division);
		//opMap["+"] = &add;
		//opMap["-"] = &minus;
		//opMap["*"] = &multiplication;
		//opMap["/"] = &division;


	}

	int doRPN(vector<string>& tokens) {
		if (tokens.size() == 0) return INT_MIN;
		stack<int> opStack;

		for (int i = 0; i < tokens.size(); i++) {
			if (isOperator(tokens[i])) {
				if (opStack.size() >= 2) {
					int op2 = opStack.top();
					opStack.pop();
					int op1 = opStack.top();
					opStack.pop();
					//opStack.push(cal(op1, op2, tokens[i]));
					//op curOp = opMap[tokens[i]];
					opStack.push(opMap[tokens[i]](op1, op2));
				} else {
				return 0.0;
				}
			} else {
				opStack.push(stoi(tokens[i]));
			}
		}
		if (opStack.size() == 1) return opStack.top();
		else return INT_MIN;
 	}
 	void addOperator(string str, op op) {
 		opMap[str] = op;
 	}

private:

	map<string, op> opMap;

	bool isOperator(string str) {
		return opMap.find(str) != opMap.end();
		//return str == "+" || str == "-" || str == "*" || str == "/";
	}

	int cal(int op1, int op2, string op) {
		if (op == "+") return op1 + op2;
		else if (op == "-") return op1 - op2;
		else if (op == "*") return op1 * op2;
		else return op1 / op2;
	}

	// pre-defined operators
 	static int add(int a, int b) {
		return a + b;
	}

	static int minus(int a, int b) {
		return a - b;
	}

	static int multiplication(int a, int b) {
		return a * b;
	}

	static int division(int a, int b) {
		return a / b;
	}
	
};

// user defined operator
static int power(int a, int b) {
	return (int)pow(a, b);
}

// test
int main() {

	RPN rpn;
	vector<string> tokens;

	cout << rpn.doRPN(tokens) << endl;

	tokens.push_back("5");
	tokens.push_back("6");
	tokens.push_back("*");
	tokens.push_back("4");
	tokens.push_back("+");
	tokens.push_back("2");
	tokens.push_back("*");
	tokens.push_back("6");
	tokens.push_back("+");
	tokens.push_back("2");
	tokens.push_back("^");
	
	rpn.addOperator("^", &power); // add user defined operator
	
	cout << rpn.doRPN(tokens) << endl;

	return 0;
}