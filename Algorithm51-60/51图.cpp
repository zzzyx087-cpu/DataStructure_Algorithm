//
// Created by  on 2026/3/20.
//
#include <iostream>

#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;
//图
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
Graph createGraph(const vector<vector<int>> &matrix) {
    // 创建一张空图
    Graph graph;

    for (int i = 0; i < matrix.size(); i++) {//matrix[0][0],matrix[0][1],matrix[0][2]
        int from = matrix[i][0];
        int to = matrix[i][1];
        int weight = matrix[i][2];
        if (graph.nodes.find(from) == graph.nodes.end()) {
            graph.nodes[from] = new Node(from);
        }
        if (graph.nodes.find(to) == graph.nodes.end()) {
            graph.nodes[to] = new Node(to);
        }
        Node* fromNode = graph.nodes[from];
        Node* toNode = graph.nodes[to];
        Edge* newEdge = new Edge(fromNode, toNode, weight);
        //把next这个toNode添加进入容器
        fromNode->nexts.push_back(toNode);
        fromNode->out++;
        toNode->in++;
        // 将边加入节点和图
        fromNode->edges.push_back(newEdge);
        graph.edges.insert(newEdge);
    }
    return graph;
}

//     // 获取矩阵一共有多少行（多少条边）
//     int rowCount = matrix.size();
//
//     // 原始 for 循环，不使用 auto，不使用简写
//     for (i = 0; i < rowCount; i++) {
//
//         // 拿到第 i 行的数据（一条边：from to weight）
//         vector<int> currentRow = matrix[i];
//
//         // 分别取出三个值
//         int from = currentRow[0];
//         int to = currentRow[1];
//         int weight = currentRow[2];
//
//         // ============== 处理 from 节点 ==============
//         // 如果图里没有这个节点，就新建
//         if (graph.nodes.find(from) == graph.nodes.end()) {
//             Node* newNode = new Node(from);
//             graph.nodes[from] = newNode;
//         }
//
//         // ============== 处理 to 节点 ==============
//         if (graph.nodes.find(to) == graph.nodes.end()) {
//             Node* newNode = new Node(to);
//             graph.nodes[to] = newNode;
//         }
//
//         // 从图里拿出这两个节点
//         Node* fromNode = graph.nodes[from];
//         Node* toNode = graph.nodes[to];
//
//         // 创建一条新的边
//         Edge* newEdge = new Edge(weight, fromNode, toNode);
//
//         // ============== 更新节点信息 ==============
//         // 把终点加入邻居
//         fromNode->nexts.push_back(toNode);
//
//         // 起点出度 +1
//         fromNode->out = fromNode->out + 1;
//
//         // 终点入度 +1
//         toNode->in = toNode->in + 1;
//
//         // 把边加入起点的边列表
//         fromNode->edges.push_back(newEdge);
//
//         // 把边加入图的边集合
//         graph.edges.insert(newEdge);
//     }
//
//     // 把建好的图返回
//     return graph;
// }
int main() {
    vector<vector<int>> matrix = {
        {1, 2, 5},
        {2, 3, 3},
        {1, 3, 10}
    };

    Graph g = createGraph(matrix);
    cout << "图生成成功！" << endl;
    cout << "节点数：" << g.nodes.size() << endl;
    cout << "边数：" << g.edges.size() << endl;

    // 注意：实际使用后需要释放内存，避免泄漏
    // ...（此处省略内存释放代码）
    // 释放图里所有 节点 和 边

    for (Edge* currentEdge : g.edges) {
        delete currentEdge;
    }

    // ==============================
    // 释放图中所有节点（不简写版本）
    // ==============================

    for (auto nodePair : g.nodes) {
        delete nodePair.second;
    }

}