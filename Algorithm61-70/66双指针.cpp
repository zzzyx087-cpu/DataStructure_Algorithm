//
// Created by zhouyxuiang on 2026/4/10.
//
#include <iostream>
using namespace std;
//大前提 双指针
//题目1
//奇偶数字归位
vector<int> sortArray(vector<int>& nums) {
    int n = nums.size();
    for (int odd = 1 , even = 0; odd < n && even < n;) {
        if ((nums[n - 1] & 1) == 1) {
            swap(nums[odd],nums[n-1]);
            odd+=2;
        }else {
            swap(nums[even],nums[n-1]);
            even+=2;
        }
    }
    return nums;
}
//题目2
//寻找重复数
//有n+1的大小数字的大小在1-n上
//返回这个重复的数字
//[1,2,3,3]返回3
//[0,1,2,3]
//0 -> 1 -> 2 -> 3 -> 3重复
//快慢指针来做 实现找环的作用
int fastAndslow(vector<int> nums) {
    if (nums == NULL || nums.size() < 2) {
        return -1;
    }
    int slow = nums[0];
    int fast = nums[nums[0]];
    while (fast != slow) {
        slow = nums[slow];
        fast = nums[nums[fast]];
    }
    fast = 0;
    while (fast != slow) {
        fast = nums[fast];
        slow = nums[slow];
    }
        return slow;
}
//3.接雨水
//天上留下了很多水看哪些会留下来
int Rain(vector<int> rain) {
    //1.辅助数组的解法
    int n = rain.size();
    vector<int> lmax (n);
    vector<int> rmax (n);
    lmax[0] = rain[0];
    //0~i范围的最大值记录在lmax
    //i~n-1范围的最大值在rmax
    for (int i = 1; i < n; i++) {
        lmax[i] = max(lmax[i-1], rain[i]);
    }
    int ans = 0;
    for (int i = 1; i < n - 1; i++) {
        ans += max(0,min(lmax[i-1],rmax[i+1]) - rain[i]);
    }
    return ans;

}
//双指针法
int rain2(vector<int> rain) {
    int n = rain.size();
    int l = 1;
    int r = n - 2;
    int lmax = rain[0] , rmax = rain[n-1];
    int ans = 0;
    while (l <= r) {
        if (lmax <= rmax) {
            ans += max(0,lmax - rain[l]);
            lmax = max(lmax,rain[l++]);
        }else {
            ans += max(0,rmax - rain[r]);
            rmax = max(rmax,rain[r--]);
        }
    }
    return ans;
}
//题目4救生艇
//给定数组people people[i]表示i个人
//承载最大重量limit return最小船数
int boat(vector<int> Pp,int limit) {
    sort(Pp.begin(), Pp.end());//排序再双指针
    int n = Pp.size();
    int l = 0,r=n-1;
    int sum = 0;
    int ans = 0;
    while (l <= r) {
        sum =l == r?Pp[l]:Pp[r] + Pp[l];
        if (sum > limit) {
            r--;
        }else {
            l++;
            r--;
        }
        ans++;
    }
    return ans;
}
//题目5长度为n的整数数组height
//n条垂线 i条的两个端点实际(i,0)(i,height[i])
//找出两条线 使他们是x轴共同构成的容器容纳最多的水
//返回最大储水量
//[1,8,6,2,5,4,8,3,7]
//输出49
int vector1(vector<int> height) {
    int ans = 0;
    for (int l = 0,r = height.size()-1;l < r;){
        ans = max(ans,min(height[l],height[r]) * (r - l));
        if (height[l] <= height[r]) {
            l++;
        }else {
            r--;
        }
    }
    return ans;
}
//题目6供暖器
//设计一个有固定加热半径的供暖器来供暖
//给出位于一条水平线上的房屋house和供暖器heaters的位置
//返回可以覆盖所有房屋的最小加热半径
//houses=[1,2,3] heaters=[2]
//输出1
bool best(vector<int> heaters,vector<int> houses,int i,int j) ;
int heaters(vector<int> heaters,vector<int> houses) {
    sort(houses.begin(), houses.end());
    sort(heaters.begin(), heaters.end());
    int ans = 0;
    for (int i = 0,j = 0;i < houses.size(); i++) {
        //i号房屋与j号供暖器
        while (!best(heaters, houses,i,j)) {
            j++;
        }
        ans = max(ans,abs(houses[i] - heaters[j]));
    }
    return ans;
}
bool best(vector<int> heaters,vector<int> houses,int i,int j) {
    return j == heaters.size() - 1|| abs(heaters[j] - houses[i] < abs(heaters[j+1] - houses[i]));
}
//题目7给一个为排序的整数数组nums 找出其中没有出现的最小正整数
//让左边的数组的数字都是i=i+1
//arr[l] = l + 1 l++
//a[l] <= l
//a[l] > r
//a[a[l]-1] == all[l]该去的位置跟原本想要排的位置一样
//交换到垃圾去
//[-3,2,1,8,5,4,2,3,5,13]
void swap(vector<int> &arr,int i,int j) ;
int TrashZoo(vector<int> nums) {
    int ans = 0;
    int l = 0;
    //l的左边都是做到了i位置放着i+1的区域
    //永远盯着l位置的数字看能不能扩充
    int r = nums.size();
    //从r到最右边都是垃圾区
    //最好状况是都能收集到
    while (l < r) {
        if (nums[l] == l+1) {
            l++;
        }else if (nums[l] <= l|| nums[l] > r || nums[nums[l]-1] == nums[l]) {
            swap(nums,l,--r);
        }else {
            swap(nums,l,nums[l] - 1);
        }
    }
    return l + 1;
}
void swap(vector<int> &arr,int i,int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}
