//
// Created by zhouyxuiang on 2026/3/27.
//
#include <iostream>
using namespace std;
int n;
const int N = 20;
int mem[N];
//记忆化搜索
int f(int x) {
    if (x < 1 || x >= N) {
        return -1;
    }
    if (mem[x] != -1) return mem[x];

    int sum = 0;
    if (x == 1) sum = 1;
    else if (x == 2) sum = 2;
    else sum = f(x - 1) + f(x - 2);
    mem[x] = sum;
    return sum;
}

//递推形式
int n2;
int const N2 = 20;
int f2[N2];



//时间复杂度O(2<<n)2的n次方
//空间复杂度 跟树的高度有关O(h)
int main (){
    for (int i = 0; i < N; ++i) {
        mem[i] = -1;
    }
    cin >> n;
    int res  = f(n);
    cout << res << endl;
    f2[1] = 1, f2[2] = 2;
    for (int i = 3 ; i <= n ; ++i) {
        f2[i] = f2[i - 1] + f2[i - 2];//递推公式就是dfs向下递推的公式
                // the easiet dp
    }
    cin >> n2;
    cout << f2[n2] << endl;
    int newf , temp1 =1, temp2 = 2;
    int n3;
    cin >> n3;
    for (int i = 3; i < n3; ++i) {
        newf = temp1 + temp2;
        temp1 = temp2;
        temp2 = newf;
    }
}