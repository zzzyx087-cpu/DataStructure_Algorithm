//
// Created by zhouyxuiang on 2026/3/19.
//
#include <iostream>
using namespace std;

struct Node {
    int value;
    Node* left;
    Node* right;
    Node (int x): value(x) , left(nullptr) , right(nullptr) {}
};
//递归 先序
void preOrderRecur(Node * root) {
    if(root == nullptr) return;
    cout << root->value << " ";
    preOrderRecur(root->left);
    preOrderRecur(root->right);
}
//递归 中序
void inOrderRecur(Node * root) {
    if(root == nullptr) return;
    inOrderRecur(root->left);
    cout << root->value << " ";
    inOrderRecur(root->right);
}
//递归 后序
void postOrderRecur(Node * root) {
    if(root == nullptr) return;
    postOrderRecur(root->left);
    postOrderRecur(root->right);
    cout << root->value << " ";
}
//非递归 先序
void preOrder(Node * root) {
    if (root == nullptr) return;
    stack <Node*> s;
    s.push(root);
    while (!s.empty()) {
        root = s.top();
        cout << s.top()->value << " ";
        s.pop();
        if (root -> right != nullptr) s.push(root -> right);
        if (root -> left != nullptr)  s.push(root -> left);
    }
}
//非递归 中序
void inOrder(Node * root) {
    stack <Node*> s;
    while (!s.empty() || root != nullptr) {
        if (root != nullptr) {
            s.push(root);
            root = root->left;
        }else {
            root = s.top();
            s.pop();
            cout << root->value << " ";
            root = root->right;
        }
    }
    cout << endl;
}
//非递归 后序
void postOrder(Node * root) {
    if (root == nullptr) return;
    stack <Node*> s1;
    stack <Node*> s2;
    s1.push(root);
    while (!s1.empty()) {
        root = s1.top();
        s1.pop();
        s2.push(root);
        if (root -> left != nullptr) s1.push(root -> left);
        if (root -> right != nullptr) s1.push(root -> right);
    }
    while (!s2.empty()) {
        cout << s2.top()->value << " ";
        s2.pop();
    }
}
int main() {
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->left = new Node(6);
    cout <<"============递归==============" << endl;
    cout << "先序遍历";
    preOrderRecur(root);
    cout << endl;
    cout << "中序遍历" ;
    inOrderRecur(root);
    cout << endl;
    cout << "后序遍历" ;
    postOrderRecur(root);
    cout << endl;
    cout <<"============非递归==============" << endl;
    cout << "先序遍历";
    preOrder(root);
    cout << "中序遍历" ;
    postOrder(root);
    cout << "后序遍历" ;
    inOrder(root);
}




