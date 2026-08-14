//
// Created by zhouyxuiang on 2026/3/10.
//
#include <iostream>
#include <string>
//统计1-2020 2出现的次数

using namespace std;
int main() {
    int count = 0;
    for (int i = 0; i < 2021; i++) {
        string s = to_string(i);
        for (int j = 0; j < s.length(); j++) {
            if (s[j] == '2') count++;
        }
    }
    cout << count << endl;
    return 0;
}