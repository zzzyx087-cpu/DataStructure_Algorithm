//
// Created by zhouyxuiang on 2026/4/18.
//
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        // 二分范围：最小1，最大是数组里最多的那堆

        int left = 1;
        int right = 0;
        right = *max_element(piles.begin(), piles.end());
        int ans = 0;

        while (left <= right) {
            int mid = left + ((right - left) >> 1); // 防止溢出
            if (f(piles , mid) <= h) {
                ans = mid;
                right = mid - 1;
            }else {
                //不达标去右侧二分 直到二分小时
                left = mid + 1;
            }
        }
        return ans;
    }
    //写个f函数重量都在piles里 速度定成speed 返回吃完耗费的时间
    long f(vector<int>& piles, int speed) {
        //向上取整
        long ans = 0;
        for (int pile : piles) {
            ans += (pile + speed - 1) / speed;//向上取整
        }
        return 1;
    }
};
//画匠问题
//[6,4,5,5]
//每个画家只能画连续的几个画 必须相邻
//只有A B两个画家 对于这个数组就是 10小时完成最好结果
//划分为k份怎么让累加和最小 让每部分的sum尽量小

//范围是0到整个数组的累加和
int f(vector<int>& nums, long aim);
int SplitArray(vector<int>& nums, int k) {
    long sum = 0;
    for (int num : nums) {
        sum += num;
    }
    long ans = 0;
    //开始二分
    //在[0,sum]二分
    for (long l = 0, r = sum,m,need;l <= r;) {
        //让每一部分的累加和<=m 划分成几个部分才够
        ///每一段的和，最大不能超过 m 这个数值。
        m = l + ((r - l) >> 1);
        need = f(nums,m);//把m当作最大容量 需要分成几段
        if (need <= k) {
            ans = m;
            r = m - 1;
        }else {
            l = m + 1;
        }

    }
    return (int)ans;
}
//必须让arr 每一部分的累加和 <= aim划分几个才够
int f(vector<int>& nums, long aim) {
    int parts = 1;
    int sum = 0;
    for (int num : nums) {
        if (num > aim) {
            return INT_MAX;
        }
        if (sum + num > aim) {
            parts++;
            sum = num;
        }else {
            sum += num;
        }
    }
    return parts;
}
//"-----------------------------"
//[1......n]建筑高度
//初始能量的范围就是[0,max]
//[l,r]通关的最小范围 然后不停二分
//max就是最大高度建筑
vector<int> arr;
bool f1(int energy , int max) {
    //如果max很大可能会数值很大 超越long的范围
    //需要减枝
    int n = arr.size();
    for (int i = 1; i <= n; i++) {
        if (energy <= arr[i]) {
            energy -= arr[i] - energy;
        }else {
            energy += energy -= arr[i];
        }
        if (energy >= max) {
            return true;
        }
        if (energy <= 0) {
            return false;
        }

    }

}
int compute(int l , int r, int max) {
    int m,ans = -1;
    while (l <= r) {
        m = l + ((r - l) >> 1);
        if (f1(m,max)) {
            ans = m;
            r = m - 1;
        }else {
            l = m + 1;
        }
    }
    return ans;
}
//----------------------
//同时运行N台电脑的最长时间
//n电脑 表示每一块电池的分钟数 让每一台电脑不断电 返回运行的最长时间
//大于目标时间的先管一台电脑 再算小于等于目标累加和看大不大于目标
//[0 ..... sum]二分 看中间mid能不能达成
bool f3(vector<int> arr,int num, long time){//num是电脑的数量
    long sum = 0;//碎片电池的总和
    for (int x : arr) {
        if (x > time) {//不是碎片电池
            num--;//单独供电
        }else {//x <= time是碎片电池 累计碎片电池的电量
            sum += x;
        }
        if (sum >= (long)num * time) {
            //碎片的电量 >= 台数  * 要求
            return true;
        }

    }
    return false;
}
long maxRunTime(int num, vector<int>& arr) {
    long sum  = 0;
    for (int n : arr) {
        sum += n;
    }
    long ans = 0;
    //开始二分
    for (long l = 0, r = sum,m;l <= r;){
        //m中点
        m = l + ((r - l) >> 1);
        if (f3(arr,num,m)) {
            ans = m;
            l = m + 1;
        }else {
            r = m - 1;
        }
    }
    return ans;
}
//------------------
//计算等位时间
//一个数组的长度为n表示服务一个客人的时间
//给一个正数m表示m个人在等位 如果你是刚来的人 请问你需要等多久 返回等待的时间
//m >> n
//n <= 10 ^ 3,m <= 10 ^ 9最优解

//遵循有空位就上的原则
//先估计最长的时间假设先让时间最短的让一个服务员提供服务
int f4(vector<int> arr, int time) {
    int guest = 0;
    for (int num : arr) {
        guest += (time / num) + 1;//加一的原因是说明已经开始服务了
    }
    return guest;
}
int reserve(vector<int> arr, int w) {
    //前面有w个人
    int Min = INT_MAX;
    for (int x : arr) {
        Min = min(x,Min);
    }
    int ans = 0;
    for (int l = 0,r = Min * w,m;l <= r;) {
        m = l + ((r - l) >> 1);
        if (f4(arr,m) >= w + 1) {
            ans = m;
            r = m - 1;
        }else {
            l = m + 1;
        }
    }
    return ans;
}



//------------
//刀砍毒杀怪兽题目
//怪兽初始血量为hp
//刀没有后续效果 毒有后续效果后面每一回合扣血
//只能选刀或者毒
//返回最快杀死怪兽时间
//两个长度为n的数组 n个回合 选毒就必死
//范围就是[1 ~ HP + 1]
bool f5(vector<int> &cuts,vector<int> &poisons, int hp,int limit) {//不超过f5函数这个值让怪兽必须死
    //limit回合的限制
    int n = min((int)cuts.size(),hp);
    for (int i = 0,j = 1; i < n; i++,j++) {
        hp -= max((long)cuts[i],(long)(limit - j) * (long)poisons[i]);

        if (hp <= 0) {
            return true;
        }
    }
    return false;
}
int fast (vector<int> &cuts,vector<int> &poisons, int hp) {
    int ans = INT_MAX;
    for (int l = 1,r = hp + 1,m;l <= r;) {
        m = l + ((r - l) >> 1);//一定要让在m回合内死掉
        if (f5( cuts,poisons, hp,m)) {
            ans = m;
            r = m - 1;
        }else {
            l = m + 1;
        }
    }
    return ans;
}





