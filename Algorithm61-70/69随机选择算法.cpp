//
// Created by zhouyxuiang on 2026/4/14.
//
#include <iostream>
using namespace std;

//无序数组中寻找第K大的数 给定num 和 k返回数组中第K大的元素
//时间复杂度为O（n）
//不关心下标只关心值 不能用排序

//思路基于u快速排序的分治思想 选择pivot对数组进行划分
//三向切分函数
pair<int,int> partition(vector<int> &arr,int l,int r, int pivotIdx) {
    int pivot = arr[pivotIdx];//选一个基准数
    swap(arr[l],arr[pivotIdx]);
    int lt = l,gt = r,i = l + 1;
    //lt表示比pivot小的数字 gt表示大于pivot的数字
    while (i <= gt) {
        if (arr[i] < pivot) {
            swap(arr[i],arr[lt]);
            lt++;
            i++;
        }else if (arr[i] > pivot) {
            swap(arr[i], arr[gt]);
            gt--;
        } else {
            i++;
        }
    }
    return {lt, gt};//等于基准值的起点和终点
}
//随机找第i小的数
int randomizedSelect(vector<int>& arr, int i) {
    int n = arr.size();
    int l = 0, r = n - 1;
    while (l <= r) {
        int pivotIdx = l + rand() % (r - l + 1);
        int first = partition(arr, l, r, pivotIdx).first;
        int last = partition(arr, l, r, pivotIdx).second;

        if (i < first) {
            r = first - 1;
        } else if (i > last) {
            l = last + 1;
        } else {
            return arr[i];
        }
    }
    return -1;
}
int findKthLargest(vector<int>& nums, int k) {
    return randomizedSelect(nums, nums.size() - k);
}


