//
// Created by zhouyxuiang on 2026/2/24.
//
#include <iostream>
using namespace std;
int main() {
    // 1. 输入雪地用品数量A和温泉用品数量B
    int A, B;
    cout << "请输入雪地用品数量A: ";
    cin >> A;
    cout << "请输入温泉用品数量B: ";
    cin >> B;

    // 2. 计算核心参数
    int S = A + B;                  // 总装配数 = 雪地用品数 + 温泉用品数
    int max_x = min(A, B);          // x的取值上限（不能超过A或B）
    int min_abs_diff = INT_MAX;     // 初始化最小差值为整数最大值（表示无穷大）

    // 3. 遍历所有合法的x值，找到最小差值
    for (int x = 0; x <= max_x; x++) {
        // 计算当前x对应的差值 |4x - S|
        int current_diff = abs(4 * x - S);
        // 更新最小差值
        if (current_diff < min_abs_diff) {
            min_abs_diff = current_diff;
        }
    }

    // 4. 输出结果
    cout << "合理装配与幽默装配数量的最小差值为: " << min_abs_diff << endl;
}