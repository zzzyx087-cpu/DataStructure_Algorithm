//
// Created by zhouyxuiang on 2026/3/12.
//
#include<iostream>
using namespace std;

int month[] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };

bool is_leapyear(int y) {
    return ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0);
}

int main() {
    int a, b, c;
    scanf("%d/%d/%d", &a, &b, &c);
    for (int y = 1960; y <= 2059; y++) {
        if (is_leapyear(y)) month[2] = 29;
        else month[2]=28;
        for (int m = 1; m <= 12; m++) {
            for (int d = 1; d <= month[m]; d++) {
                if ((a == y % 100 && b == m && c == d) ||
                    (a == m && b == d && c == y % 100) ||
                    (a == d && b == m && c == y % 100))
                    printf("%d-%02d-%02d\n", y, m, d);
            }
        }
    }
    return 0;
}