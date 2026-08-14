//
// Created by zhouyxuiang on 2026/6/7.
//
#include <iostream>
using namespace std;
//1.斐波那契数列
//时间复杂度O(logN)
class Solution1 {
    public:
    int fib2(int n) {
        vector<int> dp(n+1,-1);
        return f2(n,dp);
    }
    int f2(int i, vector<int> &dp) {
        if (i == 0) {
            return 0;
        }
        if (i == 1) {
            return 1;
        }
        if (dp[i] != -1) {
            return dp[i];
        }
        int ans = f2(i - 1 , dp) + f2(i - 2 , dp);
        dp[i] = ans;
        return ans;
    }
};
//2.