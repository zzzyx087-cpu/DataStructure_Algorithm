//
// Created by zhouyxuiang on 2026/4/16.
//
#include <iostream>
using namespace std;
int binarySearch(int nums[], int n, int target) {//需要数组有顺序
    int l = 0;
    int r = n - 1;

    while (l <= r) {
        int mid = l + (r - l) / 2; // 防止溢出

        if (nums[mid] == target) {
            return mid; // 找到了
        } else if (nums[mid] < target) {
            l = mid + 1; // 目标在右边
        } else {
            r = mid - 1; // 目标在左边
        }
    }

    return -1; // 没找到
}
//右侧小于等于menmber的最右位置
int findeRight(vector<int> arr , int num) {
    int l = 0, r = arr.size() - 1,m = 0;
    int ans = -1;
    while (l <= r) {
        m = l + (r - l) / 2;
        if (arr[m] <= num) {
            ans = m;
            l = m + 1;
        }else {
            r = m - 1;
        }

    }
    return ans;
}

//不一定发生在有序数组上
//峰值表示比临近的两个位置大
//假设-1和N位置是无穷小的数字
//每个数字都不想等
int findPeakelemnt(vector<int> arr) {
    if (arr.size() == 0) {
        return 1;
    }
    int n = arr.size();
    //数组长度大于等于2
    //且相邻两个数不相等
    if (arr[0] > arr[1]) return 0;
    if (arr[n-1] > arr[n-2]) return n - 1;
    //说明中间一定有峰值点
    int l = 1,r = n -2 , m = 0,ans = -1;
    while (l <= r) {
        m = l + (r - l) / 2;
        if (arr[m-1] > arr[m]) {
            //m是中点 说明左侧存在峰值
            r = m - 1;
        }else if (arr[m] < arr[m + 1]) {
            l = m + 1;
        }else {//说明ans就是峰值
            ans = m;
            break;
        }
    }
    return ans;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

}