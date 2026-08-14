//
// Created by zhouyxuiang on 2026/3/7.
//
#include <iostream>
using namespace std;
class Solution {
public:
    int reverse(int x) {
        int res = 0;
        while (x != 0) {
            int pop = x % 10; // 取出最后一位
            x /= 10;          // 去掉最后一位

            // 检查正溢出：res > INT_MAX/10 时，res*10 必溢出
            if (res > INT_MAX / 10 || (res == INT_MAX / 10 && pop > 7)) {
                return 0;
            }
            // 检查负溢出：res < INT_MIN/10 时，res*10 必溢出
            if (res < INT_MIN / 10 || (res == INT_MIN / 10 && pop < -8)) {
                return 0;
            }

            res = res * 10 + pop; // 构建反转后的数字
        }
        return res;
    }

};
int main () {
    int x;
    cout << "请输入一串字符串"<< endl;
    cin >> x;
    Solution obj;
    cout << obj.reverse(x) << endl;

    return 0;
}