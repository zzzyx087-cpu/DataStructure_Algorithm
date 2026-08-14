//
// Created by zhouyxuiang on 2026/3/10.
//
#include<iostream>
using namespace std;
bool isunique(long long n1,long long n2) {
    string s = to_string(n1) + to_string(n2);
    if (s.length() != 10) return false;
    sort(s.begin(), s.end());
    for (int i=0 ; i < s.length() ; i++) {
        if (s[i] != '0' + i)return false;
    }
    return true;
}
int main() {
    for (int i = 10 ; i < 30 ; i++) {
        long long cube = i * i * i;
        long long fourth    = i * i * i * i;
        if (cube > 1000 && cube < 10000 && fourth > 100000 && fourth < 1000000) {
            if (isunique(cube, fourth)) {
                cout << i << endl;
            }
        }
    }
    return 0;
}