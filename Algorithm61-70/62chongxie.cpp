//
// Created by zhouyxuiang on 2026/3/30.
//
#include <iostream>
using namespace std;
const int N = 100010;
struct Edge {
    int to;
    int w;//去的城市

};
vector<Edge> e;
int dist[N];
void dfs(int u , int parent) {

    for (auto &c : e) {//遍历所有邻边
        int v = c.to;

        if (v == parent) continue;
        dist[v] = dist[u] + c.w;
        dfs(v, u);
    }
}