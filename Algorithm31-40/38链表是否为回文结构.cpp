//
// Created by zhouyxuiang on 2026/3/17.
//
#include <iostream>
using namespace std;
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int val) {
        this->val = val;
        next = nullptr;
    }
};
// 1. 先写好反转函数
ListNode* reverseList(ListNode* head) {
    ListNode* prev = nullptr;
    ListNode* curr = head;
    while (curr) {
        ListNode* next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}

// 2. 判回文主函数（超级干净）
bool isPalindrome(ListNode* head) {
    if (!head || !head->next) return true;

    // 快慢指针找中点
    ListNode* slow = head;
    ListNode* fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    // 直接调用 reverse！你说得对！
    ListNode* right = reverseList(slow);

    // 左右比对
    ListNode* left = head;
    while (right) {
        if (left->val != right->val) return false;
        left = left->next;
        right = right->next;
    }

    return true;
}
int main() {
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(3);
    head->next->next->next->next->next = new ListNode(2);
    head->next->next->next->next->next->next = new ListNode(1);
    if (isPalindrome(head)) {
        cout<<"true"<<endl;
    }else {
        cout<<"false"<<endl;
    }
}