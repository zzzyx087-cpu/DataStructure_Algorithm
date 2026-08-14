//
// Created by zhouyxuiang on 2026/4/17.
//
#include <iostream>

using namespace std;
int get(vector<vector<int>> &matrix, int i, int j);
void build(int n, int m, vector<vector<int>> &matrix);
int sum(vector<vector<int>> &matrix, int a, int b, int c, int d);

int largestBorderedSquare(vector<vector<int>> &matrix) {
    int n = matrix.size();
    if (n == 0) return 0;
    int m = matrix[0].size();

    build(n, m, matrix);

    // 整个矩阵没有 1
    if (sum(matrix, 0, 0, n-1, m-1) == 0)
        return 0;

    int ans = 1;

    for (int a = 0; a < n; ++a) {
        for (int b = 0; b < m; ++b) {

            for (int c = a + ans, d = b + ans, k = ans + 1;
                 c < n && d < m;
                 c++, d++, k++) {

                int total = sum(matrix, a, b, c, d);
                int inner = sum(matrix, a+1, b+1, c-1, d-1);
                int border = total - inner;

                if (border == 4 * (k-1)) {
                    ans = k;
                }
                 }
        }
    }

    return ans * ans;
}

// 构建前缀和
void build(int n, int m, vector<vector<int>> &matrix) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            matrix[i][j] += get(matrix, i, j-1)
                           + get(matrix, i-1, j)
                           - get(matrix, i-1, j-1);
        }
    }
}

// 计算 (a,b) -> (c,d) 的和
int sum(vector<vector<int>> &matrix, int a, int b, int c, int d) {
    if (a > c || b > d) return 0;
    return matrix[c][d]
         - get(matrix, c, b-1)
         - get(matrix, a-1, d)
         + get(matrix, a-1, b-1);
}

// 安全获取，越界返回 0
int get(vector<vector<int>> &matrix, int i, int j) {
    return (i < 0 || j < 0) ? 0 : matrix[i][j];
}
//2.二维差分
//原始的二维数组假设是n*m 在外围用0圈起来
//左 + 上 - 左上 + 自己
int n1,m1;
vector<vector<int>> diff(n1+2,vector<int>(m1+2,0));
void expand(const vector<vector<int>> &nums) {
    int n = nums.size();
    int m = nums[0].size();
    diff.assign(n+2, vector<int>(m+2,0));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            diff[i][j] = nums[i-1][j-1];
        }
    }
}
void add(int a, int b, int d ,int c,int k) {
    a++,b++,c++,d++;
    diff[a][b] += k;
    diff[c+1][b] -= k;
    diff[c+1][d+1] += k;
    diff[a][d+1] -= k;
}
//二维差分还原
void build() {
    for (int i = 1; i <= n1; i++) {
        for (int j = 1; j <= m1; j++) {
            diff[i][j] += diff[i - 1][j]
            + diff[i][j - 1]
            - diff[i - 1][j - 1];
        }
    }
}
//给一个二维矩阵
//在有0的位置贴上邮票

//判断能不能贴的方法
//在原始矩阵里算累加和大不大于1
void build(vector<vector<int>> &m);
int sumRegion(vector<vector<int>> &arr, int a , int b, int c ,int d);
bool Stamp(vector<vector<int>> &grid, int h ,int w) {
    //生成原始矩阵的前缀和数组 sum
    int n = grid.size();
    int m = grid[0].size();
    vector<vector<int>> sum(n+1, vector<int>(m+1));
    for (int i = 0 ;i < n; i++) {
        for (int j = 0;j < m; j++) {
            sum[i+1][j+1] = grid[i][j];
        }
    }
    build(sum);
    //二维差分数组
    vector<vector<int>> diff(n+2,vector<int>(m+2,0));
    for (int a = 1, c = a + h - 1; c <= n; a++,c++) {
        for (int b = 1, d = b + w - 1; d <= m; b++,d++) {
            if (sumRegion(sum,a,b,c,d) == 0) {
                add(diff,a,b,c,d);
            }
        }
    }
    //验证是不是所有的都被覆盖
    for (int i = 0;i < n;i++) {
        for (int j = 0 ; j < m; j++) {
            if (grid[i][j] == 0 && diff[i+1][j+1] == 0) {
                return false;
            }
        }
    }
    return true;
}
//二维前缀和数组的构建

void build(vector<vector<int>> &arr) {
    int n = arr.size() - 1;
    int m = arr[0].size() - 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            arr[i][j] += arr[i-1][j] + arr[i][j-1] - arr[i-1][j-1];
        }
    }
}
//二维前缀和查询
int sumRegion(vector<vector<int>> &arr, int a , int b, int c ,int d) {
    return arr[c][d] - arr[a-1][d] - arr[c][b-1] + arr[a-1][b-1];

}
add(vector<vector<int>> &diff, int a, int b, int c, int d) -> void {
    diff[a][b] += 1;
    diff[c + 1][b] -= 1;
    diff[a][d + 1] -= 1;
    diff[c + 1][d + 1] += 1;
}

//完美的邮票问题
class Solution {
public:
    bool possibleToStamp(vector<vector<int>>& grid, int h, int w) {
        int n = grid.size();
        int m = grid[0].size();

        //构建前缀和数组
        vector<vector<int>> sum(n+1, vector<int>(m+1,0));
        for (int i=0; i<n; i++) {
            for (int j=0; j<m; j++) {
                //sum[i+1][j+1] 表示:从左上角 (0,0) 一直到 (i,j) 的所有数字总和
                sum[i+1][j+1] = grid[i][j]
                                + sum[i][j+1]
                                + sum[i+1][j]
                                - sum[i][j];
            }
        }
        vector<vector<int>> diff(n + 2, vector<int>(m + 2, 0));
        //遍历所有能贴邮票的左上角
        for (int i = 0; i + h <= n; i++) {
            for (int j = 0; j + w<= m; j++) {
                //右下角的坐标
                //计算邮票的右下角
                int x2 = i + h - 1;//会覆盖h行 第i行都会覆盖所以-1
                int y2 = j + w - 1;
                //求矩形的和 看能不能贴
                //sum数组是从1开始存的
                int total = sum[x2+1][y2+1]
                          - sum[i][y2+1]
                          - sum[x2+1][j]
                          + sum[i][j];
                if (total == 0) {
                    // 二维差分打标记
                    diff[i][j]++;
                    diff[i][y2+1]--;
                    diff[x2+1][j]--;
                    diff[x2+1][y2+1]++;
                }
            }
        }
        //对diff数组做前缀和得到覆盖次数
        vector<vector<int>> cover(n, vector<int>(m, 0));
        cover[0][0] = diff[0][0];
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (i > 0) cover[i][j] += cover[i-1][j];
                if (j > 0) cover[i][j] += cover[i][j-1];
                if (i>0 && j>0) cover[i][j] -= cover[i-1][j-1];
                cover[i][j] += diff[i][j];
                if (grid[i][j] == 0 && cover[i][j] == 0) {
                    return false;
                }
            }
        }

    }
};
//最大幸福场
//xL = x * 2 - r
//xR = x * 2 + r
//yD = y * 2 - r
//yU = Y * 2 + r


