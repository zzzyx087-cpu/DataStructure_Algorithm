//
// Created by zhouyxuiang on 2026/3/27.
//
#include <iostream>
#include <algorithm>
using namespace std;
//从1~n n个数字随机任意取多个 输出所有可能的选择方案
//所有的方案数量就是 2 ^ n
//输入3
//输出
//3
//2
//23
//1
//12
//123
const int N = 20;
int n;
int st[N];//记录每个数字的状态 0表示没有考虑 1表示选择这个数 2表示不选择这个数
void dfs1(int x) {//x表示当前枚举到的位置
    if (x > n) {
        for (int i = 1; i <= n; i++) {
            if (st[i] == 1) {
                cout << i << " ";
            }
        }
        cout << endl;
        return;
    }
    //第一种情况 选择
    st[x] = 1;
    dfs1(x + 1);
    st[x] = 0; //恢复现场
    //第二种情况
    st[x] = 2;
    dfs1(x + 1);
    st[x] = 0; //恢复现场

}
//第二道题 输入3
//输出
//1 2 3
//1 3 2
//2 1 3
//2 3 1
//3 1 2
//3 2 1
//即n的全排列
//字典序
bool st2[N];
int arr[N];//存储答案
//x表示当前枚举到的位置
void dfs2(int x) {
    if (x > n) {
        for (int i = 1; i <= n; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
    for (int i = 1; i <= n; i++) {
        if (!st[i]) {
            st[i] = true;
            arr[x] = i;
            dfs2(x + 1);
            st[i] = false;
            arr[x] = 0;
        }
    }
}
int main() {
    cin >> n;
     dfs1(1);//表示从1开始枚举
    dfs2(1);

}