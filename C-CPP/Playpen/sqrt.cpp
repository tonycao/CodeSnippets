#include <iostream>
#include <cmath>
#include <cassert>
using namespace std;

double squareroot(double x)
{
    assert(x >= 0);
    double xhi = x;
    double xlo = 0;
    double guess = x/2;

    //while (guess * guess != x)
    while (abs((guess * guess - x)/ guess )> 1e-6)
    {
        if (guess * guess > x)
            xhi = guess;
        else
            xlo = guess;

        double new_guess = (xhi + xlo) / 2;
        //if (new_guess == guess)
        //  break; // not getting closer
        guess = new_guess;
    }
    return guess; 
}

double newtonsqrt(int x, int n) {
    assert(x >= 0);
    if (x == 0)
    return 0;

    double guess = x;
    for (int i=0; i < n; i++) {
        guess -= (guess*guess-x)/(2*guess);
        //cout << guess << endl;
        if (abs(guess - x ) < 1e-6) {
            //incout << abs(guess - x ) << endl;
            break;
        }
    }
    return guess;
}



int main() {
    cout << "square root of 101 is " << squareroot(101.0) << endl;
    cout << "square root of 298 is " << squareroot(298.0) << endl;

    cout << "square root of 101 is " << newtonsqrt(101.0, 50) << endl;
    cout << "square root of 298 is " << newtonsqrt(298.0, 50) << endl;
}
