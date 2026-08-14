//
// Created by zhouyxuiang on 2026/3/12.
//
#include<iostream>
using namespace std;
//插入排序
void InsertSort(vector<int> &v) {
    for (int i = 1; i < v.size(); i++) {//让0到i有序
        for (int j = i - 1;j >= 0 && v[j] > v[j + 1] ; j--) {
            int t = v[j];
            v[j] = v[j + 1];
            v[j + 1] = t;
        }
    }
}
int main() {
    vector<int> v;
    v.push_back(5);
    v.push_back(3);
    v.push_back(2);
    v.push_back(1);
    v.push_back(0);
    v.push_back(6);
    InsertSort(v);
    for_each(v.begin(), v.end(),[](int i){cout << i << " ";});
    return 0;
}