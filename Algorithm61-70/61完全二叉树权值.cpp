//
// Created by zhouyxuiang on 2026/3/25.
//
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;
struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int x) : data(x) , left(nullptr) , right(nullptr) {}
};
//建树
Node* buildTree(vector<int> &v) {
    if (v.size() == 0) return nullptr;

    Node* root = new Node(v[0]);
    queue<Node*> q;
    q.push(root);
    int i = 1;
    int n = v.size();
    while (!q.empty()) {
        Node* curr = q.front();
        q.pop();
        if (i < n) {
            curr->right = new Node(v[i]);
            q.push(curr->right);
            i++;
        }
        if (i < n) {
            curr->left = new Node(v[i]);
            q.push(curr->left);
            i++;
        }
    }
    return root;
}
int n , a, sum , ans ,dep = 1, Max = -1e9;

int main() {
//输入的是一个数组
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a;
        sum += a;
        if (i == (1 << dep) - 1 || i == n) {//(1 << dep) = 2^dep
            if (sum > Max) {
                Max = sum;
                ans = dep;
            }
            dep++;
            sum = 0;
        }
    }
    //特殊判断叶子节点
    cout << ans << endl;
    cout << Max << endl;

}