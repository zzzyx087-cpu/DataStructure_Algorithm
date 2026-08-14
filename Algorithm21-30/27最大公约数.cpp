//
// Created by zhouyxuiang on 2026/3/13.
//
#include <iostream>
using namespace std;
//给定一个数组，每次操作可以选择数组中任意两个相邻的元素 x, y
//并将其中的一个元素替换为 gcd(x, y) ，其中 gcd(x, y) 表示 x 和 y 的最大公约数。
//请问最少需要多少次操作才能让整个数组只含 1 。
int gcd(int a , int b) {
    return b ? gcd(b , a % b) : a;
}
int main() {
    cout << gcd(10, 18) << endl;
    return 0;
}