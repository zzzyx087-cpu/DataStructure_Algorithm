//
// Created by zhouyxuiang on 2026/4/14.
//
#include <iostream>
using namespace std;
//归并分治 给一个数组实现小和
//等于左侧答案加右侧答案和左跨右答案
//拆分成左半部分 右半部分
//因为是在拆分的时候就算了左右数组内部的贡献
//递归算出左半部分的小和
//再算出右边部分小和
int merge(vector<int> &arr, int l, int mid, int r) {
    vector<int> temp;
    int i = l;
    int j = mid + 1;
    int res = 0;
    while (i <= mid && j <= r) {
        if (arr[i] <= arr[j]) {
            res += arr[i] * (r - j + 1);//还要乘上个数
            //左右两边已经排好序了
        }else {
            temp.push_back(arr[j++]);
        }
    }
    while (i <= mid) temp.push_back(arr[i++]);
    while (j <= r) temp.push_back(arr[j++]);

    for (int k = 0; k < temp.size(); k++) {
        arr[l + k] = temp[k];
    }

    return res;
}
int mergeSort(vector<int>& arr, int l, int r) {
    if (l >= r) return 0;

    int mid = (l + r) / 2;
    int leftSum = mergeSort(arr, l, mid);
    int rightSum = mergeSort(arr, mid + 1, r);
    int mergeSum = merge(arr, l, mid, r);

    return leftSum + rightSum + mergeSum;
}