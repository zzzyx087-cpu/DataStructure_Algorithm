//
// Created by zhouyxuiang on 2026/3/1.
//
#include <iostream>
using namespace std;
int main () {
    int target;
    cout << "请输入target" << endl;
    cin >> target;
    int n;
    cout << "请输入数组的个数" << endl;
    cin >> n;
    int arr[n];

    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    //暴力法
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] + arr[j] == target) {
                cout<< i << " " << j << endl;
            }
        }
    }
    return 0;
}