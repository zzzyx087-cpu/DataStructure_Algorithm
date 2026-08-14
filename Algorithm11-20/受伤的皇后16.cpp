#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int res = 0; // 统计方案数
int n;

// 检查第row行col列放皇后是否合法
bool is_valid(vector<vector<bool>>& board, int row, int col) {
    // 检查列冲突（遍历所有行，看同一列是否有皇后）
    for (int i = 0; i < row; ++i) {
        if (board[i][col]) return false;
    }

    // 检查斜线冲突（遍历所有已放皇后的位置）
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < n; ++j) {
            if (board[i][j]) { // 找到第i行的皇后位置(j)
                // 同45度斜线 且 行差<3 → 不合法
                if (abs(row - i) == abs(col - j) && abs(row - i) < 3) {
                    return false;
                }
            }
        }
    }
    return true;
}

// 回溯：处理第row行
void backtrack(vector<vector<bool>>& board, int row) {
    if (row == n) { // 所有行放完，方案+1
        res++;
        return;
    }

    // 尝试当前行所有列
    for (int col = 0; col < n; ++col) {
        if (is_valid(board, row, col)) {
            board[row][col] = true; // 放置皇后
            backtrack(board, row + 1); // 递归下一行
            board[row][col] = false; // 回溯：撤回皇后
        }
    }
}

int main() {
    cin >> n;
    // 初始化n×n棋盘，全部为false（无皇后）
    vector<vector<bool>> board(n, vector<bool>(n, false));
    backtrack(board, 0);
    cout << "合法方案数：" << res << endl;
    return 0;
}