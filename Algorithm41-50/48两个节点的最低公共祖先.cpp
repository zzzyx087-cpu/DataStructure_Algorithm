//
// Created by zhouyxuiang on 2026/3/20.
//
#include <iostream>
#include <map>
#include <set>
using namespace std;

struct Node{
    Node* left;
    int val;
    Node* right;
    Node(int x) {
        left = nullptr;
        right = nullptr;
        val = x;
    }
};
//o1 o2 一定属于head为头的树
//在这个前提下返回o1o2的祖先
//递归遍历 填充父亲的哈希表
void process(Node * head, unordered_map<Node* , Node*>* fathermap) {
    if (head == nullptr) {
        return;
    }
    fathermap->emplace(head->left, head);
    fathermap->emplace(head->right, head);
    process(head->left , fathermap);
    process(head->right, fathermap);
}

Node* lca(Node * head , Node* o1 , Node* o2) {
    unordered_map<Node*, Node*> fathermap;
    fathermap[head] = head;
    process(head, &fathermap);
    set<Node *> set1;
    set1.insert(o1);
    Node * cur = o1;
    while (cur != fathermap[cur]) {
        set1.insert(cur);
        cur = fathermap[cur];
    }
    set1.insert(cur);
    cur = o2;
    while (set1.find(cur) == set1.end()) {  // 如果当前节点不在 set1 里
        cur = fathermap[cur];               // 继续往上走
    }
    return cur;
}



int main() {
    Node* root = new Node(3);
    root->left = new Node(5);
    root->right = new Node(1);
    root->left->left = new Node(6);
    root->left->right = new Node(2);

    // 找 5 和 1 的公共祖先
    Node* ans = lca(root, root->left, root->right);
    cout << "最近公共祖先的值：" << ans->val << endl;

}