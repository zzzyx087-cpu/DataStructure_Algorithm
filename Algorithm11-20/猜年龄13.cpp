//
// Created by zhouyxuiang on 2026/3/10.
//
#include <iostream>
using namespace std;
int main() {
    for (int i = 10; i < 30; i++) {
        for (int j = 10; j < 30; j++) {
            if (i < j && i * j == (i + j) * 6 && (j-i) <= 8) {
                cout << i << " " << j <<endl;
            }
        }
    }

    return 0;
}