//
// Created by zhouyxuiang on 2026/3/14.
//
#include <iostream>
#include <queue>
using namespace std;
//堆结构 逻辑上 是完全二叉树
//某个数现在处在index的位置 往上继续移动
//当某一个数 没有父亲大 或者到头位置 就停止
void SiftUp(vector<int> &v, int index) {
    while (v[index] > v[(index - 1) / 2]) {
        swap(v[index], v[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}
//某个数载index位置 能否向下移动
void heapfy(vector<int> &v , int index , int heapsize) {//维护大根堆的性质
    int left = index * 2 + 1;//左孩子的下标
    while (left < heapsize) {//下方有孩子
        //比较哪个孩子大
        int largest = left + 1 < heapsize && v[left + 1] > v[left] ? left + 1 : left;
        largest = v[largest] > v[index] ? largest : index;
        if (largest == index) break;
        swap(v[index], v[largest]);
        index = largest;
        left = index * 2 + 1;
    }
}
void heapSort(vector<int>& arr) {
    int n = arr.size();

    // 1. 建堆（从最后一个非叶子节点开始）
    for (int i = n / 2 - 1; i >= 0; --i) {
        heapfy(arr, i, n);
    }

    // 2. 排序核心：不断把堆顶放到最后
    int heapSize = n;
    while (heapSize > 1) {
        // 堆顶和最后一个元素交换
        swap(arr[0], arr[heapSize - 1]);
        // 堆大小 -1
        heapSize--;
        // 新堆顶下沉调整
        heapfy(arr, 0, heapSize);
    }
}
void test01() {
    //调用heapfy
    vector<int> arr = {3, 1, 5, 2, 4};
    int n = arr.size();
    for (int i = n/2 - 1 ; i >= 0; i--) {
        heapfy(arr, i, n);
    }
    cout << arr[0] << endl;//最大值
    for_each(arr.begin(), arr.end(), [](int val){cout << val << " ";});
}
int main() {
    // 1. 大根堆（默认）
    // 堆顶永远是 最大值
    priority_queue<int> max_heap;
    max_heap.push(3);
    max_heap.push(1);
    max_heap.push(5);
    max_heap.push(2);
    cout << max_heap.top();
    cout << endl;
    //push(x) 插入元素
    //top() 看堆顶（最大 / 最小）
    //pop() 删除堆顶

    //遍历大根堆
    cout << "大根堆输出从大到小" << endl;
    while (!max_heap.empty()) {
        cout << max_heap.top() <<" ";
        max_heap.pop();
    }
    cout << endl;
    // 2. 小根堆
    // 堆顶永远是 最小值
    priority_queue<int, vector<int>, greater<int>> min_heap;
    min_heap.push(3);
    min_heap.push(1);
    min_heap.push(5);
    min_heap.push(2);
    cout << min_heap.top() << endl;
    //遍历小根堆
    cout << "小根堆输出从小到大" << endl;
    while (!min_heap.empty()) {
        cout << min_heap.top() << " ";
        min_heap.pop();
    }
    test01();
    vector<int> arr = {3,1,5,2,4};
    heapSort(arr);
    cout << endl;
    for_each(arr.begin(), arr.end(), [](int val){cout << val << " ";});
    return 0;
}