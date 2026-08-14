//
// Created by zhouyxuiang on 2026/3/27.
//
#include <iostream>
using namespace std;
//输入5 3
//输出
//有1 2 3 4 5 可以填充进来

//后面的数字始终大于前面的数字
//剪枝过程 减少递归次数
//减去一个树枝
//1.全局变量
//2.形参

//int x记录枚举到的位置
//int arr[N] 记录都选了哪些数字
//int start 记录当前位置从哪里开始枚举
const int N = 21;
int arr[N];
int r,n;

void dfs(int x , int start) {
    if (x > r) {
        for (int i = 1; i <= r; i++) {
            cout << arr[i];
        }

        cout << " " << endl;
        return;
    }
    for (int i = start ; i <= n - (r - x); i++) {
        arr[x] = i;
        dfs(x + 1, i + 1);
        arr[x] = 0;
    }
}
bool is_prim(int x) {
    if (x == 1) return false;
    if (x == 2) return true;
    for (int i = 2; x <= i * i; i++) {
        if (x % i == 0) {
            return false;
        }
    }
    return true;
}
//从n个整数任意取k个整数相加 得到和 输出为素数的个数
const int N2 = 30;
int n2 , k;
int q[N2];
int arr1[N2];
int res = 0;
void dfs2(int x , int start) {
    if (x + n - start < k) {
        return;
    }
    if (x > k) {

        int sum = 0;
        for (int i = 0; i <= k ; i++) {
            sum += arr[i];
        }if (is_prim(sum)){
            res++;
        }

    }
    for (int i = start ; i <= n ; i++) {
        arr1[x] = q[i];
        dfs2(x + 1, i + 1);//继续向下 深度优先
        arr[x] = 0;
    }
}
int main() {
    // cin >> n;
    // cin >> r;
    // dfs(1,1);
    cin >> n2 >> k;
    dfs2(1, 1);
    cout << res << endl;
}