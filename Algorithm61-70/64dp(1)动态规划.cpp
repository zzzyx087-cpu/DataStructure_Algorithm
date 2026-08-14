//
// Created by zhouyxuiang on 2026/3/27.
//
#include <iostream>

using namespace std;
//记忆化搜索

//例题1 大盗阿福
//输入
//2
//1 3 5
//4
//12 1 2 14
//输出
//6
//26
const int N = 100010;
int rob(vector<int> & nums) {
    int n = nums.size();
    if (n == 0) return 0;
    if (n == 1) return nums[0];
    vector<int> dp(n);
    //dp[i] 表示：走到第 i 家店铺，最多能偷多少钱。
    dp[0] = nums[0];
    dp[1] = max(nums[0], nums[1]);
//从第三家开始，一家一家往下推。
    for (int i = 2; i < n; i++) {
        dp[i] = max(dp[i - 1], dp[i - 2] + nums[i]);
        //dp[i-1] 表示不偷第i家
        //dp[i - 2] + nums[i]表示偷第i家
    }
    return dp.back();
    //表示最终能偷到的钱
}
//例题2 数字三角形
//从上到下让路径之和最大
//先输入行数
//再输逐行的数据

//先用dfs做
const int N2 = 1010;
int n1;
int g[N2][N2];
int mem[N2][N2];
int f[N2][N2];
int dfs(int x, int y) {
    if (mem[x][y]) return mem[x][y];
    if (x > n1 || y > n1) return 0;
    else return max(dfs(x+1, y), dfs(x+1, y+1));

}
//例题4最长递增子序列
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        //两个条件1.必须是递增 2.子序列
        //创建一个dp数组
        int n = nums.size();
        if (n == 0) return 0;
        // 1. 定义 dp 数组
        // dp[i] 表示：以 nums[i] 结尾的最长递增子序列长度
        vector<int> dp(n , 1);// 初始化：至少自己一个数，长度为1
        //状态转移
        for(int i = 1; i < n;i++){
            //看i前面所有的数字
            for(int j = 0; i < i;j++){
                if(nums[j] < nums[i]){
                    dp[i] = max(dp[i],dp[j] + 1);
                }
            }
            int ans = 0;
            for(auto x: dp) res = max(res,x);

            return res;
        }
    }
    };
    int main() {
        int n;
        cin >> n;
        vector<int> nums(n);
        for (int i = 0; i < n; i++) {
            cin >> nums[i];
        }
        int ans = rob(nums);
        cout << ans << endl;
        cin >> n1;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> g[i][j];
            }
        }

        for (int i = n;i >= 1;i --) {
            for (int j = 1;j <= n;j++) {
                f[i][j] = max(dfs(i + 1, j), dfs(i+1, j + 1) + g[i][j]);
            }
        }
        cout << dfs(0, 0) << endl;
        //例题3 01背包问题
        int n2, m;
        cin >> n2 >> m; // n: 物品数, m: 背包容量

        vector<int> v(n2), w(n2); // v: 体积, w: 价值
        for (int i = 0; i < n2; ++i) {
            cin >> v[i] >> w[i];
        }


        vector<int> dp(m + 1, 0); // dp[j] = 容量j时的最大价值
        //创建一个数组 dp，大小是 背包容量 + 1。
        //dp[j] 表示：背包容量是 j 的时候，能装的最大价值是多少。
        // 一开始全部是 0，因为啥都没装。
        for (int i = 0; i < n2; ++i) { // 遍历物品
            // 从后往前遍历，避免重复选取同一个物品
            for (int j = m; j >= v[i]; --j) {
                //后面的容量更新时，用的是【还没被当前物品改过的旧值】所以从j最大开始
                dp[j] = max(dp[j], dp[j - v[i]] + w[i]);
            }
        }
        //j 管背包容量
        //i 管第几个物品
        //两层循环合起来：
        //对每个物品，都去更新所有容量的最大价值

        cout << dp[m] << endl;
    }