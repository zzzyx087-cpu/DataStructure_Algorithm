//
// Created by zhouyxuiang on 2026/3/30.
//
#include <iostream>

using namespace std;
//1.砝码问题
//你有一架天平和 N 个砝码, 这 N 个砝码重量依次是 W1,W2,W3...
//问能称出多少种不同的重量
//考虑相加 相减 所有相加 几个减一个...
int n;
//2.LCS问题
//判断两个字符串的最长相同的子序列
int longestCommonSubsequence(const string& a, const string& b) {
    int n1 = a.length();
    int n2 = b.length();
    //初始化一个DP数组行数n1 + 1 列数N2 + 1
    vector<vector<int>> dp(n1 + 1, vector<int>(n2 + 1));
    //填充DP表
    for (int i = 1; i <= n1; i++) {
        for (int j = 1; j <= n2; j++) {
            if (a[i - 1] == b[j - 1]) dp[i][j] = dp[i - 1][j - 1] + 1;
            else dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }
    return dp[n1][n2];
}

int main() {
    cin >> n;
    vector<int> W(n);
    int sum = 0;
    for (int i = 0; i < n; i++) {
        cin >> W[i];
        sum += W[i];
    }
    // 1. 计算所有砝码的总重量
    //sum
    if (n == 0) cout << 0;
    if (n == 1) cout << 1;
    vector<bool> dp(sum + 1, false);
    dp[0] = true;
    for (int w : W) {
        vector<bool> new_dp = dp;
        for (int j = 0; j <= sum; ++j) {
            if (dp[j]) {
                if (j + w <= sum) new_dp[j + w] = true;
                new_dp[abs(j - w)] = true;
            }
        }
        dp.swap(new_dp);  // 👈 用 swap 代替赋值，比 = 更快
    }
    //相当于01背包问题 不放 放左边 放右边
    //dp[j] = true说明能够称出来
    int ans = 0;
    for (int i = 0; i <= sum; i++) {
        if (dp[i]) ans++;
    }
    cout << ans << endl;
}