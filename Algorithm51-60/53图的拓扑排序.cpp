//
// Created by zhouyxuiang on 2026/3/22.
//
#include <iostream>
#include <unordered_map>
#include <vector>
#include <unordered_set>
#include <queue>
#include <stack>
using namespace std;

struct Edge;
struct Node {
    int val;
    int in;  //入度
    int out; //出度
    vector<Node*> nexts;// 邻居节点
    vector<Edge*> edges;// 从该节点出发的边
    Node(int v) : val(v), in(0) , out(0) {}
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
    unordered_map<int,Node*> nodes;  // 编号 -> 节点 int 表示入度个数
    unordered_set<Edge*> edges;       // 所有边
};
//拓扑排序 适合的范围 要求有向图 且有入度为0的节点 并且没有环
vector<Node*> topoSorted(Graph& graph) {
    //key表示一个node
    //value 剩余的入度
    unordered_map<Node* , int> inMap;
    queue<Node*> zeroIn;
    // 把所有入度为0的节点先加入队列
    for (auto entry:graph.nodes) {
        Node * node = entry.second;
        inMap[node] = node->in;
        if (node->in == 0) zeroIn.push(node);
    }
    vector<Node*> result;
    //开始消除入度为0对后其他节点的影响
    while (!zeroIn.empty()) {
        Node * cur = zeroIn.front();
        zeroIn.pop();
        result.push_back(cur);
        //遍历邻居 入度-1
        for (Node * next : cur->nexts) {
            inMap[next]--;
            if (inMap[next] == 0) zeroIn.push(next);
        }

    }
    return result;

}
void freeGraph(Graph& g) {
    for (auto node : g.nodes) {
        Node * cur = node.second;
        delete cur;
    }
}
// ========================
// 测试 main 函数
// ========================
int main() {
    Graph g;
    // 创建点
    g.nodes[1] = new Node(1);
    g.nodes[2] = new Node(2);
    g.nodes[3] = new Node(3);
    g.nodes[4] = new Node(4);
    g.nodes[5] = new Node(5);

    // 建边 1->2 1->3 2->4 3->4 4->5
    g.nodes[1]->nexts.push_back(g.nodes[2]); g.nodes[2]->in++;
    g.nodes[1]->nexts.push_back(g.nodes[3]); g.nodes[3]->in++;
    g.nodes[2]->nexts.push_back(g.nodes[4]); g.nodes[4]->in++;
    g.nodes[3]->nexts.push_back(g.nodes[4]); g.nodes[4]->in++;
    g.nodes[4]->nexts.push_back(g.nodes[5]); g.nodes[5]->in++;

    // 拓扑排序
    vector<Node*> res = topoSorted(g);

    // 输出
    cout << "拓扑序：";
    for (auto n : res) cout << n->val << " ";
    freeGraph(g);
}
