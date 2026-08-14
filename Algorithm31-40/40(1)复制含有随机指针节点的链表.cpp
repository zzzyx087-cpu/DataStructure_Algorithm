//
// Created by zhouyxuiang on 2026/3/17.
//
#include <iostream>
using namespace std;

// 链表节点定义
struct Node {
    int val;
    Node *next;
    Node *random;
    Node(int x) : val(x), next(nullptr), random(nullptr) {}
};

// 原地复制法（O(1) 空间）
Node* copyRandomList(Node* head) {
    if (!head) return nullptr;

    // ===== 第一步：插入复制节点 =====
    Node* cur = head;
    while (cur) {
        Node* newNode = new Node(cur->val);
        newNode->next = cur->next;
        cur->next = newNode;
        cur = newNode->next;
    }

    // ===== 第二步：复制 random 指针 =====
    cur = head;
    while (cur) {
        Node* newNode = cur->next;
        if (cur->random) {
            newNode->random = cur->random->next;
        }
        cur = newNode->next;
    }

    // ===== 第三步：拆分链表 =====
    cur = head;
    Node* newHead = head->next;

    while (cur) {
        Node* newNode = cur->next;
        cur->next = newNode->next;
        cur = cur->next;

        if (newNode->next) {
            newNode->next = newNode->next->next;
        } else {
            newNode->next = nullptr;
        }
    }

    return newHead;
}

// 打印链表（验证用）
void printList(Node* head) {
    Node* cur = head;
    while (cur) {
        cout << "节点值: " << cur->val;
        if (cur->random) {
            cout << " | random 指向: " << cur->random->val;
        } else {
            cout << " | random 指向: NULL";
        }
        cout << endl;
        cur = cur->next;
    }
}

// 释放链表内存（解决内存泄漏）
void freeList(Node* head) {
    Node* cur = head;
    while (cur) {
        Node* next = cur->next;
        delete cur;
        cur = next;
    }
}

// ======================
// main 函数（无任何警告）
// ======================
int main() {
    // 构建链表 1 -> 2 -> 3
    Node* head = new Node(1);
    Node* node2 = new Node(2);
    Node* node3 = new Node(3);

    head->next = node2;
    node2->next = node3;

    // 设置 random
    head->random = node3;
    node2->random = head;
    node3->random = node2;

    cout << "===== 原链表 =====\n";
    printList(head);

    // 复制
    Node* newHead = copyRandomList(head);

    cout << "\n===== 复制后的新链表 =====\n";
    printList(newHead);

    // 释放内存（完全不泄漏）
    freeList(head);
    freeList(newHead);

    return 0;
}