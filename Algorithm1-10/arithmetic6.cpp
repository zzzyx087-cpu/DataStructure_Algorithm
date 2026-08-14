//
// Created by zhouyxuiang on 2026/3/4.
//
#include <iostream>
using namespace std;
bool NoRepetition(string s) {
    for (int i = 0; i <= s.length(); i++) {
        for (int j = i + 1; j <= s.length(); j++) {
            if (s[i] == s[j]) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    cout <<"请输入一串字符串" << endl;
    string s;
    cin >> s;
    string max;

    for (int  i = 0; i < s.length(); i++) {
        for (int j = i + 1; j <= s.length(); j++) {
            string s2 = s.substr(i, j - i);
             if (NoRepetition(s2) && s2.length() > max.length()) {
                max = s2;
            }
        }
    }
    cout << max.size() << endl;
    return 0;
}