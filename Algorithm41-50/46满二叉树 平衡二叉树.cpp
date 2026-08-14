//
// Created by zhouyxuiang on 2026/3/20.
//
//
#include<iostream>
using namespace std;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};
//判断满二叉树
//满足N = 2 ^ c - 1

struct Info {
    int height;
    int nodes;

    Info(int height, int nodes) : height(height), nodes(nodes) {}
};
Info process2(TreeNode * root) {
    if (root == nullptr) return Info(0,0);
    Info leftData = process2(root->left);
    Info rightData = process2(root->right);

    int height = max(leftData.height, rightData.height) + 1;
    int nodes = leftData.nodes + rightData.nodes + 1;

    return Info(height, nodes);
}
bool isF(TreeNode * root ) {
    if (root == nullptr) return true;
    Info data = process2(root);
    return data.nodes == (1 << data.height - 1);
}
//判断平衡二叉树|左高 - 右高| <= 1
//左边是否平衡——求高度 右边是否平衡——求高度
//定义返回类型 包含是否平衡 + 高度

struct ReturnType {
    bool isBalanced;
    int height;
    //构造函数
    ReturnType(bool isB, int ht) : isBalanced(isB), height(ht) {}
};
ReturnType process(TreeNode* root);
bool isBalanced(TreeNode* root) {
    return process(root).isBalanced;
}
ReturnType process(TreeNode* root) {
    if (root == nullptr)
        return ReturnType(true, 0);
    ReturnType left = process(root->left);
    ReturnType right = process(root->right);
    int height = max(left.height, right.height) + 1;
    bool isBalanced = left.isBalanced && right.isBalanced && abs(left.height - right.height) <= 1;
    return  ReturnType(isBalanced, height);
}
int main() {
    // 构建一棵平衡二叉树
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode (2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);

    cout << boolalpha << isBalanced(root)<< endl;
    // 输出 true

}