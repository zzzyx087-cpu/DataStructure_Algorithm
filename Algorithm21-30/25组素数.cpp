//
// Created by zhouyxuiang on 2026/3/13.
//
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
bool isPrime(int x) {
    if (x <= 1) return false;
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) return false;
    }
    return true;
}
int main () {
    int count = 0;
    vector<int> digits;
    digits.push_back(1);
    digits.push_back(9);
    digits.push_back(9);
    digits.push_back(4);
    sort(digits.begin(), digits.end());
    int num = digits[0] * 1000 + digits[1] * 100 + digits[2] * 10 + digits[3];
    if (isPrime(num)) count++;
    while (next_permutation(digits.begin(), digits.end())) {
        num = digits[0] * 1000 + digits[1] * 100 + digits[2] * 10 + digits[3];
        if (isPrime(num)) count++;
    }
    cout << count << endl;
    return 0;
}