//
// Created by zhouyxuiang on 2026/3/17.
//
#include<iostream>
using std::cout;
using std::endl;
struct Node {
    int data;
    Node* next;
};
void insertFromeHead(Node** head, int val) {
    //创建环状链表
    Node* newNode = new Node;
    newNode->data = val;
    if (*head == nullptr) {
       //空链表自己指向自己
        newNode->next = newNode;
        *head = newNode;
   }else {
       //正常头插法
       Node* curr = *head;
       while (curr->next != *head) {
           curr = curr->next;
       }
       newNode->next = *head;
       curr->next = newNode;
       *head = newNode;
   }
}
void printList(Node* head) {
    if (head == nullptr) return;
    Node* curr = head;
    cout << curr->data << " ";
    curr = curr->next;
    while (curr != head) {
        cout << curr->data << " ";
        curr = curr->next;
    }
    cout << endl;
}
int main() {
    //添加数据
    Node* head = nullptr;
    insertFromeHead(&head, 10);
    insertFromeHead(&head, 20);
    insertFromeHead(&head, 30);
    insertFromeHead(&head, 40);
    printList(head);
}