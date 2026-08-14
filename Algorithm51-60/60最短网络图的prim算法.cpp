//
// Created by zhouyxuiang on 2026/3/24.
//
#include <iostream>
#include <cstring>
using namespace std;
const int N = 110;
const int INF = 0x3f3f3f3f;//无穷大的数字
int n ;//表示农场的数量
int a[N][N]; //声明一个二维数组 表示农场与农场之间的距离
int dis[N];// 每个点到生成树的最短距离
bool vis[N];
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> a[i][j];
        }
    }
    //初始化 把1号点开始的数字填入dis数组中
    for (int i = 1; i <= n; i++) {
        dis[i] = a[1][i];
    }
    vis[1] = true;//1连好了
    int ans = 0;
    //核心循环 要连接n-1条边 循环 n-1次
    for (int i = 1; i < n; i++) {
        //找到没进来 以及 最近的点
        int min_len = INF;
        int pos = 0;
        for (int j = 1; j <= n; j++) {
            if (!vis[j] && dis[j] < min_len) {
                min_len = dis[j];
                pos = j;
            }
        }
        //连接点
        vis[pos] = true;
        ans += min_len;
        //用刚进来的点 更新距离
        for (int j = 1;j <= n; j++) {
            if (!vis[j] && a[pos][j] < dis[j]) {
                dis[j] = a[pos][j];
            }
        }
    }
}

