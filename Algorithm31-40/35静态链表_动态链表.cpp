//
// Created by zhouyxuiang on 2026/3/16.
//
#include<iostream>
using std::cout;
using std::endl;
//链表 由节点组成
//定义一个节点
struct node {
    int data;
    node *next;//保存下一个节点的地址
};
//循环遍历链表
void printList(node* point ) {
    while (point != nullptr) {
        //读数据
        cout << point->data << " ";
        //point 偏移
        point = point->next;
    }
    cout << endl;
}
//递归遍历链表 recursion
void printList2(node* point ) {
    if (point != NULL) {
        cout << point->data << " ";
        point = point->next;
        printList2(point);
    }
    cout << endl;
}
//后插法函数
//data插入的位置
int insertListBehind(node * point,int data,struct node* newnode) {
    while (point != NULL) {
        if (point->data == data) {
            newnode->next = point->next;
            point->next = newnode;
            return 1;
        }
        //point 偏移
        point = point->next;
    }
    return 0;
}
//前插法函数
node* insertBefore(node* head, int target, node* newnode)
{
    // 情况1：要插在 第一个节点 前面
    if (head->data == target)
    {
        newnode->next = head;
        return newnode; // 新节点变成头
    }

    // 情况2：找 target 前面的节点
    node* current = head;

    while (current->next != NULL)
    {
        // 找到 target 了
        if (current->next->data == target)
        {
            // 前插核心两行
            newnode->next = current->next;
            current->next = newnode;
            return head;
        }

        // 继续往后走
        current = current->next;
    }

    // 没找到，返回原来的链表
    return head;
}
//前插法二级指针实现
void insertFront(node** head , int targetVal,node * newNode    ) {
   if (*head == nullptr || (*head)-> data == targetVal ) {
       newNode-> next = *head;
       *head = newNode;
       return;
   }
    node* curr = *head;
    while (curr->next != nullptr && curr->data != targetVal ) {
        curr = curr->next;
    }
    //找到了插入
    newNode->next = curr->next;
    curr->next = newNode;
}
//删除节点
void deleteList(node** head , int targetVal) {
    if (*head == nullptr) return ;
    if ((*head)->data == targetVal) {
        node* temp = *head;
        *head = (*head)->next;
        return;
    }
    node* curr = *head;
    while (curr->next != nullptr && curr->next->data != targetVal) {
        curr = curr->next;
    }
    if (curr-> next != nullptr) {
        node* temp = curr->next;
        curr->next = temp->next;
    }
}
//查找节点
bool findList(node *head , int targetVal) {
    node * curr = head;
    if (head->data == targetVal) {
        return true;
    }
    while (curr->next != nullptr && curr->data != targetVal) {
        curr = curr->next;
    }
    if (curr->data == targetVal) {
        return true;
    }
    return false;
}
//添加从头位置 二级指针 动态创建节点
void insertFromHead(node** head , int targetVal) {
    node * newNode = new node();
    newNode->data = targetVal;
    newNode->next = *head;
    *head = newNode;
}
//添加从尾部位置
void insertFromTail(node** head , int targetVal) {
    node * newNode = new node();
    newNode->data = targetVal;
    //找到尾部的节点
    node * curr = *head;
    if (*head == nullptr) *head = newNode;
    else while (curr->next != nullptr) {
            curr = curr->next;
    }
    curr->next = newNode;
}
//动态删除节点 delete
void deleteNode(node ** head, int targetVal){
    node * curr = *head;
    if (*head == nullptr) return;
    if (curr->data == targetVal) {
        *head = curr->next;
        delete curr;
    }else {
        while (curr->next != nullptr) {
            if (curr->next->data == targetVal) {
                node * temp = curr->next;
                curr->next = temp->next;
                delete temp;
                return;
            }
            curr = curr->next;
        }
    }
}
int main() {
    node node01 = {11,nullptr};
    node* head = &node01;
    node node02 = {12,nullptr};
    node node03 = {13,nullptr};
    node node04 = {14,nullptr};
    //后插法的实现
    insertListBehind(head,11,&node02);
    // insertListBehind(&head,12,&node02);会无限循环
    insertListBehind(head,12,&node03);
    // node01.next = &node02;
    // node02.next = &node03;
    // cout << node01.data << endl;
    // cout << node01.next->data << endl;
    // cout << node01.next->next->data << endl;//除了-> 还可以*（指针）
    //前插法
     insertFront(&head,11,&node04);
    //删除节点
    deleteList(&head,11);
    //链表的遍历
    printList(&node04);
    //查找节点
    if (findList(head,12))cout<<"true"<<endl;
    else cout<<"false"<<endl;
    node node05 = {15,nullptr};
    insertFromHead(&head,123);
    insertFromHead(&head,125);
    printList(head);
    deleteNode(&head,125);
    printList(head);
}