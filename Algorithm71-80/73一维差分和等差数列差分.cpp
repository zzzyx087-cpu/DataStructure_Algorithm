//
// Created by zhouyxuiang on 2026/4/15.
//
//
#include <iostream>
using namespace std;
//差分就是在一个数组上的加减操作
//比如在0～3上面加1 在0位置上+1 在3+1位置上-1
//这个操作相当于一个效果 算前缀和就是效果的叠加

vector<int> BookingSeat(vector<vector<int>> bookings,int n) {
    //[1,5,6] [2,9,3]n个航班
    //cnt就是arr准备n+2的大小
    vector<int>  cnt(n + 2,0);
    for (auto& book : bookings) {
        int l = book[0];
        int r = book[1];
        int seats = book[2];
        cnt[l] += seats;
        cnt[r+1] -= seats;
    }
    //计算前缀和
    for (int i = 1;i <= n;i++) {
        cnt[i] += cnt[i-1];
    }
    vector<int> ans(n+1);
    for (int i = 1;i <= n;i++) {
        ans[i] = cnt[i];
    }
    return ans;
}
//等差数列的差分
//[l,r,s,e,d]在l到r的范围中 s是首项，e是末项，d是公差
int MAXN = 1000005;


//无聊的数列
const int N = 100005;

int n, m;

void build(vector<long long> &arr) {
    // 两次前缀和 → 二阶差分还原
    for (int i = 1; i <= m; i++) arr[i] += arr[i-1];
    for (int i = 1; i <= m; i++) arr[i] += arr[i-1];
}
//落水问题
//输入n m
//输出每个位置上的水位

void add(vector<long long> &nums,int l, int r, int d, int s ,int e) {
    if (l < 1) l = 1;
    if (r > m) r = m;
    if (l > r) return;

    nums[l] += d;
    nums[l+1] += d - s;
    nums[r+1] -= d + e;
    nums[r+2] += e;
}

void DorpInWater() {
    cin >> n >> m;
    //n表示落水的人数 m表示湖泊的长度从1～n
    vector<long long> lake(m+2,0);
    for (int j = 0;j < n;j++) {
        //四个差分数组
        int i,v;
        cin >> i >> v;
        //先从最左侧开始
        add(lake,i-2 * v,i - v,-1,0,v);
        add(lake,i - v,i,-1,v,0);
        add(lake,i,i+v,1,-v,0);
        add(lake,i + v,i + 2 * v,1,0,v);


    }
    build(lake);
    for (int j = 1; j <= m; j++) {
        cout << lake[j] << endl ;
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;

    // 用来存查询，最后一起输出
    vector<int> qs;

    while (m--) {
        int op;
        cin >> op;
        if (op == 1) {
            // 区间加等差数列
            int l, r, K, D;
            cin >> l >> r >> K >> D;
            int len = r - l + 1;
            long long last = K + (len - 1LL) * D;

            // 二阶差分核心4行
            arr[l] += K;
            arr[l+1] += D - K;
            arr[r+1] -= D + last;
            arr[r+2] += last;
        } else {
            // 记录查询位置
            int p;
            cin >> p;
            qs.push_back(p);
        }
    }

    //只需要build一次
    build();

    // 输出所有答案
    for (int p : qs) {
        cout << arr[p] << '\n';
    }

    return 0;
}