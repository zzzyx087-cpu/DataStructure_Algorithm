//
// Created by zhouyxuiang on 2026/3/13.
//
#include <iostream>

using namespace std;
long long quick_Pow(long long x, long long y) {
    long long res = 1;
    while (y > 0) {
        if (y % 2 == 1) res = res * x;
        x = x * x;
        y = y / 2;
    }
    return res;
}
int main() {
    long long pow20  = quick_Pow(2, 20);
    long long pow19 =  quick_Pow(2, 19);
    long long numerator = pow20 - 1;
    long long denominator = pow19;
    cout << numerator << "/" << denominator << endl;
    return 0;
}