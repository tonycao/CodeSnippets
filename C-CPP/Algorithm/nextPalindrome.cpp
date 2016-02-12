#include <iostream>
#include <string>
using namespace std;

string nextPalindrome2(string &num) {
    if (num.empty()) return "1";
    int i, j, length = num.length();
    if (length % 2 == 0) {
        i = length / 2 - 1;
        j = length / 2;
    } else {
        i = j = length / 2;
    }

    int carry = 1;

    while ( i >= 0 && j < length) {
        if (num[i] > num[j] && carry != 1) num[j] = num[i];
        else {
            if (carry == 1) {
                carry = (num[i] - '0' + 1) / 10;
                num[i] = num[j] = (num[i] - '0' + 1) % 10 + '0';
            } else {
                num[j] = num[i];
            }
        }
        i--; j++;
    }
    if (carry == 1) {
        num.insert(num.begin(), '1');
        num[num.length() - 1] = '1';
    }

    return num;
}





bool all9s(string num, int n) {
    for (int i = 0; i < n; i++) {
        if (num[i] != '9')
            return false;
    }
    return true;
}

void genNextPalindrome(string &num, int n) {
    int mid = n / 2;
    bool leftsmaller = false;
    int i = mid - 1;
    int j = (n % 2) ? mid + 1 : mid;

    while (i >= 0 && num[i] == num[j] ) {
        i--, j++;
    }

    if (i < 0 || num[i] < num[j])
        leftsmaller = true;

    if (!leftsmaller) {
        while (i >= 0 ) {
            num[j] = num[i];
            j++;
            i--;
        }
    }
    else {
        int carry = 1;
        i = mid - 1;
        if (n % 2 == 1) {
            int midval = num[mid] - '0';
            midval += carry;
            carry = midval / 10;
            midval %= 10;
            num[mid] = (char)midval + '0';
            j = mid + 1;

        } else
            j = mid;

        while (i >= 0) {
            if (carry) {
                int tmpval = num[i] - '0';
                tmpval += carry;
                carry = tmpval / 10;
                tmpval %= 10;
                num[i] = (char)tmpval + '0';
            }
            num[j++] = num[i--];

        }
    }
}

void nextPalindrome(string &num, int n) {
    int i;
    if (all9s(num, n)) {
        cout << "1";
        for (i = 1; i < n; i++) {
            cout << "0";
        }
        cout << "1" << endl;
    } else {
        genNextPalindrome( num, n);
        cout << num << endl;
    }
}

void printArray(string num, int n) {
    for (int i = 0; i < n; i++) {
        cout << num[i];
    }
    cout << endl;
}

int main() {
    long long int t =  1;
    //char num[1000000];
    string num("123456789");
    while (t) {
        //cin >> num;
        int n = num.length();
        //nextPalindrome(num, n);
        cout << nextPalindrome2(num) << endl;
        t--;
    }
    return 0;
}
