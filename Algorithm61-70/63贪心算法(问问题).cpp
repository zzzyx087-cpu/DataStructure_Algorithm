//
// Created by zhouyxuiang on 2026/3/25.
//
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 1010;

struct Student {
    int s, a, e;
    int total;  // s + a + e
};

Student stu[N];

// 按总耗时从小到大排序
bool cmp(Student x, Student y) {
    return x.total < y.total;
}

int main() {
    int n;
    cin >> n;

    // 读入数据
    for (int i = 0; i < n; i++) {
        cin >> stu[i].s >> stu[i].a >> stu[i].e;
        stu[i].total = stu[i].s + stu[i].a + stu[i].e;
    }

    // 贪心排序
    sort(stu, stu + n, cmp);

    long long ans = 0;   // 所有发消息时刻之和
    long long time = 0;  // 当前时间

    for (int i = 0; i < n; i++) {
        // 发消息时刻 = 当前时间 + s + a
        time += stu[i].s + stu[i].a;
        ans += time;
        // 该同学全部完成的时间
        time += stu[i].e;
    }

    cout << ans << endl;

    return 0;
}