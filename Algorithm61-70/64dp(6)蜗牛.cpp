//
// Created by zhouyxuiang on 2026/4/8.
//
//在一根数轴上，有 n 根杆子。有一只蜗牛需要从第一根杆子的起点（位置 0）出发，到达第 n 根杆子的终点（位置 x_n）。蜗牛有两种移动方式：
//在地面上水平移动：从一根杆子的底部沿着地面走到另一根杆子的底部。速度：1单位距离/秒。
//在杆子之间传送：每根杆子上有一个传送门（位于特定高度 a_i）和一个接收门（位于特定高度 b_i）。蜗牛可以从第 i 根杆子的 a_i 高度传送到第 i+1 根杆子的 b_{i+1} 高度，传送本身不消耗时间，但从 a_i 爬到 a_i 位置需要时间。同时，也可以选择不使用传送，继续向上或向下爬。
//目标是求出从起点到终点的最短时间。
//输入示例
//3
//1 10 11
//1 2
//1 2
//dp动态规划
//对于每根杆子只关心两个位置 dp[i][0]到达第i根底部最短时间
//dp[i][1]到达i根杆子传送们高度a[i]的最短时间
//到达dp[i-1][0]有两种方式
//从上一根爬 以及 上一根传送门刀上一根顶部 在爬过来
#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<double> x(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> x[i];
    }

    vector<double> a(n + 1, 0), b(n + 1, 0);
    for (int i = 1; i < n; ++i) {
        cin >> a[i] >> b[i + 1];
    }

    vector<vector<double>> dp(n + 1, vector<double>(2, 1e18));

    dp[1][0] = x[1];
    if (n >= 2) {
        dp[1][1] = x[1] + a[1] / 0.7;
    }

    for (int i = 2; i <= n; ++i) {
        double dist = x[i] - x[i-1];//两根杆子的距离

        // 到达底部:3 种方式
        double way1 = dp[i-1][0] + dist;
        double way2 = dp[i-1][1] + a[i-1]/1.3 + dist;
        double way3 = dp[i-1][1] + b[i]/1.3;
        dp[i][0] = min({way1, way2, way3});

        // 到达传送门 两种方式
        //一种是从接受门爬过来
        //第二种是上一个根底部爬过来
        double w1 = dp[i-1][0] + dist + a[i]/0.7;
        double h = fabs(a[i] - b[i]);
        double sp = (b[i] > a[i]) ? 1.3 : 0.7;
        double w2 = dp[i-1][1] + h / sp;
        dp[i][1] = min(w1, w2);
    }

    // 最终答案只需要底部！第n根没有传送门！
    cout << fixed << setprecision(1) << dp[n][0] << endl;
}