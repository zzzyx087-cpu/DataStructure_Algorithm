//
// Created by zhouyxuiang on 2026/4/26.
//
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
//1.底端食物链 最大食物链计数
const int MOD = 80112002;

class Solution1 {
public:
    int solve(int n , int m , vector<pair<int ,int>> &edges) {
        //需要有一个出度
        vector<vector<int>> graph(n+1);
        vector<int> in_degree(n + 1, 0);
        vector<int> out_degree(n + 1, 0);
        for (auto& edge : edges) {
            int a = edge.first, b = edge.second;
            graph[a].push_back(b);
            //a -> b
            in_degree[b]++;
            out_degree[a]++;
        }
        vector<int> dp(n + 1);//一个数组计算每一个推给自己的食物链条数
        queue<int> q;
        for (int i = 1; i <= n; i++) {
            if (in_degree[i] == 0) {
                dp[i] = 1;
                q.push(i);
            }
        }
        //开始拓扑排序
        while (!q.empty()) {
            int cur = q.front();
            q.pop();

            for (int v : graph[cur]) {//遍历u指向的所有的点v
                dp[v] = (dp[v] + dp[cur]) % MOD;
                if (--in_degree[v] == 0) {
                    q.push(v);//把v这个点放进队列里
                }
            }
        }
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            if (out_degree[i] == 0) {
                ans = (ans + dp[i]) % MOD;
            }
        }
        return ans;
    }
};
//喧闹和富有题
class Solution2 {
    //给需多个数组 pair里表示前一个比后一个有钱
public:
    vector<int> LoudAndRich(vector<vector<int>> richer, vector<int> quiet) {
        int n = quiet.size();
        vector<vector<int>> graph(n);
        vector<int> inDgree(n);
        vector<int> ans(n);
        for (int i = 0; i < n; i++) {
            ans[i] = i;//每个人的答案默认是自己
        }
        //建立图像
        for (auto& e : richer) {
            int a = e[0], b = e[1];
            graph[b].push_back(a);
            inDgree[a]++;
        }
        //拓扑排序
        queue<int> q;
        //找入度为0的那个点
        for (int i = 0; i < n; i++) {
            if (inDgree[i] == 0) {
                q.push(i);
            }
        }
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : graph[u]) {
                if (quiet[u] < quiet[v]) {
                    ans[v] = ans[u];
                }
                inDgree[v]--;
                if (inDgree[v] == 0) {
                    q.push(v);
                }
            }
        }
        return ans;
    }
};
class Soluton3 {
    public:
    //要有前置条件具备了 才能完成下一个任务
    //返回最快完成的时间
    //一个完成的时间数组 一个单点的时间数组
    int mininumTime(int n, vector<vector<int>>& relations, vector<int>& time) {
        //1.先建立图 再 添入度表
        vector<vector<int>> adj(n + 1);
        vector<int> inDegree(n + 1, 0);
        for (auto& e : relations) {
            int u = e[0], v = e[1];
            adj[u].push_back(v);
            inDegree[v]++;
        }
        // dp[i] = 完成课程 i 所需的最早时间
        vector<int> dp(n + 1, 0);
        queue<int> q;
        for (int i = 1; i <= n; i++) {
            if (inDegree[i] == 0) {
                dp[i] = time[i - 1];
                q.push(i);
            }
        }
        //开始拓扑排序
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : adj[u]) {
                dp[v] = max(dp[v] , dp[u] + time[v - 1]);
                if (--inDegree[v] == 0) {
                    q.push(v);
                }
            }
        }
        //返回所有课程完成时的最大值
        return *max_element(dp.begin() + 1, dp.end());

    }
};
//最难的题
//参加会议的最多员工数
//先找两个小环
//两环的最长的一条链能够安排

//如果有大环(个数大于等于3)就只能安排这个大环

class Soluton4 {
public:
    int MaxMumInvitations(vector<int> &favorite) {
        //favorite[a] = b表示a->b
        int n = favorite.size();
        vector<int> indegree(n);
        for (int i = 0; i < n; i++) {
            indegree[favorite[i]]++;
        }
        vector<int> queue(n);
        int l = 0, r = 0;
        //让入度为0的进入队列
        for (int i = 0; i < n; i++) {
            if (indegree[i] == 0) {
                queue[r++] = i;
            }
        }
        //用一个deep数组
        //不包括i i之前的最长链长度
        //前提是不在环上
        vector<int> deep(n,0);
        while (l < r) {
            int cur = queue[l++];
            int next = favorite[cur];
            deep[next] = max(deep[next], deep[cur] + 1);
            if (--indegree[next] == 0) {
                queue[r++] = next;
            }
        }
        //处理环的部分
        int sumOfSmallrings = 0;
        int bigrings = 0;
        for (int i = 0; i < n; i++) {
            if (indegree[i] > 0) {
                int maxSize = 1;
                indegree[i] = 0;//标记成0防治重复遍历
                int cur = favorite[i];
                while (cur != i) {
                    indegree[cur] = 0;
                    maxSize++;
                    cur = favorite[cur];//继续向下走
                }
                if (maxSize == 2) {
                    sumOfSmallrings += 2 + deep[i] + deep[favorite[i]];
                }else {
                    bigrings = max(bigrings,maxSize);
                }
            }
        }
        return max(sumOfSmallrings ,bigrings);
    }
};
