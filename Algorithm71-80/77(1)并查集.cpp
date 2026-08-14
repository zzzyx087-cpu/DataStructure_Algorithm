//
// Created by Nils on 2026/4/20.
//DSU
//并查集
//int find(a)find方法 查出来的是代表的值
//bool issameset(a,b)看属不属于一个集合
//void union(a,b)两个集合合并
#include <iostream>
using namespace std;
class UnionFindNowCoder {
    public:
    int MAXN = 1000001;
    vector<int> father(MAXN);//指向的指针
    vector<int> size(MAXN);
    vector<int> stack(MAXN);
    int n;
    void build() {
        for (int i = 0; i <= n; i++) {
            father[i] = i;
            size[i] = i;
        }
    }
    int find(int i) {//一直往上找找到代表节点返回
        //扁平化
        //准备一个准备数组stack
        int size = 0;//沿途收集的几个点
        while (i != father[i]) {
            stack[size] = i;
            size++;
            i = father[i];
        }
        //收集好了i是代表节点
        while (size > 0) {
            father[stack[size]] = i;
            size--;
        }
        return i;

    }
    bool isSameSet(int x, int y) {
        return find(x) == find(y);
    }
    void unionSet(int x, int y){//两个集合整合到一起
        int fx = find(x);
        int fy = find(y);
        if (fx != fy) {
            //看fx 和 fy哪个大
            size[fx] += size[fy];
            father[fx] = fx;

        }else {
            size[fy] += size[fx];
            father[fx] = fy;
        }
    }

};//复杂度是O(1)
class UnionFindNowCoder2 {
public:
    int MAXN = 100001;
    vector<int> father(MAXN);
    int n;
    build() {
        for (int i = 0; i <= n; i++) {
            father[i] = i;
        }
    }
    int find(int i) {
        if (father[i] != i) {
            father[i] = find(father[i]);//用递归栈来实现
        }
        return father[i];
    }
    bool isSameSet(int x, int y) {
        return find(x) == find(y);
    }
    void unionSet(int x, int y) {
        father[find(x)] = find(y);
    }
};
//给你一堆词
//有几个相似的单词
//并差集会把相似的合并 看集合里面词语的个数
class SimilaStringGroups {
    const int MAXN = 301;
    vector<int> father(MAXN);
    int sets;

    // 初始化并查集
    void build(int n) {
        for (int i = 0; i < n; ++i) {
            father[i] = i;
        }
        sets = n;
    }
    //带压缩的查找
    int find(int i) {
        if (i != father[i]) {
            father[i] = find(father[i]);
        }
        return father[i];
    }
    //合并两个集合
    void unionSet(int x, int y) {
        int fx = find(x);
        int fy = find(y);
        if (fx != fy) {
            father[fx] = fy;
            sets--;//合并成功为一个集合
        }
    }
    //主逻辑
    int numSimilarGroups(vector<string>& strs) {
        int n = strs.size();
        int len = strs[0].size();//每个字符串的长度
        build(n);
        //比较两两所有的字符串
        for (int i = 0; i < n; i++) {
            for (int j = 1; j < n; j++) {
                int diff = 0;
                for (int k = 0; k < len; k++) {//计算有多少位不同
                    if (strs[i][k] != strs[j][k]) diff++;
                    if (diff > 2) break;

                }
                if (diff == 0 || diff == 2) {
                    unionSet(i,j);
                }
            }
        }
        return sets;//分了的组

    }
};