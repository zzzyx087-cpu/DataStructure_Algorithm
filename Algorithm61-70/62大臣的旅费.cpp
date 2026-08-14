//
// Created by zhouyxuiang on 2026/3/25.
//
#include <iostream>
using namespace std;
const int N = 100010;
struct Edge {
    int to;
    // int w;//去的城市

};
vector<Edge> g[N];
long long dist[N];  // 距离数组，用 long long 防止溢出
//国家有n个城市 所以用n-1条路连在一起 没有环 是一棵树
//找距离最远的两个点 再根据线性关系求得路费
int n;
//两次dfs就得到最大权值和
void dfs(int u , int parent) {
    for (auto& e : g[u]) {//遍历所有邻边
        int v = e.to;

        if (v == parent) continue;
        //不等于父节点
        dist[v] = dist[u] + e.w;
        dfs(v, u);
    }
}
int main() {
    cin >> n;
    //读入n-1条边
    for (int i = 1; i < n - 1; i++) {
        int a,b,c;
        cin >> a >> b >> c;
        g[a].push_back({b,c});
        g[b].push_back({a,c});
    }
    //第一遍dfs 从1开始找到最远的点
    memset(dist, 0, sizeof(dist));
    dfs(1, -1);
    int u = 1;
    for (int i = 1; i <= n; i++) {
        if (dist[u] < dist[i]) u = i;
    }
    //第二遍dfs
    memset(dist, 0, sizeof(dist));
    dfs(u, -1);
    long long max_dist = 0;
    for (int i = 1; i <= n; i++) {
        if (dist[i] > max_dist) max_dist = dist[i];
    }
    // ========== 计算路费 ==========
    // 路费 = 10 * S + S * (S + 1) / 2
    long long ans = 10LL * max_dist + max_dist * (max_dist + 1) / 2;
    cout << ans << endl;

    return 0;
}