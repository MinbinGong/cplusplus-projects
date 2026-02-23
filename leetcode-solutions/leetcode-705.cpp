/*
 * Design HashSet
 *
 * Design a HashSet without using any built-in hash table libraries.
 *
 * To be specific, your design should include these functions:
 * 
 * add(value): Insert a value into the HashSet. 
 * contains(value) : Return whether the value exists in the HashSet or not.
 * remove(value): Remove a value in the HashSet. If the value does not exist in the HashSet, do nothing.
 * 
 * Example:
 * 
 * MyHashSet hashSet = new MyHashSet();
 * hashSet.add(1);         
 * hashSet.add(2);         
 * hashSet.contains(1);    // returns true
 * hashSet.contains(3);    // returns false (not found)
 * hashSet.add(2);          
 * hashSet.contains(2);    // returns true
 * hashSet.remove(2);          
 * hashSet.contains(2);    // returns false (already removed)
 * 
 * Note:
 * 1. All values will be in the range of [0, 1000000].
 * 2. The number of operations will be in the range of [1, 10000].
 * 3. Please do not use the built-in HashSet library.
 * 4. The hash function is not necessary to be a hash function.
 * 
 */
#include <vector>
#include <list>
using namespace std;

class MyHashSet {
private:
    vector<list<int>> buckets; // 每个桶是一个链表，存储哈希值相同的元素
    int hash(int key) {
        return key % buckets.size(); // 简单的取模哈希
    }

public:
    /** 初始化数据结构，选择质数作为桶的数量以减少冲突 */
    MyHashSet() {
        buckets.resize(10007); // 常用质数
    }
    
    /** 添加元素，如果已存在则不做任何事 */
    void add(int key) {
        int idx = hash(key);
        auto& lst = buckets[idx];
        // 检查是否已经存在
        for (int val : lst) {
            if (val == key) return;
        }
        lst.push_back(key);
    }
    
    /** 删除元素，如果不存在则不做任何事 */
    void remove(int key) {
        int idx = hash(key);
        auto& lst = buckets[idx];
        // 遍历找到并删除
        for (auto it = lst.begin(); it != lst.end(); ++it) {
            if (*it == key) {
                lst.erase(it);
                return;
            }
        }
    }
    
    /** 检查元素是否存在 */
    bool contains(int key) {
        int idx = hash(key);
        auto& lst = buckets[idx];
        for (int val : lst) {
            if (val == key) return true;
        }
        return false;
    }
};