//
// Created by zhouyxuiang on 2026/3/13.
//
#include<iostream>
using namespace std;
int gcd(int a, int b) {
    return b ? gcd(b , a % b) : a;
}
int gcd2(int a, int b) {
    if (b == 0) return a;
    return gcd2(b, a % b);
}
int main() {
    int count = 0;
    for (int i = 1; i <= 2020; i++) {
        for (int j = 1; j <= 2020; j++) {
            if (gcd(i,j) == 1) {
                count++;
            }
        }
    }
    cout << count << endl;
    return 0;
}