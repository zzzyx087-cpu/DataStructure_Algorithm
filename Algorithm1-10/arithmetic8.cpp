//
// Created by zhouyxuiang on 2026/3/7.
//
#include <iostream>
using namespace std;

class Solution {
public:
    //中心扩散法
    string longestPalindrome(string s) {
        if (s.empty()) return "";
        int start = 0 , maxLen = 1;
        int n = s.length();
        //遍历每一个可能的回文数中心
        for (int i = 0; i < n; i++) {
            //奇数长度中心
            int left = i , right = i;
            while (left >= 0 && right < n && s[left] == s[right]) {
                if (right - left + 1> maxLen) {
                    start = left;
                    maxLen = right - left + 1;
                }
                left --;
                right ++;
            }
            //偶数长度中心
            left = i , right = i + 1;
            while (left >= 0 && right < n && s[left] == s[right]) {
                if (right - left + 1> maxLen) {
                    start = left;
                    maxLen = right - left + 1;
                }
                left --;
                right ++;
            }
        }
        return s.substr(start, maxLen);
    }

};
int main() {

    Solution obj;
    string s1 = "abcdcb";
    cout<<obj.longestPalindrome(s1)<<endl;;

    return 0;
}