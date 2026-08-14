//
// Created by zhouyxuiang on 2026/3/20.
//
#include <iostream>
using namespace std;
int main() {
    //& 按位与
    //规则：两位都是 1，结果才是 1
   //1 & 1 = 1
   //1 & 0 = 0
   //0 & 1 = 0
   //0 & 0 = 0
    cout << (1 & 1) << endl;
   //|按位或
   //有1就为1
   //1 | 1 = 1
   //1 | 0 = 1
   //0 | 1 = 1
   //0 | 0 = 0
    cout << (1 | 2) << endl; //转化为2禁止01 和 10
    //^ 按位异或
    //规则：相同为 0，不同为 1
    cout << (1 ^ 2) << endl;

    // ～ 按位取反
    cout << ~0 << endl; //-1
    cout << ~4 << endl; //-5
    cout << ~3 << endl; //-4
     //~x  =  -(x + 1)
     //<<左移
     cout << (1<<2) << endl; //1*2的2次方
     cout << (3<<3) << endl; //3*2的3次方

    //>>右移
    cout << (8 >> 1) << endl; //除以2的1次方
    cout << (8 >> 2) << endl; //除以2的2次方


}