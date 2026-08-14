//
// Created by zhouyxuiang on 2026/3/3.
//
#include <iostream>
using namespace std;
struct ListNode {
    int val;//节点储存的值
    ListNode *next;//指向下一个节点的指针
    //三种构造函数 (方便构造节点)
    ListNode():val(0),next(nullptr){}//无参构造
    ListNode(int x) : val(x), next(nullptr) {}             // 传值构造，值为x，next为空
    ListNode(int x, ListNode *next) : val(x), next(next) {}// 传值+下一个节点构造
};
class Solution {
    public:
    ListNode* addTwoNumbers(ListNode* L1 , ListNode* L2) {
        ListNode* dummy = new ListNode(0);
        ListNode* curr = dummy;
        int carry = 0;
        while (L1 != nullptr|| L2 != nullptr || carry != 0) {
            int sum = carry;
            if (L1 != nullptr) {
                sum += L1->val;
                L1 = L1->next;
            }if (L2 != nullptr) {
                sum += L2->val;
                L2 = L2->next;
            }
            carry = sum / 10;
            curr->next = new ListNode(sum % 10);
            curr = curr->next;
        }
        return dummy;
    }
};

int main() {
    ListNode* L1 = new ListNode(2);
    L1->next = new ListNode(4);
    L1->next->next = new ListNode(3);
    ListNode* L2 = new ListNode(5);
    L2->next = new ListNode(6);
    ListNode* L3 = new ListNode(4);
    Solution sol;
    ListNode* result = sol.addTwoNumbers(L1, L2);
    while (result != nullptr) {
        cout << result->val << endl;
        result = result->next;
    }
    return 0;
}