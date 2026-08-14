//
// Created by zhouyxuiang on 2026/5/9.
//
#include <cassert>
#include <iostream>
using namespace std;
//Dijkstra算法
//准备小根堆 一个distance visited数组
//如果已经弹出去了 就visited为false 没弹出去就为true
//把最上面的先弹出去 重复处理 如果在堆里且距离会变短 就改变数组里的数据
//O(m *logm)时间复杂度
class Solution1 {
public:
    //n表示点的个数 s表示起点
    int networkDelayTime(vector<vector<int>>& times, int n, int s) {
        //1.动态建图
        //graph[u]存储的是{v,w}u到v的权重是w
        vector<vector<pair<int,int>>> graph(n+1);

        for (auto &edge : times) {
            graph[edge[0]].push_back({edge[1], edge[2]});
        }
        //2.距离数组初始化无穷大
        vector<int> distance(n+1,INT_MAX);
        //3.访问标记数组
        vector<bool> visited(n+1,false);
        //4.优先队列 小根堆
        // 格式：priority_queue<数据类型, 容器类型, 比较规则>
        //vector<pair<int,int>>表示存储的容器的类型
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> heap;
        //先按照first排序 再按照second排序
        heap.push({0,s});
        while (!heap.empty()) {
            //弹出距离最小的点
            int u = heap.top().second;
            int d = heap.top().first;
            heap.pop();
            if (visited[u]) continue;
            visited[u] = true;
            //遍历u的所有邻居
            for (auto &edge : graph[u]) {
                int v = edge.first;
                int w = edge.second;
                if (!visited[v] && distance[u] + w < distance[v]) {
                    distance[v] = distance[u] + w;
                    heap.push({distance[v],v});
                }
            }
        }
        int ans = INT_MAX;
        //找到距离里面的最大值
        for (int i = 1; i <= n; i++) {
            if (distance[i] == INT_MAX) {
                return -1;//说明有些点无法到达
            }
            ans = max(ans , distance[i]);
        }
        return ans;
    }
};
//反向索引堆实现算法
//弹出一个用-2 没进来的用-1 正在是在0 1 2 3 4...
//在0位置弹出 让最后一条记录在最上面
//准备好反向索引堆
//根据原点到当前点的距离组织的小根堆
//a.新增记录 b.当原点到X的距离更新时进行堆的调整
//c.x一旦弹出以后忽略X d.弹出堆顶的记录(u,原点到u的距离)
//加入反向索引堆 过程开始
class Solution2 {
public:
    struct IndexedMinHeap {
        vector<pair<int,int>> heap;
        vector<int> pos;
        int size;
        IndexedMinHeap(int n) {
            heap.reserve(n + 1);
            pos.assign(n + 1, -1); // 初始时节点不在堆中
            size = 0;
        }
        bool empty() const {
            return size == 0;
        }

        // 交换堆中两个元素，并更新pos数组
        void swap(int i, int j) {
            std::swap(heap[i], heap[j]);
            pos[heap[i].second] = i;
            pos[heap[j].second] = j;
        }
        void up(int i) {
            while (i > 1) {
                int p = i / 2;
                if (heap[p].first <= heap[i].first) break;
                swap(p, i);
                i = p;
            }
        }
        void down(int i) {
            while (true) {
                int left = 2 * i;
                int right = 2 * i + 1;
                int smallest = i;
                if (left <= size && heap[left].first < heap[smallest].first)
                    smallest = left;
                if (right <= size && heap[right].first < heap[smallest].first)
                    smallest = right;
                if (smallest == i) break;
                swap(i, smallest);
                i = smallest;
            }
        }
        // 插入/更新节点：如果节点不在堆中则插入，否则更新距离并调整
        void push_or_update(int node, int dist) {
            if (pos[node] == -1) {
                // 节点不在堆中：新增
                heap.emplace_back(dist, node);
                pos[node] = ++size;
                up(size);
            } else {
                // 节点已在堆中：更新距离并调整
                int idx = pos[node];
                if (dist < heap[idx].first) {
                    heap[idx].first = dist;
                    up(idx);
                }
            }
        }
        pair<int, int> pop() {
            assert(!empty());
            pair<int, int> top = heap[1];
            // 把最后一个元素移到堆顶，然后下滤
            swap(1, size);
            pos[top.second] = -1; // 标记节点已不在堆中
            size--;
            down(1);
            return top;
        }
    };
    // Dijkstra 主函数
    vector<int> dijkstra(int n, int s, const vector<vector<pair<int, int>>>& g) {
        vector<int> dist(n + 1, INT_MAX);
        vector<bool> done(n + 1, false);
        IndexedMinHeap heap(n);

        dist[s] = 0;
        heap.push_or_update(s, 0); // 步骤2：起点入堆

        while (!heap.empty()) {
            auto [d, u] = heap.pop(); // 步骤3：弹出堆顶
            if (done[u]) continue;    // 节点已处理过，跳过
            done[u] = true;

            for (auto [v, w] : g[u]) { // 遍历u的所有邻边
                if (!done[v] && dist[v] > d + w) {
                    dist[v] = d + w;
                    heap.push_or_update(v, dist[v]); // 更新/插入堆
                }
            }
        }
        return dist;
    }



};
class Solution3 {
//找相邻两个数值最小差值
public:
    int minimumeffortPath(vector<vector<int>>& heights) {
        int n = heights.size();
        int m = heights[0].size();
        //初始化距离数组 全部为最大值
        vector<vector<int>> distance(n,vector<int>(m,INT_MAX));
        // 访问标记数组
        vector<vector<bool>> visited(n, vector<bool>(m, false));
        int move_dir[] = {0,1,0,-1,0};
        //自定义比较规则
        auto cmp = [](const vector<int>& a, const vector<int>& b) {
            return a[2] > b[2];
        };
        priority_queue<vector<int>,vector<vector<int>>,decltype(cmp)> heap(cmp);
        distance[0][0] = 0;
        heap.push({0,0,0});
        while (!heap.empty()) {
            auto record = heap.top();
            heap.pop();

            int x = record[0];
            int y = record[1];
            int c = record[2];

            // 如果当前格子已经确定了最短路径，直接跳过
            if (visited[x][y]) {
                continue;
            }

            // 常见剪枝：发现终点直接返回，不用等队列全部清空
            if (x == n - 1 && y == m - 1) {
                return c;
            }

            // 标记当前格子已被访问
            visited[x][y] = true;

            // 遍历 4 个方向
            for (int i = 0; i < 4; ++i) {
                int nx = x + move_dir[i];
                int ny = y + move_dir[i + 1];

                // 边界检查以及未访问检查
                if (nx >= 0 && nx < n && ny >= 0 && ny < m && !visited[nx][ny]) {
                    // 当前路径到邻居格子的消耗：取【当前格子的总消耗】与【相邻格子高度差】的最大值
                    //保证不漏掉任何一条线路
                    int nc = max(c, abs(heights[x][y] - heights[nx][ny]));

                    // 如果算出的消耗比之前记录的更小，则更新并入堆
                    if (nc < distance[nx][ny]) {
                        distance[nx][ny] = nc;
                        heap.push({nx, ny, nc});
                    }
                }
            }
        }
        return -1;
    }
};
//分层最短路
//扩点问题
//获取所有钥匙的最短路径
//给一个二维网格grid
//'.'表示空房间 '#'表示一堵墙 '@'表示起点 大写字母表示钥匙 小写字母代表锁
//钥匙的范围是1，6
class Solution4 {
public:
    int shortPathAllKesy(vector<string>& grid) {
        //string的vector本质上是一个二维数组 string的长度需要一样这样才是完整的的矩形图
        int n = grid.size();
        int m = grid[0].size();
        int starX=0,starY=0;
        int allKeys = 0;//表示不同种类的钥匙
        //找到'@'就能找到starX starY了
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == '@') {
                    starX = i;
                    starY = j;
                }else if (grid[i][j] >= 'a' && grid[i][j] <= 'f') {
                    //记录钥匙的最大编号
                    allKeys = max(allKeys, grid[i][j] - 'a' + 1);
                }
            }
        }
        int targetStatus = (1 << allKeys) - 1;
        //只要状态变成了111就说明通关了
        //三维空间 坐标和状态
        vector<vector<vector<bool>>> visited(n,vector<vector<bool>>(m,vector<bool>(1 << allKeys,false)));
        //BFS
        queue<vector<int>> q;
        q.push({starX,starY,0});
        visited[starX][starY][0] = true;
        int step = 0;
        int dx[4] = {-1,1,0,0};
        int dy[4] = {0,0,-1,1};
        //status表示钥匙包
        while (!q.empty()) {
            int size = q.size();
            //先数队列里的几个点
            while (size--) {
                auto v = q.front();
                q.pop();
                int x = v[0];
                int y = v[1];
                int status = v[2];
                //如果拿到了所有的钥匙 直接返回步数
                if (status == targetStatus) return step;
                for (int i = 0; i < 4; i++) {
                    //没有拿完
                    //越界或者是墙
                    int nx = x + dx[i];
                    int ny = y + dy[i];
                    if (nx < 0 || nx >= n || ny < 0 || ny >= m || grid[nx][ny] == '#')continue;
                    char c = grid[nx][ny];
                    int nextStatus = status;
                    //如果遇到锁 看有没有对应的钥匙
                    if (c >= 'A' && c <= 'F') {
                        //!0说明为true说明要重新进行循环
                        //只有两个都是1就为1
                        if (!((status & (1 << (c - 'A'))))) continue;
                    }
                    //遇到钥匙'a'-'f'更新状态
                    //或运算让每一位是1的都变成1
                    nextStatus = status;
                    if (c >= 'a' && c <= 'f') nextStatus |= (1 << (c - 'a'));
                    // 如果这个位置在这个状态下没走过
                    if (!visited[nx][ny][nextStatus]) {
                        visited[nx][ny][nextStatus] = true;
                        q.push({nx, ny, nextStatus});
                    }
                }
            }
            step++;
        }
        return -1;//拿不完
    }
};
//跟4一样的题目 5是自己写的
class Solution5 {
public:
    const int MAXN = 31;
    const int MAXM = 31;
    const int MAXK = 6;
    int move_dir[5] = {0,1,0,-1,0};
    char grid[31][31];
    bool visited[31][31];

    int queue_arr[57600][3];//存的三维度的状态
    //让二维数组来模拟队列
    //行来代表位置坑位从0一直到57599
    //列长度为3 寸x y 状态
    //l表示出队的坑位
    //r比哦啊是下一个空闲的坑位
    //x y 钥匙的状态

    int l,r,n,m,key;

    void build(const vector<string>& g){
        l = r = key = 0;
        n = g.size();
        m = g[0].size();
        //复制王哥数据
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                grid[i][j] = g[i][j];
            }
        }
        //遍历网格寻找起点
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == '@') {
                    queue_arr[r][0] = i;
                    queue_arr[r][1] = j;
                    queue_arr[r++][2] = 0;
                }
                if (grid[i][j] >= 'a' && grid[i][j] <= 'f') {
                    //1的二进制是000001左移动几位再或就是状态
                    key |= 1 << (grid[i][j] - 'a');
                }
            }
        }
         memset(visited, false, sizeof(visited));


    }
    int shortPathAllKesy(vector<string>& g) {
        build(g);
        int level = 1;
        //开始BFS
        while (l < r) {
            int size = l - r;//计算当前这一层，一共有多少个格子在排队

            int x,y,s;//用于接收队列弹出的状态
            for (int k = 0; k < size; k++) {
                x = queue_arr[l][0];
                y = queue_arr[l][1];
                s = queue_arr[l][2];

                //遍历四个方向
                for (int i = 0; i < 4; ++i) {
                    int nx = x + move_dir[i];
                    int ny = y + move_dir[i + 1];
                    int ns = s;
                    if (nx < 0 || nx == n || ny < 0 || ny == m || grid[nx][ny] == '#') {
                        continue;
                    }
                    //如果是大写字母检查有没有钥匙
                    if (grid[nx][ny] >= 'A' && grid[nx][ny] <= 'f') {
                        if ((ns & (1 << (grid[nx][ny] - 'A'))) == 0) {
                            //说明没有钥匙
                            continue;
                        }
                    }
                    //如果是钥匙
                    if (grid[nx][ny] >= 'a' && grid[nx][ny] <= 'f') {
                        ns |= 1 << (grid[nx][ny] - 'a');
                    }
                    if (ns == key) {
                        return level;
                    }
                    //如果这个格子在当前钥匙状态下没被访问过，则入队并标记
                    if (!visited[nx][ny][ns]) {
                        visited[nx][ny][ns] = true;
                        queue_arr[r][0] = nx;
                        queue_arr[r][1] = ny;
                        queue_arr[r++][2] = ns;
                    }
                }
            }
            level++;
        }
        return -1;//无法集齐所有钥匙
    }
};
//电动车游览城市
//从一个起点到终点
//充满电可以走n个单位
//开始的电量是0 从A到B距离是5 在每个点冲一格电的时间也不同
//求最短的时间
class Solution6 {
public:
    int electricCarPlan(vector<vector<int>> paths,int cnt ,int start , int end,vector<int>& charge) {
        //cnt表示最大的电量


        //构建邻接表
        int n = paths.size();
        //graph[i]存储结构{相邻城市,路径耗电/距离}
        vector<vector<pair<int,int>>> graph(n);
        //无向图
        for (const auto& path : paths) {
            graph[path[0]].push_back({path[1], path[2]});
            graph[path[1]].push_back({path[0], path[2]});
        }
        //distance[][]表示城市i且剩余j格电的最小花费时间
        vector<vector<int>> distance(n, vector<int>(cnt + 1, INT_MAX));
        distance[start][0] = 0;
        //visited数组表示是否被记录了
        vector<vector<bool>> visited(n, vector<bool>(cnt + 1, false));
        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> heap;
        heap.push({0,start,0});//花费为0 再start 电量为0
        while (!heap.empty()) {
            auto record = heap.top();
            heap.pop();
            int cost = record[0];
            int cur = record[1];
            int power = record[2];
            //减枝
            if (visited[cur][power]) {
                continue;
            }
            if (cur == end) {
                return cost;
            }
            visited[cur][power] = true;
            //选择一在城市充电
            if (power < cnt) {
                if (!visited[cur][power+1] && cost + charge[cur] < distance[cur][power+1]) {
                    distance[cur][power+1] = cost + charge[cur];
                    heap.push({cost + charge[cur],cur,power+1});
                }
            }
            //选择二 不充电开车去其他城市
            for (const auto& edge : graph[cur]) {
                int nextCity = edge.first;
                int roadCost = edge.second;//消耗电量 距离相同

                int restPower = power - roadCost;
                int nextCost = cost + roadCost;

                //如果能走到且没有被访问过
                if (restPower >= 0 && visited[nextCity][restPower]) {
                    if (nextCost < distance[nextCity][restPower]) {
                        distance[nextCity][restPower] = nextCost;
                        heap.push({nextCost,nextCity,restPower});
                    }
                }
            }
        }
        return -1;
    }
};
class Solution7 {
    //给你n个城市和m条双向航空线路，每条航线有对应的
    //机票花费。航空公司开航庆典，
    //允许你最多免费乘坐k次航班。求从起点
    //s到终点t的最小花费。
private:
    struct Edge {
        int to;//通往的下一个城市
        int weight;
        int next;//出发的下一条路
    };
    struct State {
        int u;//当前城市
        int use;//已经使用过的免费次数
        int cost;//当前的总花费

        //小根堆的比较规则
        bool operator>(const State& o) const{
            return o.cost < cost;
        }

    };
    //成员变量
    int cnt;//代表边的条数
    vector<int> head;
    vector<Edge> edge;
    vector<vector<int>> dist;
    vector<vector<bool>> visited;

    void addEdge(int a,int b,int c) {
        edge.push_back({b,c,head[a]});
        head[a] = cnt++;
    }
    //t是目的城市
    //s是出发城市
    int flightPathSolution(int n, int k, int s, int t, vector<vector<int>>& flights) {
        int m = flights.size();
        cnt = 1;
        head.assign(n+1,0);
        //无向图加两次
        edge.resize(m * 2 + 5);
        const int INF = 0x3f3f3f3f; // 用一个大整数代表无穷大
        dist.assign(n + 1, vector<int>(k + 1, INF));
        //把“最省钱历史记录表”做成一个有(n+1) 行、(k+1)列的大表格。
        //并且把里面的每一个格子，全部用 10.6 亿（INF）填满。
        visited.assign(n + 1, vector<bool>(k + 1, false));
        // Step 2: 建立无向图（串糖葫芦的过程）
        for (const auto& flight : flights) {
            int u = flight[0];
            int v = flight[1];
            int w = flight[2];
            addEdge(u, v, w);
            addEdge(v, u, w);
        }

        // Step 3: 初始化起点，并将第一个初始“大礼包”丢进堆
        dist[s][0] = 0;
        priority_queue<State, vector<State>, greater<State>> heap;
        heap.push({s, 0, 0}); // 起点 s，用了 0 次免费，花了 0 元

        // Step 4: 自动机循环（Dijkstra 弹出与分裂扩展）
        while (!heap.empty()) {
            State record = heap.top();
            heap.pop();

            int u = record.u;
            int use = record.use;
            int cost = record.cost;

            // 如果这个“城市+免费次数”的特定状态已经处理过，直接扔掉（防止绕远路）
            if (visited[u][use]) continue;
            visited[u][use] = true;

            // 常见剪枝：一旦全场花钱最少的状态刚好到达了终点 t，说明大功告成，直接返回
            if (u == t) return cost;

            // 顺藤摸瓜：利用链式前向星遍历从城市 u 出发的所有很多个边
            for (int ei = head[u]; ei > 0; ei = edges[ei].next) {
                int v = edges[ei].to;      // 这条边通往的目的地城市 v
                int w = edges[ei].weight;  // 这条边的正常车费 w

                // 分裂抉择 A：使用免费超能力
                // 前提条件：我的免费次数还没用完（use < k），且用了之后比别人之前到 v 同样次数的记录更省钱
                if (use < k && dist[v][use + 1] > dist[u][use]) {
                    dist[v][use + 1] = dist[u][use]; // 车费不涨，但免费次数+1
                    heap.push({v, use + 1, dist[v][use + 1]});
                }

                // 分裂抉择 B：老老实实交钱走这条路
                // 只要当前的总花费 + 这一站的车费 w，比历史记录的 dist[v][use] 更便宜就更新
                if (dist[v][use] > dist[u][use] + w) {
                    dist[v][use] = dist[u][use] + w; // 免费次数不变，车费累加
                    heap.push({v, use, dist[v][use]});
                }
            }
        }

        // 如果堆都空了依然无法触发 u == t，说明起点和终点根本不连通
        return -1;
    }
};
