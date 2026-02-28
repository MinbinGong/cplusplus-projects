/**
 * 1206. Design Skiplist
 * 
 * Design a Skiplist without using any built-in libraries.
 * 
 * A skiplist is a data structure that takes O(log(n)) time to add, erase and search. Comparing with treap and red-black tree which has the same function and performance, the code length of Skiplist can be comparatively short and the idea behind Skiplists are just simple linked lists.
 * 
 * For example: we have a Skiplist containing [30,40,50,60,70,90] and we want to add 80 and 45 into it. The Skiplist works this way:
 * 
 * Artyom Kalinin [CC BY-SA 3.0], via Wikimedia Commons
 * 
 * You can see there are many layers in the Skiplist. Each layer is a sorted linked list. With the help of the top layers, add, erase and search can be faster than O(n). It can be proven that the average time complexity for each operation is O(log(n)) and space complexity is O(n).
 * 
 * Note:
 * 0 <= num, target <= 20000
 * At most 50000 calls will be made to search, add, and erase.
 * 
 */
#include <vector>
#include <random>
using namespace std;

class Skiplist {
private:
    static const int MAX_LEVEL = 16;  // 最大层数
    struct Node {
        int val;
        vector<Node*> next;
        Node(int _val) : val(_val) {
            next.resize(MAX_LEVEL, nullptr);
        }
    };
    
    Node* head;
    int level;  // 当前最大层数
    mt19937 gen;
    uniform_real_distribution<double> dis;
    
    // 随机生成节点层数
    int randomLevel() {
        int lv = 1;
        // 以 0.5 的概率增加层数
        while (dis(gen) < 0.5 && lv < MAX_LEVEL) {
            lv++;
        }
        return lv;
    }
    
    // 核心查找函数：找到每一层中小于 target 的最后一个节点
    void find(int target, vector<Node*>& update) {
        Node* cur = head;
        for (int i = level - 1; i >= 0; i--) {
            while (cur->next[i] && cur->next[i]->val < target) {
                cur = cur->next[i];
            }
            update[i] = cur;
        }
    }
    
public:
    Skiplist() : gen(random_device{}()), dis(0, 1) {
        head = new Node(-1);  // 哨兵节点
        level = 1;
    }
    
    ~Skiplist() {
        // 释放所有节点
        Node* cur = head->next[0];
        while (cur) {
            Node* next = cur->next[0];
            delete cur;
            cur = next;
        }
        delete head;
    }
    
    bool search(int target) {
        vector<Node*> update(level);
        find(target, update);
        Node* cur = update[0]->next[0];
        return cur && cur->val == target;
    }
    
    void add(int num) {
        vector<Node*> update(MAX_LEVEL, head);
        find(num, update);
        
        int newLevel = randomLevel();
        if (newLevel > level) {
            // 更新最高层数
            level = newLevel;
        }
        
        Node* newNode = new Node(num);
        for (int i = 0; i < newLevel; i++) {
            newNode->next[i] = update[i]->next[i];
            update[i]->next[i] = newNode;
        }
    }
    
    bool erase(int num) {
        vector<Node*> update(level);
        find(num, update);
        
        Node* target = update[0]->next[0];
        if (!target || target->val != num) {
            return false;
        }
        
        // 从底层向上删除
        for (int i = 0; i < level && update[i]->next[i] == target; i++) {
            update[i]->next[i] = target->next[i];
        }
        
        // 更新最高层数
        while (level > 1 && !head->next[level - 1]) {
            level--;
        }
        
        delete target;
        return true;
    }
};
