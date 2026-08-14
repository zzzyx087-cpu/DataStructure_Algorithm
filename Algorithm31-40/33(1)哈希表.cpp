//
// Created by zhouyxuiang on 2026/3/16.
//
#include<iostream>
#include <unordered_map>
#include <unordered_set>
using namespace std;
//学习哈希表
//有两种核心结构
//1.只有key 没有value用unordered_set
//2.有key 有value 用unordered_map
//增（put）、删（remove）、改（put）、查（get）操作平均时间复杂度为 O (1)，但常数开销相对较大。
//题型一 判断数组里有没有重复数字
void test01() {
    // 要检查的数组
    vector<int> nums = {1, 2, 3, 4, 2};

    // 哈希表：用来记录已经见过的数字
    unordered_set<int> seen;

    // 遍历数组
    for (int i = 0; i < nums.size(); i++) {
        int current = nums[i];

        // 如果已经见过 → 重复
        if (seen.count(current)) {
            cout << "Has duplicate" << endl;
        }

        // 没见过，加入哈希表
        seen.insert(current);
    }

    cout << "No duplicate" << endl;
}
//题型二 统计每个数字出现的次数
void test02() {
    vector<int> nums = {1, 2, 2, 3, 3, 3};

    // key：数字  value：出现次数
    unordered_map<int, int> countMap;

    for (int i = 0; i < nums.size(); i++) {
        int num = nums[i];
        countMap[num] = countMap[num] + 1;
    }

    // 遍历输出结果
    for (auto& item : countMap) {
        cout << item.first << " : " << item.second << endl;
    }

}
//题型三 差找一个数字在不在数组中
void test03() {
    vector<int> nums = {1, 3, 5, 7};
    unordered_set<int> st;

    // 全部存入哈希表
    for (int i = 0; i < nums.size(); i++) {
        st.insert(nums[i]);
    }

    // 查找 5 是否存在
    if (st.count(5)) {
        cout << "5 exists" << endl;
    } else {
        cout << "5 not found" << endl;
    }
}
//题型四 两数字之和
void test04() {
    vector<int> nums = {2, 7, 11, 15};
    int target = 9;

    unordered_map<int, int> map;

    for (int i = 0; i < nums.size(); i++) {
        int current = nums[i];
        int need = target - current;

        // 如果需要的数字已经存在
        if (map.count(need)) {
            cout << "Found: " << need << " + " << current << " = " << target << endl;
        }
        // 把当前数字存入哈希表
        map[current] = i;
    }

}
int main() {
    unordered_map<int ,string> mp;
    mp[1] = "小明";
    mp[2] = "小红";
    mp[3] = "邢诗雨";
    mp.insert({4, "小李"});
    //1.通过key 拿 value
    cout << mp[1] << endl;
    //2.判断key是否存在
    if (mp.count(2)) {
        cout << mp[2] << endl;
    }
    //3.删除
    mp.erase(3);
    //4. 遍历（最重要！必须会）
    for (auto& pair : mp) {
        cout << pair.first << " : " << pair.second << endl;
    }
    unordered_set<int> st;

    // 插入
    st.insert(10);
    st.insert(20);
    st.insert(20); // 重复，自动忽略
    st.insert(30);
    st.insert(40);
    // 查找
    if (st.count(10)) {
        cout << "10 存在" << endl;
    }

    // 删除
    st.erase(20);

    // 遍历
    for (int x : st) {
        cout << x << endl;
    }
    test01();
    test02();
    test03();
    test04();
    return 0;
}