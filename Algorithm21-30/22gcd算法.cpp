//
// Created by zhouyxuiang on 2026/3/12.
//
#include <iostream>
#include <algorithm>
using namespace std;
int gcd(int a, int b) {
    return b != 0 ? gcd(b, a % b) : a;
}
int gcdMany(vector<int> &a , int n) {
    n = a.size();
    int result = a.at(0);
    for (int i = 1; i < n; i++) {
        result = gcd(a.at(i), result);
    }
    return result;
}

int main () {
    // cout << gcd(17,19) << endl;
    // cout << gcd(48,36) << endl;
    // vector<int> a;
    // a.push_back(64);
    // a.push_back(32);
    // a.push_back(16);
    // cout <<  gcdMany(a , 3) << endl;
    for (int i = 12; i <= 84; i++) {
        for (int j = 84; j >= 12; j--) {
            if (gcd(i,j)== 12 && i + j == 84 ) {
                cout << i << ',' << j << endl;
            }
        }

    }
    return 0;
}