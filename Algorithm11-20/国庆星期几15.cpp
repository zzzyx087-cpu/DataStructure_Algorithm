//
// Created by zhouyxuiang on 2026/3/10.
//
#include <iostream>

using namespace std;
//1949年10月1日为周六 到2012年 国庆节是周一
//输出 哪几次正好是周日 次数
int main () {
    //如果是平年就是推一天 闰年推两天
    int week = 6;
    int count = 0;
    int yu1 = 365 % 7;
    int yu2 = 366 % 7;
    for (int i = 1950 ; i <= 2012 ; ++i) {
        if (i % 4 == 0 || i % 400 == 0) {
            week = (week + yu2) % 7;
            if (week % 7 == 0) {
                count ++;
            }
        }else {
            week = (yu1 + week) % 7;
            if (week % 7 == 0) {
                count ++;
            }
        }
    }
    cout << count << endl;
    return 0;
}