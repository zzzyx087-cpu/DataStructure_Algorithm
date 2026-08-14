//
// Created by zhouyxuiang on 2026/3/24.
//
#include <iostream>
using namespace std;
struct TrieNode {
    int pass;
    int end;
    TrieNode *nexts[26];//26个字节点
    TrieNode() {
        pass = 0;
        end = 0;
        memset(nexts,0,sizeof(nexts));
    }
};
class Trie{
private:
    TrieNode *root;
    public:
    Trie() {
        root = new TrieNode();
    }
    //插入字符串
    void insert(string word) {
        if (word.empty()) return;
        TrieNode *cur = root;
        cur->pass++;
        int index = 0;
        for (int i = 0; i <word.length(); i++) {
            //计算字母对应的下标 'a' == 0
            index = word[i] - 'a';
            if (cur->nexts[index] == nullptr) {
                cur->nexts[index] = new TrieNode();
            }
            cur = cur->nexts[index];
            cur->pass++;
        }
        cur->end++;
    }
    // 查询一个单词是否存在
    int search(string word) {
        if (word.empty()) return 0;

        TrieNode* cur = root;
        int index = 0;
        for (int i = 0; i < word.size(); i++) {
            index = word[i] - 'a';
            // 如果某一个字母找不到 → 直接返回 0，单词不存在
            if (cur->nexts[index] == nullptr) {
                return 0;
            }
            cur = cur->nexts[index];
        }
        return cur->end;
    }
    //沿途pass--最后end--
    void deleteWord(string word) {
        if (search(word) == 0) return;
        TrieNode *cur = root;
        cur->pass--;
        int index = 0;
        for (int i = 0; i <word.length(); i++) {
            index = word[i] - 'a';
            //把子节点pass-1
            cur->nexts[index]->pass--;
            if (cur->nexts[index]->pass == 0) {
                delete cur->nexts[index];//释放内存
                cur->nexts[index] = nullptr;//置空
                return;
            }
            cur = cur->nexts[index];
        }
        cur->end--;
    }
};

int main() {
    Trie trie;

    //插入单词
    trie.insert("appe");
    trie.insert("app");
    trie.insert("asda");
    trie.insert("rreee");
    trie.insert("zoo");

    // 测试查询
    cout << "appe 出现次数：" << trie.search("appe") << endl;
    cout << "app  出现次数：" << trie.search("app") << endl;
    cout << "zoo  出现次数：" << trie.search("zoo") << endl;
    cout << "aaa  出现次数：" << trie.search("aaa") << endl; // 没插入，输出 0
}