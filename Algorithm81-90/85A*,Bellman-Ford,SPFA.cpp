//
// Created by zhouyxuiang on 2026/5/24.
//
#include <iostream>
using namespace std;
//A*算法是一个点到目标点的最短距离
//增加当前点到终点的预估函数
//预估函数的要求 当前点到终点的距离 <= 当前点到终点的真实距离
//这是dj算法
class Solution1 {
public:
    int minDistance(vector<vector<int>> & grid,int startX,int startY,int targetX,int targetY) {
        int n = grid.size();
        int m = grid[0].size();
        vector<vector<int>> dist(n+1,vector<int>(m,INT_MAX));
        dist[startX][startY] = 1;
        vector<vector<bool>> visited(n,vector<bool>(m,false)) ;
        priority_queue<vector<int>,vector<vector<int>>,greater<vector<int>>> heap;
        heap.push({1,startX,startY});
        int move[5] = {-1,0,1,0,-1};
        while(!heap.empty()) {
            vector<int> cur = heap.top();
            heap.pop();
            int d = cur[0];
            int x = cur[1];
            int y = cur[2];
            if (visited[x][y]) {
                continue;
            }
            visited[x][y] = true;
            if (x == targetX && y == targetY) {
                return d;
            }
            for (int i = 0; i < 4; i++) {
                int nx = x + move[i];
                int ny = y + move[i+1];
                if (nx < n && nx >= 0 && ny >= 0 && ny < m && !visited[nx][ny] && d < dist[nx][ny]) {
                    dist[nx][ny] = d + 1;
                    heap.push({d + 1,nx,ny});
                }
            }
        }
        return -1;
    }
};
//A*算法的实现
class Solution2 {
    public:
    int h(int x, int y,int targetX, int targetY) {

        return abs(x - targetX) + abs(y - targetY);
    }
    int minDistace(vector<vector<int>>& grid ,int startX,int startY,int targetX,int targetY) {
        if (grid[targetX][targetY] == 0 || grid[startX][startY] == 0) return -1;
        int n = grid.size();
        int m = grid[0].size();
        vector<vector<int>> dist(n+1,vector<int>(m,INT_MAX));
        vector<vector<bool>> visited(n,vector<bool>(m,false));
        priority_queue<vector<int>,vector<vector<int>>,greater<vector<int>>> heap;
        heap.push({1 + h(startX,startY,targetX,targetY),startX,startY});
        vector<int> move = {-1,0,1,0,-1};
        dist[startX][startY] = 1;
        while(!heap.empty()) {
            vector<int> cur = heap.top();
            heap.pop();
            int x = cur[1];
            int y = cur[2];
            if (visited[x][y]) {
                continue;
            }
            if (x == targetX && y == targetY) {
                return dist[x][y];
            }
            for (int i = 0; i < 4; i++) {
                int nx = x + move[i];
                int ny = y + move[i+1];
                if (!visited[nx][ny] && dist[x][y] < dist[nx][ny] && nx < n && ny < m && nx >= 0 && ny >= 0 ) {
                    dist[nx][ny] = dist[x][y] + 1;
                    int f = h(nx,ny,targetX,targetY) + dist[nx][ny];
                    heap.push({f,nx,ny});
                }
            }
        }
        return -1;
    }
};
//Floyd算法
//可以解决权重为负的问题 不能有负环 就是无穷无尽的转这个圈
//保证最短距离的存在
class Solution3 {
    public:
    void floyd(vector<vector<int>>& dist, int n) {
        for(int bridge = 0; bridge < n; bridge++){
            for(int i = 0; i < n; i++){
                for(int j = 0; j < n; j++){
                    if(dist[i][bridge] != INT_MAX && dist[bridge][j] != INT_MAX && dist[i][j] > dist[i][bridge] + dist[bridge][j]){
                        dist[i][j] =dist[i][bridge] + dist[bridge][j];
                    }
                }
            }
        }
    }
};
//Bellman-Ford算法
//松弛就是能否让distance里的数值变小
//每一轮考察每条边 每条边都进行松弛操作 若干点的distance都变小
//至少让最短路的边数+1
//当无法松弛的时候 算法停止
class Solution4 {
    public:
    int BellmanFord(int n,vector<vector<int>>& flights,int start, int target,int k) {
        //n表示城市的数量 flghts有三个参数表示from to cost
        //k表示允许经过k个中转站
        vector<int> cur(n,INT_MAX);
        cur[start] = 0;
        for(int i = 0; i <= k; i++) {
            vector<int> next = cur;
            for (auto &edge:flights) {
                int from = edge[0];
                int to = edge[1];
                int cost = edge[2];
                if (cur[from] != INT_MAX) {
                    next[to] = min (next[to], cur[from] + cost);
                }
            }
            cur = next;
        }
        return cur[target] == INT_MAX ? -1 : cur[target];
    }
};


//SPFA优化



