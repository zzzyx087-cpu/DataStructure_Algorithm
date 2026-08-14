//
// Created by zhouyxuiang on 2026/3/10.
//
#include <iostream>
using namespace std;
int simulate(const vector<int>& cards , int start) {//cards容器存放卡片 start是开始的位置
    int n = cards.size();
    int score = 0;//初始的分数为0
    int pos = start;
    //利用一个布尔数组来记录哪些卡片被拿走
    vector<bool> taken(n, false);
    int cnt = 1;//从1开始数
    while (true) {
        bool found = false;
        int step = 0;
        int original_pos = pos;
        while (step < n) {
            if (!taken[pos] && cards[pos] == cnt) {
                taken[pos] = true;
                score += cards[pos];
                cnt = 1;
                pos = (pos + 1) % n;
                found = true;
                break;
            }
            pos = (pos + 1) % n;
            step++;
            cnt++;
        }
        if (!found) {
            break;
        }
    }
    return score;
}
int main () {
    int n;
    cin >> n;
    vector<int> cards(n);
    for (int i = 0; i < n; i++) {
        cin >> cards[i];
    }
    //尝试每一个起点
    int max = 0;
    for (int start = 0; start < n; start++) {
        int score_max = simulate(cards, start);
        if (score_max > max) {
            max = score_max;
        }
    }
    cout << max << endl;
    return 0;
}