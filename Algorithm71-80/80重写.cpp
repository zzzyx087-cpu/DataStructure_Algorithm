//
// Created by zhouyxuiang on 2026/4/28.
//
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
//第一题最大食物链
class Solution1 {
    public:
    int solve(int n , int m , vector<pair<int,int>> &edges) {
        //最后在dp数组里统计出度为0的
        vector<vector<int>> graph(n+1);
        vector<int> inDegree(n+1,0);
        vector<int> outDegree(n+1,0);
        for (auto& e : edges) {
            int a = e.first, b = e.second;
            graph[a].push_back(b);
            inDegree[b]++;
            outDegree[a]++;
        }
        vector<int> dp(n+1,0);
        queue<int> q;
        for (int i = 1;i <=n;i++) {
            if (inDegree[i] == 0) {
                dp[i] = 1;
                q.push(i);
            }
        }
        //开始拓扑排序
        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            for (int v : graph[cur]) {
                dp[v] = dp[v] + dp[cur];//之前可能已经有路径经过了v了
                if (--inDegree[v] == 0) {
                    q.push(v);
                }
            }
        }
        int ans = 0;
        for (int i = 1;i <= n;i++) {
            if (outDegree[i] == 0) {
                ans += dp[i];
            }
        }
        return ans;
    }
};
class Solution2 {
    public:
    int mininumTime(int n, vector<vector<int>>& relations, vector<int>& time) {
        vector<vector<int>> graph(n+1);
        vector<int> inDegree(n+1,0);
        for (auto& e : relations) {
            int u = e[0] , v = e[1];
            graph[u].push_back(v);
            inDegree[v]++;
        }
        // dp[i] = 完成课程 i 所需的最早时间
        vector<int> dp(n + 1, 0);
        queue<int> q;
        for (int i = 1; i <= n;i++) {
            if (inDegree[i] == 0) {
                q.push(i);
                dp[i] = time[i - 1];
            }
        }
        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            for (int v : graph[cur]) {
                dp[v] = max(dp[cur] + time[v-1] , dp[v]);
                if (--inDegree[v] == 0) {
                    q.push(v);
                }
            }
        }
        return *max_element(dp.begin(), dp.end());
    }
};
//参加会议的最多的员工数量
class Solution3 {
public:
    int MaxMumInvitations(vector<int> &favorite) {
        int n = favorite.size();
        vector<int> inDegree(n,0);
        for (int i = 1; i <= n;i++) {
            inDegree[favorite[i]]++;
        }
        vector<int> q(n);
        int l = 0, r = 0;
        for (int i = 0; i < n;i++) {
            if (inDegree[i] == 0) {
                q[r++] = i;
            }
        }
        //用一个dp数组表示不包括这个i i之前的最长的链的长度 不包括环
        vector<int> dp(n,0);
        //初始化dp数组
        while (l < r) {
            int cur = q[l++];
            int next = favorite[cur];
            dp[next] = max(dp[next], dp[cur] + 1);
            //只有链的入度会变成0
            //环上的不会变成0
           if (--inDegree[next] == 0) {
               q[r++] = next;
           }
        }
        //枝已经全部进入队列里了
        //开始处理环
        int smallring = 0;
        int bigring = 0;
        for (int i = 0; i < n;i++) {
            if (inDegree[i] > 0) {
                int cur = favorite[i];
                int MaxSize = 1;
                inDegree[i] = 0;//标记成0
                while (cur != favorite[cur]) {
                    inDegree[cur]=0;
                    cur = favorite[cur];
                    MaxSize++;
                }
                if (MaxSize == 2) {
                    smallring = 2 + dp[cur] + dp[favorite[cur]];
                }else {
                    bigring = max(bigring, MaxSize);
                }
            }
        }
        return max(smallring, bigring);
    }

};
