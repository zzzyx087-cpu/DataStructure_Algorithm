//
// Created by zhouyxuiang on 2026/3/4.
//
#include <iostream>
using namespace std;
bool isPrime (int x) {
    if (x <= 1) return false;       // 1及以下不是质数
    if (x == 2) return true;        // 2是唯一的偶质数
    if (x % 2 == 0) return false;   // 偶数（除2外）都不是质数
    for (int i = 3; i * i <= x; i += 2) { // 只检查到sqrt(x)，且只检查奇数
        if (x % i == 0) {
            return false;
        }
    }
    return true;
}
int main() {
    int x;
    cin >> x;
    int sum = 0;
    for (int i = 1; i <= x; i++) {
        if (isPrime(i)) {
            sum += i;
        }
    }
    cout << sum << endl;
}