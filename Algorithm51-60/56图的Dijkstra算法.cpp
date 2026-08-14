//
// Created by zhouyxuiang on 2026/3/23.
//
//使用范围 权值没有负数
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <climits>
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

//找到未被处理的点 且 距离起点最近的节点
/*遍历 distanceMap 里所有节点
筛选出 ** 未被 selected（未确定最短路径）** 的节点
在这些节点里找到距离最小的那个，返回它
初始 minDistance 用最大值
 */
Node* getMinDisanceAndUnselectedNode(unordered_map<Node* , int> distanceMap, unordered_set<Node*> selectedNodes) {
    Node* minNode = nullptr;
    int minDistance = INT_MAX;
    for (auto entry : distanceMap) {
            Node* node = entry.first;
            int distance = entry.second;
        if (selectedNodes.find(node) != selectedNodes.end() && distance < minDistance) {
            minNode = node;
            minDistance = distance;
            }
        }
    return minNode;
}
unordered_map<Node*, int> dijkstra(Node* head) {
    // key: 节点, value: 从 head 出发到该节点的最小距离
    //如果没有记录 说明没有连接 value为MAX
    unordered_map<Node*, int> distanceMap;
    distanceMap[head] = 0;
    //确定已经确定的最短路径节点
    unordered_set<Node*> selectedNodes;
    Node * minNode = getMinDisanceAndUnselectedNode(distanceMap,selectedNodes);
    //循环到没有可以选择的点
    while (minNode != nullptr) {
        int distance = distanceMap[minNode];
        //遍历当前节点的所有邻居
        for (Edge* edge : minNode->edges) {
            Node* toNode = edge->to;//邻居节点
            int weight = edge->weight;
            if (distanceMap.find(toNode) == distanceMap.end()) {
                distanceMap[toNode] = distance + weight;
                //这一段表示到toNode时候 distance + weight表示开始的点到这个toNode最近的距离
            }
            //比较新路线是否会更近
            distanceMap[toNode] =min(distanceMap[toNode], distance + weight);
        }
        //所有的点 邻居都更新完了
        //最短距离确定
        selectedNodes.insert(minNode);
        //4.继续寻找下一个点
        minNode = getMinDisanceAndUnselectedNode(distanceMap, selectedNodes);
    }
    return distanceMap;
}
int main() {
    // 建图：4个节点
    Node* a = new Node(0);
    Node* b = new Node(1);
    Node* c = new Node(2);
    Node* d = new Node(3);

    // 加边（有向图）
    a->edges.push_back(new Edge(a, b, 1));
    a->edges.push_back(new Edge(a, c, 4));
    b->edges.push_back(new Edge(b, c, 2));
    b->edges.push_back(new Edge(b, d, 5));
    c->edges.push_back(new Edge(c, d, 1));

    // 执行 Dijkstra，从 a 点出发
    auto result = dijkstra1(a);

    // 输出结果
    cout << "起点到各点最短距离：" << endl;
    for (auto& entry : result) {
        cout << "节点 " << entry.first->val << " : " << entry.second << endl;
    }

}