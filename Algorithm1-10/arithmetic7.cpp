//
// Created by zhouyxuiang on 2026/3/4.
//
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 定义边界极值：处理切分点在数组两端的情况（比如i=0时nums1左边无元素）
#define INI_MIN -2147483648  // int类型最小值
#define INI_MAX 2147483647   // int类型最大值

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size();  // 数组1长度
        int n = nums2.size();  // 数组2长度

        // 核心优化：始终在较短的数组上做二分（减少循环次数）
        // 如果nums1更长，交换两个数组，保证m ≤ n
        if (m > n) {
            return findMedianSortedArrays(nums2, nums1);
        }

        // 二分查找的边界：i的取值范围是0~m（0=数组1全在右边，m=数组1全在左边）
        int left = 0;
        int right = m;

        // 二分查找主循环：找正确的切分点i
        while (left <= right) {
            // 1. 计算当前nums1的切分点i（二分中间值）
            int i = (left + right) / 2;
            // 2. 计算nums2的切分点j：保证左右长度平衡（left_total = right_total 或 right_total+1）
            int j = (m + n + 1) / 2 - i;

            // 3. 处理边界：获取四个关键值（切分点左右的元素）
            // left1 = nums1左边最后一个元素；i=0时左边无元素，用极小值
            int left1 = (i == 0) ? INI_MIN : nums1[i - 1];
            // right1 = nums1右边第一个元素；i=m时右边无元素，用极大值
            int right1 = (i == m) ? INI_MAX : nums1[i];
            // left2 = nums2左边最后一个元素；j=0时左边无元素，用极小值
            int left2 = (j == 0) ? INI_MIN : nums2[j - 1];
            // right2 = nums2右边第一个元素；j=n时右边无元素，用极大值
            int right2 = (j == n) ? INI_MAX : nums2[j];

            // 4. 验证切分点是否正确：左边所有元素 ≤ 右边所有元素
            if (left1 <= right2 && left2 <= right1) {
                // 找到正确切分点，计算中位数
                if ((m + n) % 2 == 1) {
                    // 总长度奇数：中位数=左边最大值（因为左边多1个）
                    return max(left1, left2);
                } else {
                    // 总长度偶数：中位数=（左边最大值 + 右边最小值）/2
                    return (max(left1, left2) + min(right1, right2)) / 2.0;
                }
            } else if (left1 > right2) {
                // 5. 切分点偏右：nums1左边元素太大，需要把i往左移
                right = i - 1;
            } else {
                // 6. 切分点偏左：nums2左边元素太大，需要把i往右移
                left = i + 1;
            }
        }
        // 理论上不会执行到这里（输入是有序数组，一定能找到切分点）
        return 0.0;
    }
};

// 测试代码：验证逻辑正确性
int main() {
    Solution obj;
    vector<int> nums1 = {1, 2, 4, 6, 7};
    vector<int> nums2 = {3, 4, 5, 6};
    // 合并后数组：[1,2,3,4,4,5,6,6,7] → 中位数是4
    cout << obj.findMedianSortedArrays(nums1, nums2) << endl; // 输出4
    return 0;
}