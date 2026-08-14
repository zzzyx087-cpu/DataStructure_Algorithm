//
// Created by zhouyxuiang on 2026/3/17.
//
#include <iostream>
using std::cout;
using std::endl;
struct Node {
    Node *next;
    int value;
    Node(int x) : value(x) , next(nullptr) {}
};
Node* listPartition2(Node* head, int pivot) {
    Node* sH = nullptr; // small head
    Node* sT = nullptr; // small tail
    Node* eH = nullptr; // equal head
    Node* eT = nullptr; // equal tail
    Node* mH = nullptr; // big head
    Node* mT = nullptr; // big tail
    Node* next = nullptr; // save next node
    while (head != nullptr) {
        next = head->next;
        head->next = nullptr;//单独拿出来这个head 防止拿出head的时候把head后面的节点都拿出来
        if (head->value < pivot) {
            if (sH == nullptr) {
                sH = head;
                sT = head;
            }else {
                sT->next = head;
                sT = head;
            }
        }else if (head -> value == pivot) {
            if (eH == nullptr) {
                eH = head;
                eT = head;
            }else {
                eT->next = head;
                eT = head;
            }
        }else if (head -> value > pivot) {
            if (mH == nullptr) {
                mH = head;
                mT = head;
            }else {
                 mT->next = head;
                 mT = head;
            }
        }
        head = next;

    }
    if (sT != nullptr) {//拥有小于区
        sT->next = eH;//小于区的尾巴连接等于区的头
        eT = eT == nullptr ? sT:eT;
    }
    if (eT != nullptr) {
        eT->next = mH;
        mT = mT == nullptr ? mT:mT;
    }
    return sH != nullptr ? sH :(eH != nullptr ? eH : mH);
}
void printList(Node* head) {
    if (head == nullptr) {
        cout << endl;
    }
    Node* curr = head;
    while (curr != nullptr) {
        cout << curr->value << " ";
        curr = curr->next;
    }
    cout << endl;
}
void freeList(Node* head) {
    Node* curr = head;
    while (curr != nullptr) {
        Node* next = curr->next;
        delete curr;
        curr =next;
    }
}
int main() {
    Node* head = new Node(3);
    head->next = new Node(1);
    head->next->next = new Node(4);
    head->next->next->next = new Node(2);
    head->next->next->next->next = new Node(5);
    head->next->next->next->next->next = new Node(2);

    // 2. 打印原来的链表
    printList(head);
    Node* p = listPartition2(head, 3);
    cout << "按照3来区分之后" << endl;
    printList(p);
    freeList(p);
}