//
// Created by zhouyxuiang on 2026/3/12.
//
//时间复杂度o(log2 N)
#include <iostream>
#include <vector>
using namespace std;
int binarySearch(vector<int> v , int Target) {
    int n = int(v.size());
    int left = 0;
    int right = n - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (v[mid] == Target) {
            return mid;
        }else if (v[mid] > Target) {
            right = mid - 1;
        }else {
            left = mid + 1;
        }
    }
    return -1;
}
int main () {
    vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(3);
    v.push_back(4);
    v.push_back(4);
    v.push_back(4);
    v.push_back(5);
    cout << binarySearch(v , 3);
    return 0;
}