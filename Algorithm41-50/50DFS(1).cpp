//
// Created by zhouyxuiang on 2026/3/19.
//
#include <iostream>
#include <vector>
using namespace std;
class Solution {
private:
    vector<vector<int>> result;//存放所有排列结果
    vector<int> path;//存放当前排列
    void backtracking(vector<int>& nums , vector<bool>& used) {
        if (path.size() == nums.size()) {
            result.push_back(path);
            return;
        }
        //遍历所有数字
        for (int i = 0; i < nums.size(); i++) {
            if (used[i] == true) continue;//数字用过 跳过
            used[i] = true;
            path.push_back(nums[i]);
            backtracking(nums, used);
            path.pop_back();
            used[i] = false;
        }
    }
public:
    vector<vector<int>> permute(vector<int>& nums) {
        result.clear();
        path.clear();
        vector<bool> used(nums.size(), false);
        backtracking(nums, used);
        return result;
    }
};
int main() {
    Solution s;
    vector<int> nums = {1,2,3};
    vector<vector<int>> res = s.permute(nums);
    cout << "所有排列：" << endl;
    for (int i = 0; i < res.size(); i++) {
        cout << "[";
        for (int j = 0; j < res[i].size(); j++) {
            cout << res[i][j];
            if (j < res[i].size() - 1) cout << ",";
        }
        cout << "]" << endl;
    }
    cout << "共 " << res.size() << " 种排列" << endl;
}