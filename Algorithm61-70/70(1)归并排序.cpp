//
// Created by zhouyxuiang on 2026/4/14.
//
//复杂度O(nlogn)
//左边排序右边排序再merge总体有序
#include <iostream>
using namespace std;
// 合并两个有序区间：[l, mid] 和 [mid+1, r]
void merge(vector<int> &arr, int l, int mid,int r) {
    vector<int> temp;
    int i = l;//左边区域起点
    int j = mid + 1;//右边区域起点
    while (i <= mid && j <= r) {
        if (arr[i] < arr[j]) {
            temp.push_back(arr[i]);
            i++;
        }else {
            temp.push_back(arr[j]);
            j++;
        }

    }
    while (i <= mid) {
        temp.push_back(arr[i]);
        i--;
    }
    while (j <= r) {
        temp.push_back(arr[j]);
        j++;
    }
    for (int k = 0;k < temp.size(); k++) {
        arr[l + k] = temp[k];
    }
}
//merge的过程就是左右数组整合到一起
//左边一个指针右边一个指针
//谁小复制谁
void mergeSort(vector<int>& arr, int l, int r) {
    if (l >= r) return;//只有一个数不排序
    int mid = (l + r) / 2;
    mergeSort(arr, l, mid);
    mergeSort(arr, mid + 1, r);
    merge(arr, l, mid, r);//合并左右
}
//非递归版本的归并排序
//步长 =0,1,2,4,8,16...
