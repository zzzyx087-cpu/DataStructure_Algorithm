//
// Created by zhouyxuiang on 2026/3/12.
//
#include<iostream>
using namespace std;
//大数运算
string HihgAdd(string s1 , string s2) {
    int carry = 0;//判断是否进位
    string res = "";
    //先从个位开始
    int i = s1.length() - 1;
    int j = s2.length() - 1;
    while (i >= 0 || j >= 0 || carry > 0) {
        int digit1 =(i >= 0) ? (s1[i] - '0'): 0;
        int digit2 =(j >= 0) ? (s2[j] - '0'): 0;
        int sum = digit1 + digit2 + carry;
        res.push_back(sum % 10 + '0');
        carry = sum / 10;
        i--;
        j--;
    }
    reverse(res.begin(), res.end());
    return res;
}
int main() {
    cout << HihgAdd("19934134", "13141412412413") << endl;
    return 0;
}