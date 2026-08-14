//
// Created by zhouyxuiang on 2026/3/16.
//
#include <iostream>
#include <vector>
using namespace std;

// 交换两个数
void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// 快速排序主函数
void quickSort(vector<int>& v, int L, int R) {
    if (L >= R) return; // 递归终止条件
    int i = L;
    int j = R;
    int mid = L + (R - L) / 2;
    int p = v[mid];
    while (i <= j) {
        while (v[i] < p) i++;
        while (v[j] > p) j--;
        if (i <= j) {
            swap(v[i], v[j]);
            i++;
            j--;
        }
    }
    quickSort(v, L, j);
    quickSort(v, i, R);
}

// 测试
int main() {
    vector<int> v = {31, 77, 22, 15, 19, 35};

    quickSort(v, 0, v.size() - 1);

    cout << "排序结果：";
    for (int num : v) {
        cout << num << " ";
    }
    return 0;
}