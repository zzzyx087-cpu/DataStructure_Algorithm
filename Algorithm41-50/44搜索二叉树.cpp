//
// Created by zhouyxuiang on 2026/3/19.
//
#include <iostream>
#include <algorithm>
using namespace std;
//每一颗子树左数小右树大
//用中序遍历 一定是升序的
//没有重复值
//非递归 中序struct Node {
struct Node {
    int value;
    Node* left;
    Node* right;
    Node (int x): value(x) , left(nullptr) , right(nullptr) {}
};
// 树形DP返回结构体：是否是BST + 子树最小值 + 子树最大值
struct ReturnData {
  bool isBST;
  int min;   // 子树最小值
  int max;   // 子树最大值
  // 构造函数
  ReturnData(bool is, int mi, int ma) : isBST(is), min(mi), max(ma) {}
};

ReturnData process(Node* root) {
  // 空节点处理：空树视为BST，为了不影响min/max计算，返回极端值
  if (root == nullptr) {
    return ReturnData(true, INT_MAX, INT_MIN);
  }

  // 递归获取左右子树信息
  ReturnData leftData = process(root->left);
  ReturnData rightData = process(root->right);

  // 计算当前子树的min和max
  int minVal = min({root->value, leftData.min, rightData.min});
  int maxVal = max({root->value, leftData.max, rightData.max});

  // 默认当前是BST
  bool isBST = true;

  // 条件1：左子树不是BST 或 左子树最大值 >= 当前节点值 → 不是BST
  if (!leftData.isBST || leftData.max >= root->value) {
    isBST = false;
  }
  // 条件2：右子树不是BST 或 右子树最小值 <= 当前节点值 → 不是BST
  if (!rightData.isBST || rightData.min <= root->value) {
    isBST = false;
  }

  return ReturnData(isBST, minVal, maxVal);
}

// 对外接口
bool isBST(Node* root) {
  return process(root).isBST;
}

// ==================== 测试 main 函数 ====================
int main() {
  // 测试一棵合法BST
  Node* root = new Node(5);
  root->left = new Node(3);
  root->right = new Node(7);
  root->left->left = new Node(2);
  root->left->right = new Node(4);
  root->right->right = new Node(8);

  cout << boolalpha << isBST(root) << endl; // 输出 true

  // 测试一棵非法BST（左子树最大值 >= 根节点）
  Node* badRoot = new Node(5);
  badRoot->left = new Node(6);
  cout << isBST(badRoot) << endl; // 输出 false

  return 0;
}