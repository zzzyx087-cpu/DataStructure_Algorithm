//
// Created by zhouyxuiang on 2026/3/18.
//
#include <iostream>
using namespace std;
vector<int> pre, in;
vector<int> post;
void build(int root , int l , int r) {
    if (l > r) return;
    //1.找到根在中序的位置
    int mid = l;
    while (in[mid] != pre[root]) {
        mid++;
    }
    //然后找到了这个根
    build(root + 1 , l , r);
    build(root + (mid - l + 1), mid + 1 , r);
    post.push_back(pre[root]);
}

int main() {

}