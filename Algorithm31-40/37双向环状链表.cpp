//
// Created by zhouyxuiang on 2026/3/17.
//
#include<iostream>
using namespace std;
struct Node {
    int data;
    //前一个节点
    Node * prev;
    //后一个节点
    Node * next;
};
void addNode(Node **head , int val) {
    Node * newNode = new Node();
    newNode->data = val;
   if (*head == nullptr) {
       newNode->next = newNode;
       newNode->prev = newNode;
       *head = newNode;
   }//不是空指针 直接插在最前面
    else {
       newNode->next = *head;
       newNode->prev = (*head)->prev;
        (*head)->prev->next = newNode;
        (*head)->prev = newNode;
        *head = newNode;
   }
}
void printList(Node * head) {
    if (head == nullptr) return;
    Node * curr = head;
    cout << curr->data << " ";
    curr = curr->next;
    while (curr != head) {
        cout << curr->data << " ";
        curr = curr->next;
    }
    cout << endl;
}
void eraseNode(Node **head , int val) {
    if (*head == nullptr) return;

    Node * curr = *head;
    while (curr->data != val) {
        curr = curr->next;
        if (curr == *head) {
            return;
        }
    }
    if (curr -> next == curr) {
        *head = nullptr;
        return;
    }
    //curr->data就是对应的val 要把curr删除

    curr->next->prev = curr->prev;
    curr->prev->next = curr->next;
    if (*head == curr) {
        *head = curr->next;
    }
}
int main() {
    Node* head = nullptr;
    addNode(&head , 13);
    addNode(&head , 14);
    addNode(&head , 15);
    addNode(&head , 16);
    printList(head);
    eraseNode(&head , 13);
    printList(head);
    eraseNode(&head , 14);
    printList(head);
    return 0;
}