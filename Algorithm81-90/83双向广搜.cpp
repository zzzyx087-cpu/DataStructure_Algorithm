//
// Created by zhouyxuiang on 2026/5/9.
//
//双向广搜
//单词接龙
//从单词beginword 和 endword的转换序列
//每一对相邻的单词只差一个字母
//求最短的长度
#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <list>
#include <algorithm>

using namespace std;
const int MAXN = 1 << 21;//2的21次方
int lsum[MAXN], rsum[MAXN];
int fillIdx;
class Solution1 {
    vector<vector<string>> ans;
    list<string> path;
    //存储单词之间的指向关系
    unordered_map<string, vector<string>> graph;
    unordered_set<string> dict;
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        ans.clear();
        graph.clear();
        path.clear();
        dict = unordered_set<string>(wordList.begin(), wordList.end());
        //如果这个dict里没有这个endWord就return ans
        if (dict.find(endWord) == dict.end()) return ans;
        //双向的集合
        unordered_set<string> smallLevel;
        unordered_set<string> bigLevel;
        smallLevel.insert(beginWord);
        bigLevel.insert(endWord);
        //调用双向的BFS
        if (bfs(smallLevel, bigLevel, false)) {
            dfs(beginWord, endWord);
        }
        return ans;
    }
private:
    //reverse表示从begin到end移动
    bool bfs(unordered_set<string> &smallLevel , unordered_set<string>&bigLevel, bool reverse) {
        if (smallLevel.empty()) return false;
        //从人少的一侧扩展
        if (smallLevel.size() > bigLevel.size()) {
            return bfs(bigLevel, smallLevel, !reverse);
        }
        //开始删除单词的环节
        for (const string &word : smallLevel) {
            dict.erase(word);
        }
        for (const string &word : bigLevel) {
            dict.erase(word);
        }
        unordered_set<string> nextLevel; // 存储下一层要扩散的单词
        bool found = false;
        //开始尝试改变单词
        for (const string &word : smallLevel) {
            string curr = word;
            for (int i = 0; i < curr.length(); i++) {
                char old = curr[i];
                for (char ch = 'a'; ch <= 'z'; ch++) {
                    if (ch == old) continue;
                    curr[i] = ch;
                    if (bigLevel.count(curr)) {
                        // 找到了相遇点！
                        found = true;
                        addEdges(word, curr, reverse);
                    } else if (dict.count(curr)) {
                        // 没相遇，但是是合法单词，继续扩展
                        nextLevel.insert(curr);
                        addEdges(word, curr, reverse);
                    }
                }
                curr[i] = old;//复原试下一个字母
            }
        }

        return found || bfs(nextLevel, bigLevel, reverse);
    }
    void addEdges(string u,string v, bool reverse) {
        if (reverse) {
            //如果是反向搜出来的调换顺序存入
            //确保箭头指向离终点最近的方向
            graph[v].push_back(u);
        }else {
            graph[u].push_back(v);
        }
    }
    void dfs(const string& curr, const string& target) {
        path.push_back(curr);
        if (curr == target) {
            //找到了 复制一份当前的path到ans
            ans.push_back(vector<string>(path.begin(), path.end()));

        }else {
            //没看到按照地图走
            if (graph.count(curr)) {
                for (const string &next : graph[curr]) {
                    dfs(next, target);//往深处走一步
                }
            }
        }
    }
};
//零食问题 世界冰球锦标赛
//包容量为w n袋零食 i袋体积为v[i]
//看有几种零食的放法
//背包数值大 零食的体积很大
//不能用动态规划
class Solution2 {
public:
    //n表示物品数量
    //w表示最大重量
    //arr表示重量的数组
    int mid;
    long long findMaxWays(int n, long long w,vector<long long>& arr) {
        mid = n / 2;
        lsum.clear();
        rsum.clear();
        dfsLeft(0,mid,0,w,arr);
        dfsRight(mid,n,0,w,arr);
        sort(rsum.begin(),rsum.end());//右边排序用于二分查找
        sort(lsum.begin(),lsum.end());
        long long ans = 0;
        //双指针统计
        //左侧从0位置开始
        //右侧从最右侧开始
        int i = 0;
        int rsize = rsum.size();
       for (int j = rsize - 1; j >= 0; j--) {
           while (i < mid && lsum[i] + rsum[j] <= w) {
               ans += j + 1;
               i++;
           }
       }
    }
private:
    vector<long long> lsum;//左边子集和
    vector<long long> rsum;//右边子集和

    //递归生成左半部分的子集和
    // 左半部分 DFS
    void dfsLeft(int idx, int end, long long sum, long long w, vector<long long>& arr) {
        if (sum > w) return;
        if (idx == end) {
            lsum.push_back(sum);
            return;
        }
        dfsLeft(idx + 1, end, sum, w, arr);                // 不选
        dfsLeft(idx + 1, end, sum + arr[idx], w, arr);      // 选
    }

    // 右半部分 DFS
    void dfsRight(int idx, int end, long long sum, long long w, vector<long long>& arr) {
        if (sum > w) return;
        if (idx == end) {
            rsum.push_back(sum);
            return;
        }
        dfsRight(idx + 1, end, sum, w, arr);                // 不选
        dfsRight(idx + 1, end, sum + arr[idx], w, arr);      // 选
    }

};
//选出子序列来跟goal进行比较 来找出差最小的那几个子序列
class Solution3 {
    public:
    int mid;
    long long findMinimum(vector<int> &nums, int goal) {
        int n = nums.size();
        long long minSum = 0,maxSum = 0;
        for (int x : nums) {
            if (x >= 0) maxSum += x;
            else minSum += x;
        }
        if (maxSum <= goal) return abs(maxSum - goal);
        if (minSum >= goal) return abs(minSum - goal);
        //排序去除重复
        sort(nums.begin(), nums.end());
        //生成两边的子集

    }
    void collect(vector<int> &nums , int pos, int end ,int curSum, int sumArr[]) {

    }

};