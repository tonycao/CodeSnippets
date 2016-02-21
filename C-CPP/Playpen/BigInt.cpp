#include <iostream>
#include <vector>
#include <string>
using namespace std;

class BigInt {
private:
    int sign; // -1 or 1;
    vector<char> digits;

public:
    BigInt(const int &capacity) : sign(1), digits(capacity)	 {}

    BigInt(const string &s) : sign(s[0] == '-' ? -1 : 1),
    						  digits(s.size() - (s[0] == '-')) {
        for (int i = (int)s.size() - 1, j = 0; i >= (s[0] == '-'); i--, j++) {
            if (isdigit(s[i])) {
                digits[j] = s[i] - '0';
            }
        }
    }

    BigInt operator*(const BigInt &n) const {
    	vector<char> num1 = digits;
    	vector<char> num2 = n.digits;
    	//reverse(num1.begin(), num1.end());
    	//reverse(num2.begin(), num2.end());
        BigInt result((int)num1.size() + (int)num2.size());
        result.sign = sign * n.sign;
        int i, j = 0;
        for (i = 0; i < num1.size(); i++) {
            for (j = 0; j < num2.size(); j++) {
                    result.digits[i + j] += num1[i] * num2[j];
                    result.digits[i + j + 1] += result.digits[i + j] / 10;
                    result.digits[i + j] %= 10;
            }
        }

        // If one number is 0, the result size should be 0
        /*if ((digits.size() == 1 && digits.front() == 0) ||
            (n.digits.size() == 1 && n.digits.front() == 0)) {
            result.digits.resize(1);
        } else {
            result.digits.resize(i + j - 1);
        }*/
        while(result.digits.size() != 1 && (int)result.digits.back() == 0) {
        	result.digits.pop_back();
        }

        reverse(result.digits.begin(), result.digits.end());
        return result;
    }

    void print() {
        for (auto a:digits) {
            cout << (int)a;
        }
        cout << endl;
    }
};

int main() {
    string astr = "110";
    string bstr = "213";
    BigInt a = astr;
    BigInt b = bstr;
    BigInt c = a*b;
    c.print();
    return 0;
}
