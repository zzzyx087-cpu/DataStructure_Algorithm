//
// Created by zhouyxuiang on 2026/4/23.
//
#include <iostream>
using namespace std;

const int MAXN = 11;//节点的最大数量
const int MAXM = 21;//边的最大数量
//1.邻接矩阵
int graph1[MAXN][MAXN];
//2.邻接表
vector<vector<pair<int,int>>>graph2;//pair<to,weight>
//3.链式前向星
int head[MAXN];// 链式前向星：每个点的第一条边
int next_[MAXM]; // 第i条边的【上一条边】是谁
int to[MAXM];// 第i条边【去到哪个点】
int val[MAXM];// 第i条边【权值】
int cnt;// 现在用到第几条边了（从1开始数）
// 初始化所有图
void build(int n) {
    // 邻接矩阵清空
    memset(graph1, 0, sizeof(graph1));

    // 邻接表清空并初始化
    graph2.clear();
    graph2.resize(n + 1); // 0号不用

    // 链式前向星清空
    cnt = 1;
    memset(head, 0, sizeof(head));
}
// 链式前向星加边
void addEdge(int u, int v, int w) {
    to[cnt] = v;// 这条边去 v
    val[cnt] = w;// 权值 w
    next_[cnt] = head[u];// 新边 指向 原来u的第一条边
    head[u] = cnt;// u的第一条边 变成 新边
    cnt++; // 下一条边
}
// 无向带权图建图（三种方式）
void undirectGraph(vector<vector<int>>& edges) {
    // 1. 邻接矩阵
    for (auto& edge : edges) {
        int u = edge[0], v = edge[1], w = edge[2];
        graph1[u][v] = w;
        graph1[v][u] = w;
    }

    // 2. 邻接表
    for (auto& edge : edges) {
        int u = edge[0], v = edge[1], w = edge[2];
        graph2[u].emplace_back(v, w);
        graph2[v].emplace_back(u, w);
    }

    // 3. 链式前向星
    for (auto& edge : edges) {
        int u = edge[0], v = edge[1], w = edge[2];
        addEdge(u, v, w);
        addEdge(v, u, w);
    }
}
//拓扑排序
//有向图 没有环
//把入度为0的删去一次删除他的影响
class Solution {
public:
   vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites) {
       vector<vector<int>> graph(numCourses);//邻接表存图 numCourse表示课程的数量
       vector<int> indegree(numCourses, 0);//记录入度

       for (auto& edge : prerequisites) {
           int a = edge[0], b = edge[1];
           graph[b].push_back(a);//[a,b]表示a是后选课 b是先修课
           indegree[a]++;
       }
       vector<int> q(numCourses);
       int l = 0, r = 0;
       for (int i = 0; i < numCourses; i++) {
           if (indegree[i] == 0) {
               q[r++] = i;//把入度为0的点收进来
           }
       }

       vector<int> order;  // 存最终上课顺序
       int cnt1 = 0;
       while (l < r) {     // 队列不为空
           int cur = q[l++];//拿出来一个点
           order.push_back(cur);//把结果加进去
           cnt1++;

           for (int v : graph[cur]) {
               //v是cur的下一个节点
               // 遍历 u 所有后续课 v
               indegree[v]--;       // v 的先修课少了一门（因为 u 上完了）

               if (indegree[v] == 0) { // 如果 v 没有先修课了
                   q[r++] = v;         // 把 v 加入队列
               }
           }
       }
       if (cnt != numCourses) {
           return {};
       }
       return order;
   }
};
//返回所有正确拓扑排序中字典序最小的结果
//把队列换掉变成小根堆
class Solution2 {
    public:
    vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites) {
        vector<vector<bool>> graph(numCourses, vector<bool>(numCourses, false));
        //单纯看两个点有没有边
        //graph [b][a] = true 就是 b → a
        vector<int> indegree(numCourses, 0);
        //建立图
        for (auto &edge : prerequisites) {
            int a = edge[0], b = edge[1];
            if (!graph[a][b]) {//说明没有建立
                graph[a][b] = true;
                indegree[a]++;
            }
        }
        //小根堆
        priority_queue<int,vector<int>,greater<int>> heap;
        for (int i = 0; i < numCourses; i++) {
            if (indegree[i] == 0) {
                heap.push(i);
            }
        }
        vector<int> order;
        while (!heap.empty()) {
            int cur = heap.top();
            heap.pop();
            order.push_back(cur);
            //消除cur对后面的节点的影响
            for (int v = 0; v < numCourses; v++) {
                if (graph[cur][v]) {
                    indegree[v]--;
                    if (indegree[v] == 0) {
                        heap.push(v);
                    }
                }
            }
        }
        if (order.size() != numCourses) {
            return {};
        }
        return order;
    }
};
//火星词典
//整理一个相对的顺序
class Solution3 {
//给一个字符串的列表
//链式前向星
    //思路wrt wrf
    //说明t排在f前面
    //转化好成图 t->f 一条有向边

    public:
    //先开两个数组 graph[26]邻接表 存谁就指向谁
    //indegree[26]记录每个字母的入度
    //对比两个单词的i和i+1位置
    //找到不一样的字母
    // vector<vector<int>> g(26);c++类成员里不能这么写
    // vector<int> in(26, -1);
    string alienOrder(vector<string> &words) {
        vector<vector<int>> g{vector<vector<int>> (26)};
        vector<int> inDgree{vector<int>(26, -1)};//-1表示没有出现
        //标记所有出现的字母
        for (auto &word:words) {
            for (char c : word) {
                inDgree[c - 'a'] = 0;
            }
        }
        //构建字母之间的大小关系
        //知道谁在前谁在后
        for (int i = 0;i < words.size() - 1; i++) {
            string& w1 = words[i];
            string& w2 = words[i + 1];
            int len = min(w1.length(), w2.length());
            int ptr = 0;
            while (ptr < len) {
                if (w1[ptr] != w2[ptr]) {
                    //说明u排在v的后面
                    int u = w1[ptr] - 'a';
                    int v = w2[ptr] - 'a';
                    //画一条箭头u -> v
                    g[u].push_back(v);
                    inDgree[v]++;
                    break;
                }
                ptr++;
            }
        //非法情况
            //前面的单词更长且包含了后面的单词就比较不出来
        if (ptr == w2.length() && ptr < w1.length()) {
            return "";
        }
        }
        int total = 0;
        for (int i = 0; i < 26; i++) {
            if (inDgree[i] == -1) {//表示从来没有出现过
                total++;
            }
        }
        //把入度为0的放入队列

        queue<int> q;
        //i为26个小写字母的编号
        for (int i = 0; i < 26; i++) {
            if (inDgree[i] == 0) {
                q.push(i);//入度为0进队列
            }
        }
        //开始拓扑排序
        string res;
        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            res += (char)(cur + 'a');
            //遍历它指向的字母
            for (int next : g[cur]) {
                inDgree[next]--;
                if (inDgree[next] == 0) {
                    q.push(next);
                }
            }

        }
        //判断是否成环
        if (res.size() != total) {
            return "";
        }
        return res;
    }
};
//戳印序列
//一个序列 一个印章
//后盖的会覆盖前面的 让完全正确的后面盖
class Solution4 {
    public:
    vector<int> movesToStamp(string stamp, string target) {
        int m = stamp.size();
        int n = target.size();
        //每个位置需要匹配的数量
        vector<int> inDegree(n - m + 1, m);//n-m+1表示能盖章的位置
        //这个盖章点 i 还差几个字符才能完全匹配！
        //依赖图
        vector<vector<int>> graph(n);
        vector<bool> done(n,false);
        queue<int> q;

        for (int i = 0; i < n - m; i++) {//遍历印章可能存在的盖章位置
            for (int j = 0; j < m; j++) {//逐个对比印章和目标的字符串
                if (target[i + j] == stamp[j]) {
                    inDegree[i]--;//剩余多少个字符不匹配说明这个范围的不匹配的数量
                }else {
                    //说明不匹配
                    //这个字符不匹配 不能擦掉
                    // 要等着 i+j 这一格先被擦掉。
                    graph[i+j].push_back(i);
                }
            }
            if (inDegree[i] == 0) {
                q.push(i);//盖这个位置所有字符都匹配
            }
            //拓扑排序
            vector<int> path;//记录擦掉印章的顺序
            while (!q.empty()) {
                int cur = q.front();
                q.pop();
                path.push_back(cur);
                for (int j = 0; j < m; j++) {

                }
            }
        }
    }
};
//戳印序列
class Solution5{
    public:
    vector<int> movesToStamp(string stamp, string target) {
        int n = target.size();
        int m = stamp.size();
        vector<int> res;
        vector<bool> visited(n,false);
        int cnt2 = 0;//变成?的字符数量
        //反向拓扑
        //假设最开始的结果就是target 一步步变成？？就是不正确的情况
        while (cnt2 < n) {
            bool flag = false;
            //这一轮没有成功改一次章
            //遍历所有能够盖章的点
            for (int i = 0; i <= n - m; i++) {
                if (!visited[i] && check(stamp,target,i)) {
                    visited[i] = true;
                    flag = true;
                    //把i 到 i + m变成？
                    for (int j = 0; j < m; j++) {
                        if (target[i + j] != '?') {
                            target[i + j] = '?';
                            cnt2++;
                        }
                    }
                    res.push_back(i);
                }
            }
            if (!flag) {
                return {};
            }
        }
        reverse(res.begin(), res.end());
        return res;
    }
    bool check(string& stamp, string& s, int pos) {//在s这个字符串里 从pos开始 能不能一次盖章stamp
        int m = stamp.size();
        bool hasChar = false;
        for (int i = 0; i < m; i++) {
            if (s[pos + i] != '?' && s[pos + i] != stamp[i]) {
                return false;
            }
            if (s[pos + i] != '?') {
                hasChar = true;
            }
        }
        return hasChar;
    }
};

