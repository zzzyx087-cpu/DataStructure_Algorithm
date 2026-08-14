//
// Created by zhouyxuiang on 2026/3/22.
//
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <set>
using namespace std;

// 你的图结构（固定不变）
struct Edge;
struct Node {
    int val;
    vector<Node*> nexts;
    vector<Edge*> edges;
    Node(int v) : val(v) {}
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

// 小根堆比较器
struct EdgeComparator {
    bool operator()(const Edge* a, const Edge* b) const {
        return a->weight > b->weight;
    }
};

// ===================== 【核心：Prim 算法实现】 =====================
set<Edge*> primMST(Graph& graph) {
    // 1. 核心三件套 → 你已经懂了
    priority_queue<Edge*, vector<Edge*>, EdgeComparator> pq;
    unordered_set<Node*> visited;
    set<Edge*> result;

    // 遍历所有点（防止图不连通）
    for (auto& entry : graph.nodes) {
        Node* cur = entry.second;

        if (visited.find(cur) == visited.end()) {//说明没有被标记 这个点不在这个表里
            visited.insert(cur);
            // 标记已访问
            // 把这个点的所有边加入堆
            for (Edge* e : cur->edges) {
                pq.push(e);
            }

            // 核心循环
            while (!pq.empty()) {
                Edge* e = pq.top();    // 拿最小边
                pq.pop();

                Node* toNode = e->to;  // 拿到边的终点

                // 如果这个点没访问过 → 选中这条边
                if (visited.find(toNode) == visited.end()) {
                    result.insert(e);       // 加入答案
                    visited.insert(toNode); // 标记已访问

                    // 把新点的边继续加入堆
                    for (Edge* nextE : toNode->edges) {
                        pq.push(nextE);
                    }
                }
            }
        }
    }
    return result;
}

// ===================== 测试运行 =====================
int main() {
    Graph g;
    // 建点
    Node* n1 = new Node(1);
    Node* n2 = new Node(2);
    Node* n3 = new Node(3);
    Node* n4 = new Node(4);
    g.nodes[1] = n1;
    g.nodes[2] = n2;
    g.nodes[3] = n3;
    g.nodes[4] = n4;

    // 建边（无向图双向加）
    Edge* e1 = new Edge(n1, n2, 1);
    Edge* e1r = new Edge(n2, n1, 1);
    Edge* e2 = new Edge(n1, n4, 2);
    Edge* e2r = new Edge(n4, n1, 2);
    Edge* e3 = new Edge(n2, n3, 3);
    Edge* e3r = new Edge(n3, n2, 3);
    Edge* e4 = new Edge(n1, n3, 4);
    Edge* e4r = new Edge(n3, n1, 4);
    Edge* e5 = new Edge(n3, n4, 5);
    Edge* e5r = new Edge(n4, n3, 5);

    // 把边放进节点 & 图
    n1->edges = {e1, e2, e4};
    n2->edges = {e1r, e3};
    n3->edges = {e3r, e4r, e5};
    n4->edges = {e2r, e5r};

    g.edges = {e1,e1r,e2,e2r,e3,e3r,e4,e4r,e5,e5r};

    // 运行 Prim
    auto mst = primMST(g);

    // 输出结果
    int sum = 0;
    cout << "最小生成树边：" << endl;
    for (Edge* e : mst) {
        cout << e->from->val << " -> " << e->to->val << " 权值:" << e->weight << endl;
        sum += e->weight;
    }
    cout << "总权值：" << sum << endl;
    for (auto& entry : g.nodes) {
        delete entry.second;
    }
    // 2. 释放所有边
    for (Edge* e : g.edges) {
        delete e;
    }
    return 0;
}