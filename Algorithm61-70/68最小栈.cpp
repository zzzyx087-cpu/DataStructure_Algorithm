//
// Created by zhouyxuiang on 2026/4/14.
//
#include <iostream>
using namespace std;
class MinStack {
    private:
    stack<int> data;// 主栈，存所有数据
    stack<int> minSt;  // 辅助栈，存当前的最小值
    public:
    MinStack() {
        // 构造函数，栈默认初始化，无需额外代码
    }
    void push(int val) {
        data.push(val);
        // 关键：如果辅助栈为空 或 新值小于等于当前最小值，才压入
        if (minSt.empty() || val <= minSt.top()) {
            minSt.push(val);
        }
    }
    void pop() {
        // 防止主栈空报错
        if (data.empty()) return;

        int val = data.top();
        data.pop();

        // 关键：如果弹出的值是当前最小值，辅助栈也得弹
        if (val == minSt.top()) {
            minSt.pop();
        }
    }
    int top() {
        // 题目保证操作合法，直接取顶
        return data.top();
    }

    int getMin() {
        // 题目保证操作合法，直接取辅助栈顶
        return minSt.top();
    }
};