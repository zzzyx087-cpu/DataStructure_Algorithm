//
// Created by zhouyxuiang on 2026/4/15.
#include <iostream>
using namespace std;
bool isPowerThree(int n) {
    return n > 0 && 1162261467 % n == 0;
}
//判断是不是2的幂
bool isPowerTwo(int n) {
    return n > 0 && n == (n & -n);
}
//让一个数字到达最近的2的幂次位
int Near2Power(int n) {
    if (n <= 0) {
        return 1;
    }
    n--;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    return n + 1;
}
//求区间[l,r]的所有结果&起来
int AllAnd(int l , int right) {
    while (l < right) {
        right -= right & -right;
    }
    return right;
}
//反转一个数字
//比如00111010到01011100
//不用循环做
int reverseBits(int n) {
    //1v1交换
    //2v2交换
    //4v4交换
    n = ((n & 0xaaaaaaaa) >> 1 | (n & 0x55555555) << 1);
    n = ((n & 0xcccccccc) >> 2 | (n & 0x33333333)<<2);
    n = ((n & 0xf0f0f0f0) >> 4 | (n & 0x0f0f0f0f)<<2);
    n = ((n & 0xff00ff00) >> 8 | (n & 0x00ff00ff)<<8);
    n = (n >> 16) | (n << 16);
    return n;
}
//返回数字中有几个1
int Many1(int n) {


}

