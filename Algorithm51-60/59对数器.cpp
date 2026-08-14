//
// Created by zhouyxuiang on 2026/3/24.
//
#include <iostream>
#include <vector>
#include <algorithm>  // 系统自带排序（当作正确答案）
#include <cstdlib>
#include <ctime>
using namespace std;

// ===================== 1. 你要测试的算法（比如你写的排序）=====================
void mySort(vector<int>& arr) {
    // 这里放你写的代码
    // 比如你自己写的冒泡、快排、贪心……
    sort(arr.begin(), arr.end()); // 先假装是你写的
}

// ===================== 2. 绝对正确的暴力方法（标准答案）=====================
void rightMethod(vector<int>& arr) {
    // 用系统排序，绝对正确
    sort(arr.begin(), arr.end());
}

// ===================== 3. 随机数组生成器（对数器核心）=====================
vector<int> generateRandomArray(int maxSize, int maxValue) {
    // 随机长度 [0, maxSize]
    int n = rand() % (maxSize + 1);
    vector<int> arr(n);

    for (int i = 0; i < n; i++) {
        // 随机值 [-maxValue, maxValue]
        arr[i] = rand() % (maxValue + 1) - rand() % maxValue;
    }
    return arr;
}

// ===================== 4. 对比两个数组是否一样 =====================
bool isEqual(vector<int>& a, vector<int>& b) {
    return a == b;
}

// ===================== 对数器主函数 =====================
int main() {
    srand((unsigned)time(NULL)); // 随机种子

    int testTime = 50000; // 测试 5 万组数据
    int maxSize = 100;    // 数组最大长度
    int maxValue = 100;   // 数组最大值
    bool success = true;

    for (int i = 0; i < testTime; i++) {
        // 生成随机数组
        vector<int> arr1 = generateRandomArray(maxSize, maxValue);
        vector<int> arr2 = arr1; // 拷贝一份

        // 分别用两种方法排序
        mySort(arr1);     // 你的方法
        rightMethod(arr2); // 标准答案

        // 对比结果
        if (!isEqual(arr1, arr2)) {
            success = false;

            // 打印出错的数据
            cout << "出错啦！数据：";
            for (int num : arr2) cout << num << " ";
            cout << endl;
            break;
        }
    }

    if (success) {
        cout << "✅ " << testTime << " 组测试全通过！你的代码是对的！" << endl;
    } else {
        cout << "❌ 你的代码错了！" << endl;
    }

    return 0;
}