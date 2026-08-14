//
// Created by zhouyxuiang on 2026/4/8.
//
#include <iostream>
using namespace std;
//统计子矩阵
/*
输入3 4 10
1 2 3 4
5 6 7 8
9 10 11 12

输出
19
给定一个 N x M 的矩阵 A 和一个整数 K，
统计有多少个子矩阵满足子矩阵中所有元素的和不超过 K。
 */
int main() {
    int n , m ,k;
    cin >> n >> m >> k;
    vector<vector<int>> matrix(n + 1, vector<int>(k + 1, 0));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> matrix[i][j];
            //利用前缀和 提前算好
            //核心公式:区间[l,r]的和 = pre[r] - pre[l-1]
            //pre[i][j]表示(1,1)到(i,j)这个矩形的和
            //matrix[i][j]表示j列前i行的和
            matrix[i][j] += matrix[i - 1][j];
        }
    }
    long long ans = 0;
    //枚举上边界 top
    for (int top = 1; top <= n; top++) {
        //枚举下边界bottom
        for (int bottom = 1; bottom <= m; bottom++) {
            //统计