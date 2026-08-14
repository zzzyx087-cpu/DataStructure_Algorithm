//
// Created by zhouyxuiang on 2026/4/28.
//
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <unordered_set>
#include <deque>
#include <list>
using namespace std;
//bfs特点是逐层扩散 从源头到目标点扩了几层就是level 表示最短的路
//只能用于任意两个节点的距离相同

//地图分析
//每个单元格是0 和 1
//求距离所有陆地最远的海洋
//多元的BFS
//用1去扩2 2扩3 3扩4 4扩...

class Solution1 {
public:
    const int MAXN = 101;
    const int MAXM = 101;
    int queue_[MAXN * MAXM][2];
    int l, r;
    bool visited[MAXN][MAXM];
    int move_[5] = {-1, 0, 1, 0, -1}; // 上、右、下、左
    int maxDistance(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
         l = 0, r = 0;
        memset(visited , 0 , sizeof(visited));
        //所有为1的进入队列
        int seas = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (grid[i][j] == 1) {
                    queue_[r][0] = i;
                    queue_[r][1] = j;
                    r++;
                    visited[i][j] = true;
                }else {
                    visited[i][j] = false;
                    seas++;
                }
            }
        }
        //表示全是陆地或者海洋
        if (seas == n * m || seas == 0) return -1;

        int level = 1;

        while (l <= r) {
            level++;
            //当前队列的元素
            //size次弹出
           int size = r - l;
            for (int k = 0,x,y,nx,ny;k < size; ++k) {
                x = queue_[l][0];
                y = queue_[l++][1];
                for (int i = 0; i < 4; ++i) {
                    int nx = x + move_[i];
                    int ny = y + move_[i + 1];
                    if (nx >= 0 && nx < n && ny >= 0 && ny < m && !visited[nx][ny]) {
                        visited[nx][ny] = true;
                        queue_[l][0] = nx;
                        queue_[l++][1] = ny;
                    }
                }
            }
        }
        return level - 1;
    }
};
//bfs减枝
//贴纸拼词
//返回使用的最小张数
class Solution2 {
public:
    vector<vector<string>> graph;//一个装有26个字母的贴纸仓库 graph[0]里面是包含字母a的贴纸
    unordered_set<string> visited;//记录已经处理过的残缺的字符串 哈希表

    //字符串排序
    string sortStr(string s) {
        sort(s.begin(), s.end());
        return s;
    }
    //用贴纸消去字符 返回剩余的字符串
    string getNext(string cur,string sticker) {
        //前提是cur 和1sticker已经被拍排过序了
        string res;
        int i = 0 , j = 0;
        while (i < cur.length() && j < sticker.length()) {
          if (cur[i] < sticker[j]) {
              res += cur[i++];
          }else if (cur[i] > sticker[j]) {//贴纸的字符太小了 贴纸指针往前走看下一个
              j++;
          }else {
              i++;
              j++;
          }
        }
        return res;
    }
    int minStickers(vector<string>& stickers, string target) {
        graph.assign(26,vector<string>());
        visited.clear();
        //将贴纸排序 + 字母存入graph
        for (string &s : stickers) {
            s = sortStr(s);
            for (int i = 0; i < s.size(); ++i) {
                if (i == 0 || s[i] != s[i - 1]) {
                    graph[s[i] - 'a'].push_back(s);
                }
            }
        }
        //BFS初始化
        target = sortStr(target);
        queue<string> q;
        q.push(target);
        int level = 0;
        while (!q.empty()) {
            int size = q.size();
            for (int i = 0; i < size; ++i) {
                string cur = q.front();q.pop();
                int c = cur[0] - 'a';
                for (string& stk : graph[c]) {
                    //用贴纸来消去字符
                    string nextStr= getNext(cur,stk);
                    if (nextStr.empty()) return level + 1;

                    //没访问过加入队列
                    //就是一些贴纸消不掉这个字符
                    if (visited.find(nextStr) == visited.end()) {
                        visited.insert(nextStr);
                        q.push(nextStr);
                    }
                    //取出来的顺序：
                    //0 张 → 1 张 → 2 张 → 3 张
                }
            }

            level++;
        }
        return -1;
    }
};
//01bfs求单源的最短路径
//引入了双端队列
//权重只有0和1两种值 求源点到目点的最短距离
//准备一个distance表值先设置为正无穷
//准备一个双端队列

//头部弹出X 返回distance[x]表示远点到目标点的最短距离
//权为0的边 插到队首
//权为1的边 插到对尾
//重复步骤
//处理弹出来的点的边 就算重复也要进入
//边没了 弹出
//想当于有几个可以改变的机会 因为可能一个为0一个为1
class Solution3 {
public:
    int minimumObstacles(vector<vector<int>> &grid) {
        const int move[] = {-1, 0, 1, 0, -1};
        //只用一个数量为5的就能完成四个方向的探索
        int m = grid.size();
        int n = grid[0].size();

        // 初始化 distance 数组，默认填充 INT_MAX（相当于 Integer.MAX_VALUE）
        vector<vector<int>> distance(m, vector<int>(n, INT_MAX));
        distance[0][0] = 0;

        // C++ 中的双端队列，存储 {x, y} 坐标对
        deque<pair<int, int>> dq;
        dq.push_front({0, 0});

        while (!dq.empty()) {
            // 弹出队头元素 (C++17 结构化绑定语法)
            int x = dq.front().first;
            int y = dq.front().second;
            dq.pop_front();

            // 如果到达右下角，直接返回最短距离
            if (x == m - 1 && y == n - 1) {
                return distance[x][y];
            }

            // 遍历四个方向
            for (int i = 0; i < 4; i++) {
                int nx = x + move[i];
                int ny = y + move[i + 1];

                // 越界检查
                if (nx >= 0 && nx < m && ny >= 0 && ny < n && distance[x][y] + grid[nx][ny] < distance[nx][ny]) {
                    // 更新最短距离
                    distance[nx][ny] = distance[x][y] + grid[nx][ny];

                    //核心逻辑
                    //grid[][]就相当于是边它的值就是边的权值
                    if (grid[nx][ny] == 0) {
                        dq.push_front({nx, ny}); // 权重为0，加到队头
                    } else {
                        dq.push_back({nx, ny});  // 权重为1，加到队尾
                    }
                }
            }
        }

        return 0; // 正常情况下由于题目保证有解，不会走到这里
    }
};
//给一个grid每个格子里面有一个方向
//每个格子可以改一次 花费1 求最小花费找到有效路径
class Solution4 {
    public:
    int minCost(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        const int move[5][2] = {{0,0},
            {0,1},
        {0,-1},
        {1,0},
        {-1,0}};
//  到每个点的最小距离
        vector<vector<int>> distance(m,vector<int>(n,INT_MAX));
        deque<pair<int, int>> dq;
        while (!dq.empty()) {
            int x = dq.front().first;
            int y = dq.front().second;
            dq.pop_front();
            if (x == m - 1 && y == n - 1) {
                return distance[x][y];
            }
            //开始往四个方向走
            //1 右 2 左 3 下 4 上
            for (int i = 0; i < 4; i++) {
                int nx = x + move[i][0];
                int ny = y + move[i][1];
                //越界检查
                if (nx >= 0 && nx < m && ny >= 0 && ny < n ) {
                    //开始算权值是否跟指着的方向一样
                    int weight = (grid[x][y] == i) ? 0 : 1;
                    if (distance[nx][ny] > distance[x][y] + weight) {
                        distance[nx][ny] = distance[x][y] + weight;
                        if (weight == 0) {
                            dq.push_front({nx, ny});
                        }else {
                            dq.push_back({nx, ny});
                        }
                    }
                }
            }
        }
        return distance[m - 1][m - 1];
    }
};
//二维接雨水
//给一个二维数组表示格子的高度
//边缘处的格子 放进优先级队列 小根堆里 第三个格子
//把不是最高的点先找出来
class Solution5 {
    public:
    int trapRainWater(vector<vector<int>> heightMap) {
        if (heightMap.size() == 0
    || heightMap[0].size() == 0) {
            return 0;
        }
        int m = heightMap.size();
        int n = heightMap[0].size();
        //无法形成水坑
        if (m <= 2 && n <= 2) {
            return 0;
        }
        priority_queue<vector<int>,vector<vector<int>>, greater<vector<int>>> minHeap;
        //把高度放在第一个位置
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == 0 || i == m - 1 || j == 0 || j == n - 1) {
                    minHeap.push({heightMap[i][j], i, j});
                    visited[i][j] = true;
                }
            }
        }
        int water_sum = 0;
        const int dirs[] = {-1,0,1,0,-1};
        while (!minHeap.empty()) {
            auto current = minHeap.top();
            minHeap.pop();
            int curr_h = current[0];
            int curr_r = current[1];
            int curr_c = current[2];

            //探索这个的四个邻居
            for (int i = 0; i < 4; i++) {
                int nx = current[0] + dirs[i];
                int ny = current[1] + dirs[i + 1];
                //邻居的水位
                if (nx >= 0 && nx < m && ny >= 0 && ny < n && !visited[nx][ny]) {
                    visited[nx][ny] = true;
                    int neighbor_h = heightMap[nx][ny];
                    //能够积水
                    if (neighbor_h < curr_h) {
                        water_sum += curr_h - neighbor_h;
                    }
                    minHeap.push({max(curr_h, neighbor_h), nx, ny});
                }
            }
        }
    return water_sum;
    }
};
//bfs dfs结合
//字词接龙
//给我一个endword和beginword
//还有必须存在在这个list里转化的word

class Solution6 {
public:
    // 全局变量（对应 Java 的 static 成员）
    unordered_set<string> dict;//判断一个词存不存在
    //需要这两个set的原因是要求最短路径 不能回头搜
    unordered_set<string> curLevel;
    unordered_set<string> nextLevel;
    //拼成一个有向无环图
    unordered_map<string, vector<string>> graph;
    list<string> path;
    vector<vector<string>> ans;

    void build(const string& beginWord, vector<string>& wordList) {
        dict = unordered_set<string>(wordList.begin(), wordList.end());
        graph.clear();
        ans.clear();
        curLevel.clear();
        nextLevel.clear();
    }

    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        build(beginWord, wordList);

        // 初始检查
        if (dict.find(endWord) == dict.end()) {
            return ans;
        }

        if (bfs(beginWord, endWord)) {
            // 注意：截图思路是从 end 往 begin 搜
            dfs(endWord, beginWord);
        }

        return ans;
    }
//bfs的逻辑是根据bfs的特性 修到的路一定是路径最短的
    bool bfs(string begin, string end) {
        bool find = false;
        curLevel.insert(begin);

        while (!curLevel.empty()) {

            // 每一层处理完后，从字典中删掉这一层，保证“最短”且不往回走
            //一层一层往外扩
            for (const string& w : curLevel) {
                dict.erase(w);
            }
            //开始尝试变换 改变每一个字母
            for (const string& word : curLevel) {
                string w = word;
                for (int i = 0; i < w.length(); i++) {
                    char old = w[i];
                    for (char ch = 'a'; ch <= 'z'; ch++) {
                        w[i] = ch;
                        if (dict.count(w) && w != word) {//新词合法
                            if (w == end) find = true;
                            // 关键逻辑：建立反向图 记下这个新词w是从父亲节点word变来的
                            graph[w].push_back(word);
                            //来确认这一层只有这一个单词
                            if (nextLevel.find(w) == nextLevel.end()) {
                                nextLevel.insert(w);
                            }
                        }
                    }
                    //变回来 尝试下一个字母
                    w[i] = old;
                }
            }

            if (find) {
                return true;
            } else {
                curLevel = nextLevel;
                nextLevel.clear();
            }
        }
        return false;
    }
    //拿着地图 从起点走到终点
    void dfs(string word, string aim) {
        // 对应 Java 的 path.addFirst(word)
        path.push_back(word);
        if (word == aim) {
            ans.push_back(vector<string>(path.begin(), path.end()));
        }else if (graph.find(word) != graph.end()) {
            for (const string& w : graph[word]) {
                dfs(w, aim);
            }
        }
        //一个词既不是起点并且在graph里也找不到它的爹


        //两种情况都会弹出来
        //第一种是这条路可以到达 也会回溯一次看倒数第二个单词还有没有其他的路径

        //第二种是走到最后一个单词的时候是一个死胡同
        //一层一层的回溯发现都不行 一直触发pop
        path.pop_front();
    }
};


