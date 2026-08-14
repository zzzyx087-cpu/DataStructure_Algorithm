//
// Created by zhouyxuiang on 2026/3/15.
//
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 基数排序（只排非负整数）
void radixSort(vector<int>& v) {
    if (v.empty()) return;

    // 1. 找到最大值，确定要排到第几位数
    int maxVal = *max_element(v.begin(), v.end());

    // 2. 辅助数组（存每一位排序后的结果）
    vector<int> temp(v.size());

    // 3. 按每一位排序：个位、十位、百位...
    for (int exp = 1; maxVal / exp > 0; exp *= 10) {
        int count[10] = { 0 }; // 0~9 计数

        // 统计当前位每个数字出现次数
        for (int num : v) {
            int digit = (num / exp) % 10;
            count[digit]++;
        }

        // 变成前缀和，确定位置
        for (int i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }

        // 从后往前遍历，放入辅助数组（保证稳定）
        for (int i = v.size() - 1; i >= 0; i--) {
            int digit = (v[i] / exp) % 10;
            temp[--count[digit]] = v[i];
        }

        // 把排好的结果复制回原数组
        for (int i = 0; i < v.size(); i++) {
            v[i] = temp[i];
        }
    }
}
int maxbits(vector<int> v) {
    int max = *min_element(v.begin(), v.end());
    int res = 0;
    for (int i = 0; i < v.size(); i++) {
        max = max > v[i] ? max : v[i];
    }
    while (max != 0) {
        res ++;
        max/=10;
    }
    return res;
}
int getDigit(int num,int digit) {
    int div = 1;
    for (int i = 1; i < digit; i++) {
        div *= 10;
    }
    return (num / div)%10;
}
void radixSrt(vector<int>& v , int L , int R , int digit) {
    const int radix = 10;
    int i = 0, j = 0;
    vector<int> vec(R - L + 1);
    //进桶出桶次数是digit次
    for (int d = 1;d <= digit; d++) {//有多少位出多少次
        vector<int>count(radix,0);

        for (i = L; i <= R; i++) {
            j = getDigit(v[i] , d);
            count[j]++;
        }
        for (i = 1; i < radix; i++) {
            count[i] = count[i] + count[i-1];
        }
        for (i = R; i >= L; i--) {
            j = getDigit(v[i] , d);
            vec[count[j] - 1] = v[i];
            count[j]--;
        }
        for ( i = L; i <= R; i++) {
            v[i] = vec[i];
        }
    }
}
// 测试
int main() {
    vector<int> v = { 32, 1, 15, 22, 7, 100, 5 };

    radixSrt(v , 0, v.size() - 1, 3);

    cout << "排序后：";
    for (int num : v) {
        cout << num << " ";
    }
    return 0;
}