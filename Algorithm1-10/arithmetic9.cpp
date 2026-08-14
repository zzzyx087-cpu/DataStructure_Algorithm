//
// Created by zhouyxuiang on 2026/3/7.
//
#include<iostream>
#include<string>
#include<vector>
using namespace std;
class Solution {
public:
    string convert(string s, int numRows) {
        if (numRows == 1) return s;
        vector<string> rows(numRows);//一个动态字符串数组 每一行对应一个字符串
        int i = 0;          //把字符串放到第几行
        int offset = -1;    //行数变化的步长
        for (char ch : s) {
            rows[i] += ch;
            if (i == 0 || i == numRows - 1) {
                offset = -offset;
            }
            i += offset;
        }
        string ans;
        for (auto& s : rows) {
            ans += s;
        }
        return ans;
    }
};
int main() {
    string s;
    cin >> s;
    Solution obj;
    cout << obj.convert(s,3);
    return 0;
}