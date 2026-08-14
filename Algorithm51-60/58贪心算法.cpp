//
// Created by knight
#include <iostream>
using namespace std;
//贪心算法
//活动调度 安排项目
struct Program {
    int start;
    int end;

};
//排序规则 按照结束时间 从小到大排序(贪心算法的核心)
bool compare(const Program &a, const Program &b) {
    return a.end < b.end;
}
int bestArrange(vector<Program> programs , int timePoint) {
    sort(programs.begin(), programs.end(), compare);
    int result = 0;
    for (int i = 0; i < programs.size(); i++) {
        if (timePoint <= programs[i].start) {

            result++;

            timePoint = programs[i].end;
        }
    }
    return result;
}
int main() {

}