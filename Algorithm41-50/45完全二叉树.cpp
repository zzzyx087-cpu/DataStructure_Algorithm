//
// Created by zhouyxuiang on 2026/3/19.
//
#include <iostream>
#include <queue>
using namespace std;
struct Node {
    int val;
    Node* right;
    Node* left;
    int value;
    Node (int x) : val(x), right(nullptr), left(nullptr) {};
};
bool isCBT(Node * root) {
    if (root == nullptr) return true;
    queue<Node*> q;
    bool leaf = false;//是否遇到两个孩子不双全的节点
    Node *l = nullptr;
    Node *r = nullptr;
    q.push(root);
    while (!q.empty()) {
        Node * curr = q.front();
        q.pop();
        l = curr->left;
        r = curr->right;
        if (leaf && (l != nullptr || r != nullptr)) {
            return false;
        }

        // 情况2：左空但右不空 → 绝对不是 CBT
        if (l == nullptr && r != nullptr) {
            return false;
        }
        if (l != nullptr) {
            q.push(l);
        }
        if (r != nullptr) {
            q.push(r);
        }
        if (l == nullptr || r== nullptr) {
            leaf = true;
        }
    }
    return true;
}

int main() {

        // 构建一棵 完全二叉树
        Node* root = new Node(1);
        root->left = new Node(2);
        root->right = new Node(3);
        root->left->left = new Node(4);
        root->left->right = new Node(5);
        root->right->left = new Node(6);

        bool res = isCBT(root);

        cout << "是不是完全二叉树：" << boolalpha << res << endl;

        return 0;
    }

