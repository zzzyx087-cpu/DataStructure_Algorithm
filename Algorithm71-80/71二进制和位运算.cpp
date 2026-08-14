//
// Created by zhouyxuiang on 2026/4/14.
//
#include <iostream>
using namespace std;
//-7 1001 -8 1000 -1 1111 -2 1110
//减1取反 有符号数____-7 ~ 8
void printBinary(int num) {
    cout << bitset<32>(num) << endl;
}
void swap1();
int main () {
    int a = 78;
    cout << a << endl;
    printBinary(a);
    cout << "===a===" << endl;

    // b = -6
    int b = -6;
    cout << b << endl;
    printBinary(b);
    cout << "===b===" << endl;

    // Direct binary literal definition (C++14+)
    int c = 0b1001110;
    cout << c << endl;
    printBinary(c);
    cout << "===c===" << endl;

    // Direct hexadecimal literal definition
    int d = 0x4e;
    cout << d << endl;
    printBinary(d);
    cout << "===d===" << endl;

    // ~ operator (bitwise NOT) and negative number conversion
    cout << a << endl;
    printBinary(a);
    printBinary(~a);
    int e = ~a + 1;
    cout << e << endl;
    printBinary(e);
    //常见的位运算
    //|或运算
    printBinary(a | e);
    //&运算
    printBinary(a & e);
    //^异或运算
    printBinary(a ^ e);
    //左移和右移
    printBinary(12 << 1);//不够拿0补
    printBinary(12 >> 3);//左边拿0补
    //对于负数就不一样
    int j = -222;
    printBinary(j);
    printBinary(j >> 2);
    cout<< "------------------------" << endl;
    //异或的操作
    //(n << shift_amount) & 0xFFFFFFFF
    //异或就是无进位相加 0 ^ n = n,n ^ n = 0
    //01101110 ^ 10011101
    //=11110011 满足结合律交换律
    swap1();

}
int flip(int n) {
    return n ^ 1;
}
//1.交换两个数
void swap1(){
        int z = 123;
        int j = -222;
        z = z ^ j;
        j = z ^ j;
        z = j ^ z;
    cout << z << endl;
    cout << j << endl;
    }
//2.不用任何比较操作返回两个数的最大值
//非负返回1负数返回0
int sign(int n) {
    int shift = n>> 31;
    return (~shift) & 1;
}
//3.其他数字出现大于等于m次 在0不增长 1要增长
//[0110,1100,1001]
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        // 本题 m = 3，调用通用函数
        return find(nums, 3);
    }//告诉 find 函数：其他数字都出现 3 次

    // 通用解法：已知数组中只有1个数出现少于m次，其余都出现m次
    // 返回那个唯一的数
    int find(vector<int>& arr, int m) {
        int cnts[32] = {0}; // 统计32位整数中，每一位上1的个数

        // 1. 统计所有数字的位分布
        for (int num : arr) {
            for (int i = 0; i < 32; i++) {
                // 将num右移i位，与1做与运算，得到第i位是否为1
                cnts[i] += (num >> i) & 1;
            }
        }
        //第一段：定义数组，统计每一位 1 出现多少次

        int res = 0;
        // 2. 还原结果：对每一位取模 m
        for (int i = 0; i < 32; i++) {
            // 如果这一位的总数不能被 m 整除，说明唯一的数在这一位是 1
            if (cnts[i] % m != 0) {
                res |= (1 << i); // 将这一位设为1 只要有1就是1
            }
        }

        return res;
    }
};

