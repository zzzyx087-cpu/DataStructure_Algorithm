//
// Created by zhouyxuiang on 2026/4/20.
//
#include<iostream>
using namespace std;

//如果同行同列的石头可以移除掉 并差集 打标签
//只要同行或者同列就整合到一起
const int MAXN = 1001;
int father[MAXN];
int sets;

unordered_map<int, int> rowFirst;//记录这一行这一列第一次出现的石头是哪一个
unordered_map<int, int> colFirst;
// 初始化并查集
void build(int n) {
    rowFirst.clear();
    colFirst.clear();
    for (int i = 0; i < n; ++i) {
        father[i] = i;
    }
    sets = n;
}

// 带路径压缩的查找
int find(int i) {
    if (i != father[i]) {
        father[i] = find(father[i]);
    }
    return father[i];
}

// 合并两个集合
void my_union(int x, int y) {
    int fx = find(x);
    int fy = find(y);
    if (fx != fy) {
        father[fx] = fy;
        sets--;
    }
}
int removeStones(vector<vector<int>> &stones) {
    int n = stones.size();
    build(n);
    for (int i = 0; i < n; ++i) {
        //把同一行 / 同一列的石头，看成 “连通的”，合并成一个集合
        int row = stones[i][0];// 处理行：同一行的石头合并
        int col = stones[i][1];
        if (!rowFirst.count(row)) {
            rowFirst[row] = i;
        } else {
            my_union(i, rowFirst[row]);
        }

        // 处理列：同一列的石头合并
        if (!colFirst.count(col)) {
            colFirst[col] = i;
        } else {
            my_union(i, colFirst[col]);
        }
    }
    return n - sets;
}
//-------------------
//找出知道秘密的专家
//返回知道秘密的顺序
//在不同时间开会 前面的连接就取消

//打标签的技巧 弄一个数组 让S[num] = true
//也需要一个拆开的过程
//看是不是true知道秘密 不知道就拆开
vector<bool> secret(MAXN);
void build1(int n, int firstPerson) {
    for (int i = 0; i < n; ++i) {
        father[i] = i;
        secret[i] = false;
    }
    father[firstPerson] = 0;//father设置成0说明是一个集合
    secret[0] = true;
}
void my_union2(int x, int y) {
    //找到fx的代表数字
    int fx = find(x);
    int fy = find(y);
    if (fx != fy) {
        secret[fy]= secret[fy] || secret[fx];
        father[fx] = fy;
    }
}
vector<int> findAllPeople(int n, vector<vector<int>> &meetings,int first) {
    build1(n,first);
    int m = meetings.size();
    //按会议时间排序

    sort(meetings.begin(),meetings.end(),[](const vector<int>& a, const vector<int>& b) {
        return a[2] < b[2];
    });//O(mlogM)
    for(int l = 0;l < m;) {
        int r = l;
        //r .. l一定是共同时刻
        while (r + 1 < m && meetings[l][2] == meetings[r + 1][2]) {
            r++;
        }
        //这些会议一定是一个时刻
        //然后合并
        //有些知道秘密有些不知道秘密
        for (int i = l; i <= r; ++i) {
            int a = meetings[i][0];
            int b = meetings[i][1];
            my_union2(a, b);
        }
        //拆散行为
        //重新建立集合
        for (int i = l,a,b;i <= r;i++) {
            a = meetings[i][0];
            b = meetings[i][1];
            if (!secret[find(a)] ) {//看finda的集合知不知道秘密
                father[a] = find(a);
            }
            if (!secret[find(b)] ) {
                father[b] = find(b);
            }
        }
        l = r + 1;
    }
    vector<int> res;
    for (int i = 0; i < n; ++i) {
        if (secret[find(i)]) {
            res.push_back(i);
        }
    }
    return res;
}
//好路径的条数
class Solution1{
//从节点一样的值到另一个一样的值的节点
    public:
    int MAXN =30001;
    int father[MAXN];
    int maxcnt[MAXN];
    //maxcnt这个数组 就是存最大值点的个数
    void build(int n) {
        for (int i = 0; i < n; ++i) {
            father[i] = i;
            maxcnt[i] = 1;
        }
    }
    int find(int i) {
        if (i != father[i]) {
            father[i] = find(father[i]);
        }
        return father[i];
    }
    int unite1(int x , int y, const vector<int>& vals) {
        int fx = find(x);
        int fy = find(y);
        int path = 0;
        if (vals[fx] > vals[fy]) {
            father[fy] = fx;
        }else if (vals[fx] < vals[fy]) {
            father[fx] = fy;
        }else {
            path = maxcnt[fx] * maxcnt[fy];
            father[fy] = fx;
            maxcnt[fx] += maxcnt[fy];
        }
        return path;
    }
    int numberOfGoodPaths(vector<int>& vals, vector<vector<int>>& edges) {
        //edges是图的所有遍 是两个点之间的连线
        int n = vals.size();
        build(n);
        int ans = n;//单节点也是一条路径
        //edges的两条边e1 e2
        //e1[0,1]分别表示第一个节点0 第二个节点1
        //e2[2,3]分别表示第一个节点2 第二个节点3
        sort(edges.begin(), edges.end(), [&](const vector<int>& e1, const vector<int>& e2) {
        return max(vals[e1[0]], vals[e1[1]]) < max(vals[e2[0]], vals[e2[1]]);//取出每条边的两点的值拿出更大的那一个
           // 按边两个点中的最大值从小到大排序！
    });
        for (auto& edge : edges) {
            ans += unite1(edge[0], edge[1], vals);
        }
        return ans;
    }

};
//减少恶意软件的传播
//删掉哪一个节点 能够挽回最多的点
class Solution2 {
public:
    static const int MAXN =30001;
    bool virus[MAXN];//b标记这个节点是不是病毒
    int father[MAXN];//记录联通到哪个模块
    int size_[MAXN];//联通块有多少个节点
    int infect[MAXN];//标记一个联通块被感染了
    int cnts[MAXN];
    void build(int n, vector<int>&initial) {
        for (int i = 0; i < n; ++i) {
            virus[i] = false;
            infect[i] = -1;
            size_[i] = 1;
            father[i] = i;
            cnts[i] = 0;//表示删除后能救几个点
        }
        for (int i : initial) {
            virus[i] = true;
        }
    }
    int find(int i) {
        if (i != father[i]) {
            father[i] = find(father[i]);
        }
        return father[i];
    }
    void unite(int i, int j) {//合并数组
        int fi = find(i);
        int fj = find(j);
        if (fi == fj) return ;//如果本来就是一家人，直接返回不用合。
        if (size_[fi] < size_[fj]) swap(fi,fj);
        //把小集合 挂到 大集合 下面
        //这样fi所在的数量就是最多的了
        father[fj] = fi;
        size_[fi] += size_[fj];
    }
    int minMalwareSpread(vector<vector<int>> graph, vector<int> initial) {
        //普通点先合并 只要一个普通点的集合连接两个病毒点 就无法被拯救
        int n = graph.size();
        build(n,initial);
        //先把非病毒的点连接起来
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (graph[i][j] == 1 && !virus[i] && !virus[j]) {//表示这两个点相互连接
                    unite(i,j);
                }
            }
        }
        //给每个联通块标记他会被哪一个病毒感染
        for (int sick : initial) {//遍历每一个病毒
            for (int neighbor = 0; neighbor < n; ++neighbor) {
                // 如果：病毒sick 和 邻居neighbor 相连
                // 并且 neighbor 不是病毒（是正常人）
                if (sick != neighbor && !virus[neighbor] && graph[sick][neighbor] == 1) {
                    //第三个参数表示有连接
                    int fn = find(neighbor);//代表节点
                    if (infect[fn] == -1) {
                        //表示没有感染
                        infect[fn] = sick;
                    }else if (infect[fn] != -2 && infect[fn] != sick) {
                        infect[fn] = -2;//完全救不回来
                    }
                }
            }
        }
        //统计拯救的数据
        //不是代表点的不讨论
        //只看代表数字
        for (int i = 0;i < n;++i) {
            if (i == find(i) && infect[i] >= 0) {//只要>0就说明被sick感染了
                cnts[infect[i]] += size_[i];//infect[i]表示感染的源头病毒
            }
        }
        sort(initial.begin(), initial.end());
        //如果两个病毒能救的人一样多，必须返回【编号更小】的那个
        //编号小的优先选择
        int ans = initial[0];
        int max = cnts[ans];
        for (int i = 0; i < n; ++i) {
            if (cnts[i] > max) {
                ans = i;
                max = cnts[i];
            }
        }

        return ans;
    }

};