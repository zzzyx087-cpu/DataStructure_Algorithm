//
// Created by zhouyxuiang on 2026/3/11.
//
#include <iostream>
using namespace std;
//递归思想
class Solution {
    public:
    int jumpfloor(int number) {
        if (number == 0 || number == 1) {
            return 1;
        }
        return jumpfloor(number - 1) + jumpfloor(number - 2);
    }
};
int main() {
    Solution s;
    cout << s.jumpfloor(4) << endl;
    return 0;
}