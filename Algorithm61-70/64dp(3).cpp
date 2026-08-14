//
// Created by zhouyxuiang on 2026/3/30.
//
#include <iostream>
using namespace std;
//过河卒
//定义一个障碍物的数组
int x , y;
//棋盘大小是 21x21（从0到20），因为坐标范围是 0~20
//一个二维数组标记障碍物（马的控制点）
bool blocked[21][21];//标记障碍物

//一个二维数组做DP（存储路径数）
long long dp[21][21];
int main() {
    //输入棋盘大小（n,m） 马的坐标(horseX,horseY)
    int n , m , horseX , horseY;
    cin >> n >> m >> horseX >> horseY;
    // 马的8个移动方向 + 马本身的位置
    // dx[i]和dy[i]配合使用，表示马可以跳到的9个点的坐标偏移
    int dx[] = {0,-2,-1,1,2,2,1,-1,-2};
    int dy[] = {0,1,2,2,1,-1,-2,-2,-1};
    //标记所有障碍物
    for (int i = 0; i < 9; i++) {
        int bx = horseX + dx[i];   // 计算当前要标记的点的x坐标
        int by = horseY + dy[i];   // 计算当前要标记的点的y坐标
        if (bx >= 0 && bx < m && by >= 0 && by < m) {
            blocked[bx][by] = true;//标记为障碍物
        }
    }
    // 如果起点(0,0)本身就是障碍物，直接输出0
    // 因为起点被马控制了，卒连出发都做不到，所以路径数为0
    if (blocked[0][0]) {
        cout << 0 << endl;
        return 0;  // 程序结束
    }
    dp[0][0] = 1;// DP初始化：起点到起点的路径数为1（只有一条路径：原地不动）
    //开始填入表格 从上到下 从左到右
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            if (i == 0 && j == 0) continue;
            if (blocked[i][j]) {
                dp[i][j] = 0;
                continue;
            }
            // 状态转移：从上方和左方转移过来
            // 因为卒只能向下或向右走，所以到达(i,j)只能从(i-1,j)下来，或从(i,j-1)过来
            // 计算从上方来的路径数：如果i>0（存在上一行），则取dp[i-1][j]的值，否则为0
            long long formTop = (i > 0) ? dp[i - 1][j] : 0;
            long long formLeft = (j > 0) ? dp[i][j - 1] : 0;
            dp[i][j] = formTop + formLeft;
        }
    }
    cout << dp[n][m] << endl;
}