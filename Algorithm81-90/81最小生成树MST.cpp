//
// Created by zhouyxuiang on 2026/4/27.
//
#include <iostream>
using namespace std;
//MST
//最小生成树
//Kruskal算法
//并查集
class Solution1 {
public:
    vector<int> father;
    //并差集 查找和路径收缩
    int find(int x) {
        if (father[x]!= x) {//祖宗不是自己
            father[x] = find(father[x]);//往上照
        }
        return father[x];//返回最终的祖宗
    }
    bool unite(int x, int y){
        int fx = find(x);
        int fy = find(y);
        if (fx==fy) return false;
        father[fx] = fy;
        return true;
    }
    int kruskal(int n ,int m,vector<vector<int>>& edges) {
        father.resize(n+1);
        for (int i = 1; i <= m; i++) {
            father[i] = i;
        }
        //按照权值大小排序
        sort(edges.begin(),edges.end(),[&](vector<int>& a,vector<int>& b) {
            return a[2] < b[2];
        });
        int sum = 0;
        int cnt = 0;
        for (auto&e : edges) {
            int u = e[0];
            int v = e[1];
            int w = e[2];
            if (unite(u,v)) {
                sum += w;
                cnt++;
            }
        }
        //必须选购n-1条边才是最小生成树
        return cnt == n-1 ? sum : -1;
    }
};
//时间复杂度为 O(m log m)


//prim算法 建图
//解锁了点的集合为set
//解锁了的边的集合是edge 小根堆

class Solution2 {
public:
//从任意点开始 开始的点进入set 加入的边到heap
//从heap弹出权值最小的边e 查边e所去往的点x
    int prim(int n, vector<vector<vector<int>>>&graph) {
        //graph[1] → 点1的所有边
        //graph[1][0]存一个点的第一个邻居边
        //graph[1][0]=2表示指向点2
        //graph[1][1]=3表示权值为3
        //这个小根堆存的是int int
        //first边权w second节点v
        priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> heap;
        //greater<pair<int, int>>按照first从小到大排序
        //vector<pair<int,int>>表示存很多个pair
        //开始存入堆结构
        for (auto& e : graph) {
            int v = e[0];
            int w = e[1];
            heap.push({w,v});
        }
        //表明哪些节点已经发现过了

        vector<bool> set(n+1,false);
        set[1] = true;
        int nodeCnt = 1;
        int ans = 0;//权重和
        while (!heap.empty()) {
            auto top = heap.top();
            heap.pop();
            int cost = top.first;
            int next = top.second;
            if (!set[next]) {
                nodeCnt++;
                set[next] = true;
                ans += cost;
                //把next的所有邻边存入堆
                for (auto& e: graph[next]) {
                    int v = e[0];
                    int w = e[1];
                    heap.push({w,v});
                }
            }
        }
        return (nodeCnt == n) ? ans : -1;
    }
};
//水资源分配优化
class Solution3 {
public:
    //代价打井 或者 与其他村庄相连接
    //最小的花费
    //我们引入一个虚拟节点 0，把它当成「水源」
    vector<int> father;
    int find(int x) {
        if (father[x]!=x) {
            return father[x] = find(father[x]);
        }
        return father[x];
    }
    bool unite(int x, int y) {
        int fx = find(x);
        int fy = find(y);
        if (fx == fy) return false;
        father[fx] = fy;
        return true;
    }
    int minCost(int n,vector<int>& wells, vector<vector<int>>& pipes) {
        //wells表示节点成本
        //pipes表示真实的边
        for (int i = 1; i <= n; i++) {
            pipes.push_back({0,i,wells[i-1]});
        }
        sort(pipes.begin(),pipes.end(),[](const vector<int> &a, const vector<int> &b) {
            return a[2] < b[2];
        });
        //初始化并查集
        father.resize(n+1);
        for (int i = 0; i <= n; i++) {
            father[i] = i;
        }
        int ans = 0;
        int cnt = 0;
        //k算法选边
        for (auto& p : pipes) {
            int u = p[0] , v = p[1] , w = p[2];
            if (unite(u,v)) {
                ans += w;
                cnt++;
            }
            if (cnt == n) break;
        }
        return ans;
    }
};
//检查边长度限制的路径是否存在
class Solution4 {
public:
    vector<int> father;

    int find(int x) {
        if (father[x]!=x) {
            return father[x] = find(father[x]);
        }
        return father[x];
    }
    bool unite(int x, int y) {
        int fx = find(x);
        int fy = find(y);
        if (fx == fy) return false;
        father[fx] = fy;
        return true;
    }
    vector<bool> distanceLimitedPathsExist(int n, vector<vector<int>>& edgeList, vector<vector<int>>& queries) {
        //vector<vector<int>>& queries表示一堆需要查找的数组
        //edgeList = 图的边：{u, v, 边长}
        //按边的权值大小排序

        sort(edgeList.begin(), edgeList.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[2] < b[2];
        });
        int m = edgeList.size();
        int k = queries.size();
        vector<vector<int>> questions(k);
        //因为待会输出的位置是根据实际的顺序输出的
        for (int i = 0; i < k; ++i) {
            questions[i] = {queries[i][0], queries[i][1], queries[i][2], i};
        }

        // 3. 查询按 limit 从小到大排序
        sort(questions.begin(), questions.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[2] < b[2];
        });

        // 4. 初始化并查集
        father.resize(n);
        for (int i = 0; i < n; ++i) {
            father[i] = i;
        }

        vector<bool> ans(k);
        int j = 0; // 边的指针

        // 5. 双指针处理查询
        for (int i = 0; i < k; ++i) {
            // 把所有权值 < 当前 limit 的边加入并查集
            while (j < m && edgeList[j][2] < questions[i][2]) {
                unite(edgeList[j][0], edgeList[j][1]);
                j++;
            }
            // 判断两点是否连通
            ans[questions[i][3]] = (find(questions[i][0]) == find(questions[i][1]));
        }

        return ans;
    }
};
//最小瓶颈数
//最大边的权重尽肯能小
class Solution5{
public:
    vector<int> father;

    int find(int x) {
        if (father[x] != x) father[x] = find(father[x]);
        return father[x];
    }

    bool unite(int x, int y) {
        int fx = find(x), fy = find(y);
        if (fx == fy) return false;
        father[fx] = fy;
        return true;
    }

    pair<int, int> solve(int n, vector<vector<int>>& edges) {
        sort(edges.begin(), edges.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[2] < b[2];
        });

        father.resize(n + 1);
        for (int i = 1; i <= n; ++i) father[i] = i;

        int ans = 0;//记录最大的边权
        int edgeCnt = 0;//记录已经选了几条边

        for (auto& e : edges) {
            if (unite(e[0], e[1])) {
                edgeCnt++;
                ans = max(ans, e[2]);
            }
            if (edgeCnt == n - 1) break;
        }

        return {n - 1, ans};
    }
};

