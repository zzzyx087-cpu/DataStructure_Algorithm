//
// Created by zhouyxuiang on 2026/3/13.
//
#include <iostream>
using namespace std;
//学习快速幂
//快速计算 a 的 b次方 数字可能会很大
//普通方法时间复杂度O(b) 会超时

//快速幂方法 时间复杂度O(log b)
//核心思想 二进制分解
//例如3的13次方 13 = 1101 = 8 + 4 + 1
//3^13 = 3 ^ 8 * 3 ^ 4 * 3 ^ 1
long long quick_pow(long long a, long long b) {
    long long res = 1;      // 结果
    long long base = a;     // 当前位的值：a^1, a^2, a^4, a^8...

    while (b > 0) {
        // 如果当前二进制位是1，就乘到结果里
        if (b % 2 == 1) {        // 判断最低位是不是1
            res = res * base;
        }

        // base 自乘，准备下一位：a^1 → a^2 → a^4 → a^8
        base = base * base;

        // b 右移一位，处理下一位
        b = b / 2;            // 去掉最低位
    }

    return res;
}
//如果数字很大 进行取模操作
long long quick_Pow_mod(long long a, long long b , long long mod) {
    long long res = 1;      // 结果
    long long base = a;     // 当前位的值：a^1, a^2, a^4, a^8...

    while (b > 0) {
        // 如果当前二进制位是1，就乘到结果里
        if (b % 2 == 1) {        // 判断最低位是不是1
            res = (res * base) % mod;
        }
        // base 自乘，准备下一位：a^1 → a^2 → a^4 → a^8
        base = (base * base) % mod;
        // b 右移一位，处理下一位
        b = b / 2;// 去掉最低位
    }
    return res;
}

int main () {
    cout << quick_pow(10, 5) << endl;
    int result = quick_Pow_mod(2, 10, 1000);
    printf("%0*lld", 3, result);
    return 0;
}