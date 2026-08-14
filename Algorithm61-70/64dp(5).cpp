//
// Created by zhouyxuiang on 2026/3/31.
//
#include <iostream>
using namespace std;
//1.编辑距离
//用最少的操作让一个单词 变成 另一个单词
int editDistance(const string &a, const string &b) {
     int n1 = a.length(), n2 = b.length();
     //依旧是用dp的二维数组
     //dp[i][j]表示在A的前i个字符变成B的前j个字符最少要几步
     //如果想通就变成一样
     vector<vector<int>> dp(n1 + 1, vector<int>(n2 + 1));
     //先初始化第一列和第一行
     for (int i = 1; i <= n1; i++) dp[i][0] = i; // 全部删除
     for (int j = 1; j <= n2; j++) dp[0][j] = j; // 全部插入

     for (int i = 1; i <= n1; i++) {
         for (int j = 1; j <= n2; j++) {
             if (a[i] == b[j]) {
                 dp[i][j] = dp[i - 1][j - 1];
             }else {
                 // 三选一：删除、插入、替换
                 int del = dp[i-1][j] + 1;
                 int ins = dp[i][j-1] + 1;
                 int rep = dp[i-1][j-1] + 1;
                 dp[i][j] = min({del, ins, rep});
             }
         }
     }
     return dp[n1][n2];
 }
// i, j: 当前位置
// count: 已经拿了几个
// max_val: 手中宝贝的最大价值 (初始传-1)
int m,n,k;
int grid[55][55];//是来存宝藏的价值的
//记忆化数组
long long dp[55][55][15][15];//来存储方案的数量的
int dfs(int i, int j , int count , int max_val) {
   // 定义一个四维数组dp
    vector<vector<vector<vector<int>>>> dp;
    if (i >= n || j >= m) return 0;
    //当到达终点时
    if (i == n && j == m) {
        //如果刚好拿到了k个 算一种方案
        return (count == k) ? 1 : 0;
    }
    // 3.查备忘录 (记忆化)
    // 注意这里要用 max_val + 1 作为下标，防止 -1 越界
    //这里是查看表格 记忆化搜索 防止重复计算
    //不等于-1说明已经计算过了
    if (dp[i][j][count][max_val + 1] != -1) {
        return dp[i][j][count][max_val + 1];
    }
    int res = 0;
    //做出决策取决于当前格子的宝贝的价值
    int curr_val = grid[i][j];
    // 情况1 还没拿满k个 目前的大于手里的价值
    if (count < k && curr_val > max_val) {
        res += dfs(i + 1, j, count + 1, max_val);//向下走
        res += dfs(i, j + 1, count + 1, max_val);//向右走
    }
    //情况2 不能拿宝贝
    res += dfs(i + 1, j, count, max_val);
    res += dfs(i, j + 1, count, max_val);
    // 同样要用 max_val + 1
    dp[i][j][count][max_val + 1] = res;

    return res;

 }
int main() {
    memset(dp,-1,sizeof(dp));
    cin >> m >> n >> k;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> grid[i][j];
        }
    }

    int result = dfs(1, 1, 0, -1);

}