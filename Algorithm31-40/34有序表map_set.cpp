//
// Created by zhouyxuiang on 2026/3/16.
//
#include <iostream>
#include <algorithm>
#include <map>
#include <set>
using namespace std;
int main() {
    // 对应 Java TreeMap<Integer, String>
    map<int, string> treeMap1;

    // 对应 put(key, value)
    treeMap1[7] = "我是7";
    treeMap1[5] = "我是5";
    treeMap1[4] = "我是4";
    treeMap1[3] = "我是3";
    treeMap1[9] = "我是9";
    treeMap1[2] = "我是2";
    cout << (treeMap1.count(5) ? "true" : "false") << endl;
    // 对应 get(5)
    cout << treeMap1.at(5) << endl;
    // 对应 firstKey()
    cout << treeMap1.begin()->first << ", 我最小" << endl;
    // 对应 lastKey()
    cout << treeMap1.rbegin()->first << ", 我最大" << endl;
    // 对应 floorKey(8)
    auto it_floor = treeMap1.upper_bound(8);
    if (it_floor != treeMap1.begin()) {
        --it_floor;
        cout << it_floor->first << ", 在表中所有<=8的数中，我离8最近" << endl;
    }
    // 对应 ceilingKey(8)
    auto it_ceil = treeMap1.lower_bound(8);
    if (it_ceil != treeMap1.end()) {
        cout << it_ceil->first << ", 在表中所有>=8的数中，我离8最近" << endl;
    }
    // 对应 remove(5)
    treeMap1.erase(5);
    cout << (treeMap1.count(5) ? "true" : "false") << endl;
    return 0;
}