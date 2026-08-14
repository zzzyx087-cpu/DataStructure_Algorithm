//
// Created by zhouyxuiang on 2026/3/20.
//
#include <iostream>
using namespace std;
class Node {

};
//递归过程中 来到了某一个节点
//i是节点层数 N是一共的层数 down == true 凹 down == false 凸
void printProcess(int i , int N , bool down) {
    if (i > N) return;
    printProcess(i + 1, N, true);
    string s = down ? "凹" : "凸" ;
    cout << s << " ";
    printProcess(i + 1 , N , false);
}
int main() {
    int N = 3;
    printProcess(1,N,false);

}