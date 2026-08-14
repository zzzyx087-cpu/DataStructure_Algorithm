//
// Created by zhouyxuiang on 2026/3/18.
//
#include <iostream>
using std::cout;
using std::endl;
struct ListNode {
    ListNode * next;
    int value;
    ListNode(int x) : value(x) , next(nullptr) {};
};
//判断是否成环 以及第一个入环节点
//哈希表实现这个函数

//不用哈希表实现这个函数
//快慢指针
ListNode* getLoop(ListNode* head) {
    //快慢指针
    if (head == nullptr || head->next == nullptr || head->next->next == nullptr) return nullptr;
    ListNode* slow = head->next;
    ListNode* fast = head->next->next;
    while (slow != fast) {
        if (fast->next == nullptr || fast->next->next == nullptr) return nullptr;
        slow = slow->next;
        fast = fast->next->next;
    }
    fast = head;
    while (fast != head) {
        fast = fast->next;
        slow = slow->next;
    }
    return slow;
}
//非环状链表
ListNode* TwoNoLoop(ListNode* head1 , ListNode* head2) {
    if (head1 == nullptr || head2 == nullptr) return nullptr;
    ListNode* cur1 = head1;
    ListNode* cur2 = head2;
    int n = 0;
    while (cur1->next != nullptr) {
        n++;
        cur1 = cur1->next;
    }
    while (cur2->next != nullptr) {
        n--;
        cur2 = cur2->next;
    }
    if (cur1 != cur2) {//此时是最后一个节点 最后一个节点不一样说明一定不一样
        return nullptr;
    }
    cur1 = n > 0 ? head1: head2;//长的是cur1 短的是cur2
    cur2 = cur1==head1 ? head2:head1;
    n = abs(n);
    for (int i = 0; i < n; i++) {
        n--;
        cur1 = cur1->next;
    }
    while (cur1 != cur2) {
        cur1 = cur1->next;
        cur2 = cur2->next;
    }
    //返回相交节点
    return cur1;
}
//两个都是环状链表
ListNode* BothLoop(ListNode * head1 , ListNode * head2 , ListNode * loop1 , ListNode * loop2) {
    //第一种两个完全不相交
    ListNode* cur1 = nullptr;
    ListNode* cur2 = nullptr;
    if (loop1 == loop2) {
        cur1 = head1;
        cur2 = head2;
        int n = 0;
        while (cur1 != loop1) {
            n++;
            cur1 = cur1->next;
        }
        while (cur2 != loop2) {
            n--;
            cur2 = cur2->next;
        }
        cur1 = n > 0 ? head1 : head2;
        cur2 = cur1==head1 ? head2:head1;
        n = abs(n);
        while (cur1 != cur2) {
            cur1 = cur1->next;
            cur2 = cur2->next;
        }
        return cur1;
    }else {
        cur1 = loop1->next;
        while (cur1 != loop1) {
            if (cur1 == loop2) return loop1;
            cur1 = cur1->next;
        }
    }
    return nullptr;
}
int main() {
    cout << "===== 测试 1：两个无环链表 相交 =====" << endl;
    ListNode *n1 = new ListNode(1);
    ListNode *n2 = new ListNode(2);
    ListNode *n3 = new ListNode(3);
    ListNode *n4 = new ListNode(4);
    ListNode *n5 = new ListNode(5);
    n1->next = n2; n2->next = n3; n3->next = n4; n4->next = n5;
    ListNode *m1 = new ListNode(10);
    m1->next = n3;//相交在n3
    ListNode *res1 = TwoNoLoop(n1, m1);
    cout << res1->value << endl;
    cout << "\n===== 测试 3：两个有环链表 相交 =====" << endl;
    ListNode *x1 = new ListNode(1);
    ListNode *x2 = new ListNode(2);
    ListNode *x3 = new ListNode(3);
    ListNode *x4 = new ListNode(4);
    x1->next = x2; x2->next = x3; x3->next = x4; x4->next = x2; // 环入点 x2

    ListNode *y1 = new ListNode(10);
    y1->next = x2; // 相交在环上
    ListNode *res2 = BothLoop(x1,y1,getLoop(x1),getLoop(y1));
    cout << res2->value << endl;
}