//
// Created by zhouyxuiang on 2026/3/13.
//
#include <iostream>
using namespace std;
//归并排序 + 递归
void merge(vector<int> &v , int L,int M, int R);
void process(vector<int> &board , int L , int R) {
    if (L == R) return;
    int mid = (L + R) / 2;
    process(board, L, mid);
    process(board, mid + 1, R);
    merge(board , L , mid , R);
}
void merge(vector<int> &v , int L,int M, int R) {
    vector<int> help;
    help.resize(R-L+1);//等规模的数组
    int i = 0;
    int p1 = L;
    int p2 = M + 1;
    while (p1 <= M && p2 <= R) {
        help[i++] = v[p1] <= v[p2] ? v[p1++] : v[p2++];
    }
    while (p1 <= M) {
        help[i++] = v[p1++];
    }
    while (p2 <= R) {
        help[i++] = v[p2++];
    }
    for (int i = 0; i < help.size(); i++) {
        v[L + i] = help[i];
    }
}
int main () {
    vector<int> board;
    board.resize(6);
    board[0] = 1;
    board[1] = 4;
    board[2] = 3;
    board[3] = 7;
    board[4] = 5;
    board[5] = 6;
    process(board, 0, 5);
    for_each(board.begin(), board.end(), [](int i) { cout << i << " "; });
    return 0;

}