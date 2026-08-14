//
// Created by zhouyxuiang on 2026/3/18.
//
#include <iostream>
#include <map>
using namespace std;
struct Node {
    Node * left;
    Node * right;
    int value;
    Node(int val) : value(val) ,left (nullptr) , right(nullptr) {}
};
//宽度优先遍历 越宽的 先 遍历
void bfsWidthFirst(Node * root) {
    if (!root) return;
    queue<pair<Node*,int>> q;
    map<int , vector<int>> levelmap;
    q.push({root,0});
    while (!q.empty()) {
       pair<Node*,int>current = q.front();
        q.pop();
        Node* node = current.first;//节点
        int level = current.second; //拿到层数
        levelmap[level].push_back(node->value);
        if (node->left) q.push({node->left,level+1});
        if (node->right) q.push({node->right,level+1});
    }
    vector<pair<int ,vector<int>>> levels(levelmap.begin(),levelmap.end());
    sort(levels.begin(),levels.end(),[](pair<int ,vector<int>>& a,pair<int ,vector<int>>& b) {
        return a.second.size() > b.second.size();
    });
    // 6. 输出结果：最宽的层先打印
    cout << "按宽度从大到小输出：" << endl;
    for (int i = 0; i < levels.size(); i++ ) {
        pair<int , vector<int>> currentlevel = levels[i];
        vector<int> &v = currentlevel.second;
        for (int j = 0; j < v.size(); j++) {
            cout << v[j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}
int main() {
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new  Node(4);
    root->left->right = new Node(5);
    root->right->left = new Node(6);
    root->right->right = new Node(7);

    bfsWidthFirst(root);
    return 0;
}