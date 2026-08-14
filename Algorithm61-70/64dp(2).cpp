//
// Created by zhouyxuiang on 2026/3/30.
//
#include <iostream>
#include <algorithm>
using namespace std;
//采药问题
int const N = 10001;
vector<int> T(N);//表示时间
vector<int> M(N);//表示价值
int t , m;//表示一共的时间 ， 表示草药的价值
vector<int> dp(m + 1, 0); // dp[j] = 容量j时的最大价值
//创建一个数组 dp，大小是 时间容量 + 1。
//dp[j] 表示：背包容量是 j 的时候，能装的最大价值是多少。
// 一开始全部是 0，因为啥都没装。
//dp来做
void dp1() {//x表示处理到的位置
   for (int i = 0; i <= t ; i++) dp[i] = 0;
    for (int i = 0; i < m; ++i) {
        for (int j = t; j >= T[j]; --j) {
            dp[j] = max(dp[i] , dp[j - T[i]] + M[i]);
        }
    }
}
//记忆化DFS
int memo[105][1005];
int dfs(int x, int used_time) {//ued_time表示减去的时间
    if (x == 0) return 0;//没有药采
    if (memo[x][used_time] != -1) return memo[x][used_time];
    //不采第x株
    int res1 = dfs(x+1,used_time);
    //采第x株
    int res2 = 0;
    if (used_time + T[x] <= t) {
        res2 = dfs(x + 1 , used_time + T[x]) + M[x];
    }
    return memo[x][used_time] = max(res1 , res2);
}
//例题5 是否能分割两个子数组让两个数组和相等
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return false;

        int total = 0;  //
        for (int i = 0; i < n; i++) {
            total += nums[i];
        }
        if (total % 2 != 0) return false;

        int half = total / 2;
        vector<bool> dp(half + 1, false);  //
        dp[0] = true;
        for (int num : nums) {
            for (int j = half; j >= num; j--) {
                if (dp[j - num]) {
                    dp[j] = true;
                }
            }
        }
        return dp[half];
    }
};
int main() {
    cin >> t >> m;
    for (int i = 0; i < m; i++) {
        cin >> T[i] >> M[i];
    }
    dp1();
    cout << dp[t] << endl;
}