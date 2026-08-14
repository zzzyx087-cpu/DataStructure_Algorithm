//
// Created by zhouyxuiang on 2026/3/22.
//
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
using namespace std;

struct Edge;
struct Node {
    int val;
    int in, out;
    vector<Node*> nexts;
    vector<Edge*> edges;
    Node(int v) : val(v), in(0), out(0) {}
};

struct Edge {
    Node* from;
    Node* to;
    int weight;
    Edge(Node* f, Node* t, int w) : from(f), to(t), weight(w) {}
};

struct Graph {
    unordered_map<int, Node*> nodes;
    unordered_set<Edge*> edges;
};

// ==================== 并查集 ====================
//只有两个功能 1.find找到x的祖宗
//2.unite（x,y）把x和y连接起来
struct DSU {
    vector<int> fa;
    DSU(int n) {
        fa.resize(n);
        for (int i = 0; i < n; ++i) {
            fa[i] = i;
        }
    }
    int find(int x) {
        if (fa[x] != x) fa[x] = find(fa[x]); return fa[x];
    }
    bool unite(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return false;
        fa[x] = y;
        return true;
    }
};

// ==================== 完美 Kruskal（无空间浪费） ====================
int kruskal(Graph& graph) {
    // 1. 把所有点编号 → 连续 id 【离散化】
    vector<int> ids;
    for (auto& p : graph.nodes) ids.push_back(p.first);
    unordered_map<int, int> id_map;
    int idx = 0;
    for (int x : ids) id_map[x] = idx++;

    // 2. 拿所有边
    vector<Edge*> edges(graph.edges.begin(), graph.edges.end());
    sort(edges.begin(), edges.end(), [](Edge* a, Edge* b) {
        return a->weight < b->weight;
    });

    // 3. 并查集大小 = 真实点数 ✅ 不浪费空间
    DSU dsu(ids.size());
    int total = 0;

    for (Edge* e : edges) {
        int u = id_map[e->from->val];  // 连续编号
        int v = id_map[e->to->val];
        if (dsu.unite(u, v)) {
            total += e->weight;
        }
    }
    return total;
}

// ==================== 测试 ====================
int main() {
    Graph g;
    Node* n1 = new Node(1);
    Node* n2 = new Node(2);
    Node* n3 = new Node(3);
    g.nodes[1] = n1; g.nodes[2] = n2; g.nodes[3] = n3;

    Edge* e1 = new Edge(n1, n2, 2);
    Edge* e2 = new Edge(n1, n3, 3);
    Edge* e3 = new Edge(n2, n3, 1);
    g.edges = {e1, e2, e3};

    cout << kruskal(g) << endl;

    for (auto& p : g.nodes) delete p.second;
    for (Edge* e : g.edges) delete e;
    return 0;
}