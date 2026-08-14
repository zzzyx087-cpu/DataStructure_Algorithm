//
// Created by  on 2026/3/22.
//
#include <iostream>
#include <unordered_map>
#include <vector>
#include <unordered_set>
using namespace std;

struct Edge;
struct Node {
    int val;
    int in;  //入度
    int out; //出度
    vector<Node*> nexts;// 邻居节点
    vector<Edge*> edges;// 从该节点出发的边
    Node(int v) : val(v) ,in(0), out(0) {}
};
// 边 结构
struct Edge {
    Node* from;   // 起点
    Node* to;     // 终点
    int weight;   // 权重

    Edge(Node* f, Node* t, int w) : from(f), to(t), weight(w) {}
};
// 图 结构
struct Graph {
    unordered_map<int, Node*> nodes;  // 编号 -> 节点
    unordered_set<Edge*> edges;       // 所有边
};
//图的宽度优先遍历
//1.利用队列实现
//2.从源节点开始依次按照宽度进队列再弹出
//3.每次弹出一个点 把该节点所有没有进过队列的邻节点放入队列
//4.直到队列变空
//BFS 的本质:像水波纹一样扩散
void bfs(Node* node) {
    if (node == nullptr) return;
    queue<Node*> q;
    unordered_set<Node *> visited;
    //先放最开始的点
    q.push(node);
    visited.insert(node);
    //while循环
    while (!q.empty()) {
        Node* curr = q.front();
        q.pop();
        cout << curr->val << " ";
        //遍历这个节点的邻居
        for (Node* next : curr->nexts) {
            if (visited.find(next) == visited.end()) {
                visited.insert(next);
                q.push(next);
            }
        }
    }
}
//DFS 的本质:深度优先
void dfs(Node* node) {
    if (node == nullptr) return;
    //栈来实现 深度优先
    stack<Node*> s;
    unordered_set<Node *> visited;

    s.push(node);
    visited.insert(node);
    cout << node->val << " ";
    while (!s.empty()) {
        Node* cur = s.top();
        s.pop();
       //for循环 遍历邻居
        for (Node* next : cur->nexts) {
            if (visited.find(next) == visited.end()) {
                s.push(cur);
                s.push(next);
                visited.insert(next);
                cout << next->val << " ";
                //如果到达 E 了
                //4. 继续弹出
                //弹出 C → 没新路
                //弹出 B → 没新路
                //弹出 A → 没新路
            }
        }
    }

}
//递归形式 DFS
unordered_set<Node*> visited;
void DFS2(Node * curr) {
    visited.insert(curr);
    cout << curr->val << " ";
    //.遍历所有邻居
    for (Node* next : curr->nexts) {
        if (visited.find(next) == visited.end()) {
            DFS2(next);
        }
    }

}
int main() {
    // 1. 创建图
    Graph g;

    // 2. 创建4个节点
    g.nodes[1] = new Node(1);
    g.nodes[2] = new Node(2);
    g.nodes[3] = new Node(3);
    g.nodes[4] = new Node(4);

    // 3. 设置邻居关系（建图）
    g.nodes[1]->nexts.push_back(g.nodes[2]);
    g.nodes[1]->nexts.push_back(g.nodes[3]);

    g.nodes[2]->nexts.push_back(g.nodes[4]);

    // 4. 开始 BFS 遍历（从节点1出发）
    cout << "=== BFS 遍历结果 ===" << endl;
    bfs(g.nodes[1]);

    // 5. 释放内存（不简写版）
    for (auto& pair : g.nodes) {
        delete pair.second;
    }
    for (Edge* e : g.edges) {
        delete e;
    }
    // 1. 创建图
    unordered_map<char, Node*> graph;

    // 2. 创建节点 A B C D E
    graph['A'] = new Node('A');
    graph['B'] = new Node('B');
    graph['C'] = new Node('C');
    graph['D'] = new Node('D');
    graph['E'] = new Node('E');

    // ======================================================
    // 3. 【核心】设置邻居顺序 —— 你在这里决定先走谁！
    // ======================================================
    // A 的邻居：B 第一个 → 所以DFS一定先走B！
    graph['A']->nexts.push_back(graph['B']);
    graph['A']->nexts.push_back(graph['C']);
    graph['A']->nexts.push_back(graph['E']);

    // B 的邻居
    graph['B']->nexts.push_back(graph['A']);
    graph['B']->nexts.push_back(graph['C']);

    // C 的邻居
    graph['C']->nexts.push_back(graph['A']);
    graph['C']->nexts.push_back(graph['B']);
    graph['C']->nexts.push_back(graph['D']);
    graph['C']->nexts.push_back(graph['E']);

    // D 的邻居
    graph['D']->nexts.push_back(graph['C']);

    // E 的邻居
    graph['E']->nexts.push_back(graph['A']);
    graph['E']->nexts.push_back(graph['C']);

    // 4. 开始DFS
    cout << "DFS 遍历顺序：";
    dfs(graph['A']);

    // 释放内存
    for (auto& pair : graph) {
        delete pair.second;
    }

}