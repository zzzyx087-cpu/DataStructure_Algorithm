//
// Created by zhouyxuiang on 2026/4/13.
//
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;
//计算索引 left和right之间sums的和

//给一个数组[3,2,-2,3,1,1,1,0,6,5,1]
//让子数组相加=6 尽量长的子数组返回
//让每个位置结尾向左边延伸达到6的最大长度
//假设aim=100 total=1000 让前缀和最快达到900就是最长
//用hashmap记录前缀和 某一个前缀和最早出现记录记录0这个和 返回-1
const int MAXN = 100001;
int arr[MAXN];
int n,aim;
unordered_map<int,int> mp;
int compute1(){
    mp.clear();
    mp[0] = -1;
    int ans = 0;
    int sum = 0;
    //map<前缀和, 下标>
    for (int i = 0; i < n; i++) {
        sum += arr[i];//计算前缀和
        //找到了
        if (mp.find(sum - aim) != mp.end()) {
            ans = max(ans,i - mp[sum - aim]);
        }
        //没找到
        if (mp.find(sum) == mp.end()) {
            mp[sum] = i;
        }
    }
    return ans;

}
//无序数组中累加和为给定值的子数组数量
//看几个累加和是sum - aim
int compute2() {
    unordered_map<int,int> mp2;
    mp2.clear();
    //0这个前缀和在没有任何数字的情况下已经有一次了
    mp2[0] = 1;
    int ans = 0;
    int sum = 0;
    //sum是0～i的前缀和
    //key表示前缀和 value表示出现了几次
    for (int i = 0; i < n; i++) {
        sum += arr[i];
        if (mp2.find(sum - aim) != mp2.end()) {
            ans += mp[sum - aim];
        }
        mp[sum] ++;
    }
    return ans;
}
//返回无序数组中正数和负数个数相等最长子数组长度
int compute3(vector<int>& num) {
    //子数组正负一样多
    //正数认为是 0是0 负数认为是-1 让他累加和为0最长数组

    unordered_map<int,int> mp3;
    mp[0] = -1;
    int maxLen = 0;
    int sum = 0;
    for (int i = 0; i < num.size(); i++) {
        if (num[i] > 0) {
            num[i] = 1;
        } else if (num[i] < 0) {
            sum -= 1;   // 负数 -1
        }
        if (mp3.find(sum) != mp3.end()) {
            maxLen = max(maxLen,i - mp3[sum]);
        }else {
            mp3[sum] = i;
        }
    }
    return maxLen;
}
//大于8的时间的天数严格大于下雨等于8的时间的个数
//>8 +1 and <=8 -1
int compute3(vector<int>& num) {
    //map记录的是某个前缀和最早出现的位置
    unordered_map<int,int> mp;
    mp[0] = -1;
    int ans = 0;
    int sum = 0;
    for (int i = 0; i < num.size(); i++) {
        sum += num[i] > 8 ? 1 : -1;
        if (sum > 0) {
            ans = i + 1;
        }else {//sum <= 0
            if (mp.find(sum - 1) != mp.end()) {
                ans = max(ans,i - mp[sum]);
            }
            if (mp.find(sum) == mp.end()) {
                mp[sum] = i;
            }
        }

    }
    return ans;
}