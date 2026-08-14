//
// Created by zhouyxuiang on 2026/4/8.
//
#include <iostream>
using namespace std;
//一段数组 要在窗口增加数字R++增加数字
//窗口减少数字L++左闭右闭
//题目1
//累加和大于target的最短数组的长度
//给一个含有n个正整数的数组和一个正整数
//找到累加和>=target长度最小的子数组
//看能不能让下一个数字出去
int Window1(int target , vector<int>& nums) {
    int ans = INT_MAX;

   int l = 0;
    int sum = 0;
    for (int r = 0; r < nums.size(); ++r) {
        sum += nums[r];
        while (sum - nums[l] > target) {
            sum -= nums[l];
            l = l + 1;
        }
        if (sum >= target) {
            ans = min(ans, r - l + 1);
        }
    }
    return ans == INT_MAX ? 0 : ans;

}
//题目2
//无重复字符的最大子串
//连续 且 无重复字符
int NoRepeatString(string &str) {
    //如果左边界触碰到了一个重复的字符 就更新L的位置
    vector<int> last(256,-1);//记录每个位置最后出现的位置
    //ASCII总共为0 ~ 255

    int max_len = 0;
    int left = 0;
    for (int right = 0; right < str.length(); ++right) {
        left = max(left,last[str[right]] + 1);
        //更新最大长度
        max_len = max(max_len,right - left + 1);
        last[str[right]] = right;
    }
return max_len;

}
//题目3 最小覆盖子串
//无所谓顺序 只要包含target的字符串就行
string minWindow(string str, string tar) {
    //做一个欠债表 哈希表或者数组
    //每一个字符 对应欠5的数字
    //str还无关的字符 不会改变总负债
    //cnt[i] = 负数i有负债
    //cnt[i] = 正数i有盈余
    vector<int> cnts(256,0);
    for (int r = 0; r < tar.length(); ++r) {
        cnts[tar[r]]--;
    }
    //最小覆盖子串的长度
    int len = INT_MAX;
    int start = 0;
    //总债务
    int debt = tar.length();
    for (int l = 0,r = 0;r < str.length(); ++r) {
        if (cnts[str[r]]++ < 0) debt--;
        if (debt == 0) {
            //向右滑动 看是否盈余
            while (cnts[str[l]] > 0) {
                cnts[str[l]]--;
                l++;
            }
            if (r - l + 1 < len) {//更新答案
                len = r - l + 1;
                start = l;
            }
        }
    }
    return len == INT_MAX ? " " : str.substr(start,len);
}
//题目4加油站良好出发点
//在一条环路上 有n个加油站其中第i个加油站有汽油gas[i]升
//你有一辆容量无限的汽车 从i到i+1需要cost[i]升汽油
//开始时为空 从其中一个加油站出发
//给两个整数数组 如果可以按顺序绕路行驶一周 泽返回出发时的加油站的编号 否则返回1
int PetrolStation(vector<int> gas,vector<int> cost) {
    //设置一个余数组 从一个点出发计算累加和
    //再复制二倍的数组 从2跳到1相当于从2跳到7
    int n = gas.size();
    //本来下标是从0...n-1,扩充到0...2n-1,i位置的余信息在(r%n)的位置
    //窗口范围时[l,r)左闭右开
    //[a,b,c,d,e a,b,c,d,e]
    //[0,1,2,3,4,5,6,7,8,9]
    //sum是累加和

    for (int l = 0, r = 0,sum; l < n; l = r + 1,r = l) {
        //l = 0, r = 0窗口没有数字
        sum = 0;
        while (sum + gas[r % n] - cost[r % n] >= 0) {
            if (r - l + 1 == n) {//此时检查转了一圈
                return l;
            }//不成立没有转一圈
            sum += gas[r % n] - cost[r % n];
            r++;
        }
    }
    return -1;
}
//题目5
//替换子串得到平衡字符串
//有只含有QWER四种字符 且长度为n的字符串 n一定为4的整数倍 假如在一个字符串中 这四个字符都恰好出现n/4次
//那么它就是一个 平衡字符串 给一个字符串S通过替换一个子串的方式
//使元字符串S变成一个平衡字符串
//返回替换的最小可能长度
//s = 40
//Q = 4 W = 12 E = 14 K = 10
//Q -- 0 W -- 1 E -- 2 R -- 3
int balancedString(string s) {
    int n = s.length();
    vector<int> S(n);
    vector<int> cnts(4);//记录的是4个字母的欠债情况
    for (int i = 0; i < n; i++) {
        char c = s[i];
        s[i] = c == 'W'?1:(c == 'E'?2:(c == 'R'?3:0));
        cnts[s[i]]++;
    }
    int debt = 0;
    for (int i = 0;i < 4;i++) {
        if (cnts[i] < n / 4) {
            cnts[i] = 0;
        }else {
            cnts[i] = n / 4 - cnts[i];
            debt -= cnts[i];
        }
    }
    if (debt == 0) return 0;
    int ans = INT_MAX;
    for (int l = 0 , r = 0; r < n; r++) {
        if (cnts[s[r]]++ < 0) debt--;//先判断大小再自增
        if (debt == 0) {
            while (cnts[s[r]] > 0) {//让前面的l开始向后收缩
                cnts[s[l]]--;
                l++;
            }
            ans = min(ans, r - l + 1);
        }
    }
    return ans;
}
//题目6
//k
//含有k个不同整数的子数组
//设置一个函数用 (<=k的个数) - (<=k-1的个数)就行了
//arr中的数字都在0～n之间
int MAXN = 200001;
vector<int> cnts(MAXN);
int numsOfMostKinds(vector<int> arr,int k) {
    int ans = 0;
    fill(cnts.begin() + 1, cnts.end(), 0);
    for (int l = 0, r = 0,collect =0;r < arr.size();r++) {
        //r表示进入窗口意味增加种类
        if (++cnts[arr[r]] == 1) {
            collect++;
        }
        //l ~ r要求不超过3种 已经4中 l向右
        while (collect > k) {
            if (--cnts[arr[l++]] == 0) {
                collect--;
            }
        }

       ans += r - l + 1;
        //l...r不超时了
        //0~3
        //.. 3~3
    }
    return ans;
}
int sbuArrayWithDistinct(vector<int> arr, int k) {
    return numsOfMostKinds(arr,k) - numsOfMostKinds(arr,k - 1);
}
//题目7
//至少有k个重复字符的最长子串
//不能普通的滑动窗口做
//先固定窗口里最多有的几种不同的字符 再滑动窗口
//子串必须只有1种字符 >= k次 最长多长
// 只有2种
// 只有3种......一直到26种

int longestSubstring(string str , int k) {
     int n = str.length();
    vector<int> cnts(256,0);
     int ans = 0;
    //每次必须要求子串必须含有require种字符 每种必须大于等于k次
    for (int require = 1; require <= 26; require++) {
        fill(cnts.begin() + 1, cnts.end(), 0);
        for (int l = 0,r = 0,collect =0,satisfy = 0;r < n; r++) {
            //collect收集到的种类数
            //satisfy达标的种类数(字符次数>=k)
            cnts[str[r]]++;
            if (cnts[str[r]] == 1) collect++;
            if (cnts[str[r]] == k) satisfy++;//关于收集到的种类与达标的种类
            while (collect > require) {//种类超了
                //l位字符吐出来
                if (cnts[str[l]] == 1) {
                    collect--;
                }
                if (cnts[str[l]] == k) {
                    satisfy--;
                }
                cnts[str[l]]--;
                l++;
            }
            //l到r子串以r位的字符结尾 种类不超为最大长度
            if (satisfy == require) {
                ans = max(ans, r - l + 1);
            }
        }
    }
    return ans;
}




