//
// Created by zhouyxuiang on 2026/4/23.
//
#include <iostream>
using namespace std;
//由 1 和 0组成的二维网络 计算网格中岛的数量
class Solution1 {
    int numIslands(vector<vector<char>> &board) {
        int islands = 0;
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[0].size(); j++) {
                if (board[i][j] == '1') {
                    islands++;
                    dfs(board, i, j);
                }
            }
        }
        return islands;
    }
    void dfs(vector<vector<char>> &board, int i ,int j) {
        if (i < 0|| i == board.size() || j < 0|| j == board[0].size() || board[i][j] != '1')
            return;//代码直接结束
        //没有return 说名一定是1
        board[i][j] = '0';
        dfs(board, i-1, j);
        dfs(board, i+1, j);
        dfs(board, i, j-1);
        dfs(board, i, j+1);
    }
    //一个格子最多被访问4次
    //时间复杂度O(n * m)

};
class Solution2 {
    //给一个二维矩阵 X 和 O
    //如果有一个O被完全围绕就改成X 没有被围绕就不改
    public:
    void solve(vector<vector<char>> &board) {
        int n = board.size();
        int m = board[0].size();
        //处理上下两条边所有的'O'

        for (int j = 0;j < m;j++) {
            if (board[0][j] == '0') {
                dfs(board,n,m,0,j);
            }
            if (board[n-1][j] == '0') {
                dfs(board,n,m,n-1,j);
            }
        }
        //然后处理左右两条边
        for (int i = 0;i < n-1;i++) {
            if (board[i][0] == '0') {
                dfs(board,n,m,i,0);
            }
            if (board[i][m-1] == '0') {
                dfs(board,n,m,i,m-1);
            }
        }
        //最终的处理由于一些已经变成了F一些没有就把剩余的O变成X
        for (int i = 0;i < n;i++) {
            for (int j = 0;j < n;j++) {
                if (board[i][j] == '0') {
                    board[i][j] = 'X';
                }
                if (board[i][j] == 'F') {
                    board[i][j] = 'O';
                }
            }
        }

    }
    void dfs(vector<vector<char>> &board, int n , int m , int i ,int j) {
    //退出的条件 越界或者这个格子字符不是'O'
        if (i == -1 || i == n || j == m || j == -1|| board[i][j] != '0') {
            return;
        }
        board[i][j] = 'F';//标记为安全
        dfs(board,n,m,i+1,j);
        dfs(board,n,m,i-1,j);
        dfs(board,n,m,i,j-1);
        dfs(board,n,m,i,j+1);
    }

};
class Solution3 {
    public:


};
int main() {

}