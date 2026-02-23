/*
 * Design HashMap
 *
 * Design a HashMap without using any built-in hash table libraries.
 *
 * To be specific, your design should include these functions:
 * 
 * put(key, value) : Insert a (key, value) pair into the HashMap. If the value already exists in the HashMap, update the value.
 * get(key): Returns the value to which the specified key is mapped, or -1 if this map contains no mapping for the key.
 * remove(key) : Remove the mapping for the value key if this map contains the mapping for the key.
 * 
 * Example:
 * 
 * MyHashMap hashMap = new MyHashMap();
 * hashMap.put(1, 1);
 * hashMap.put(2, 2);
 * hashMap.get(1);            // returns 1
 * hashMap.get(3);            // returns -1 (not found)
 * hashMap.put(2, 1);          // update the existing value
 * hashMap.get(2);            // returns 1 
 * hashMap.remove(2);          // remove the mapping for 2
 * hashMap.get(2);            // returns -1 (not found) 
 * 
 * Note:
 * 1. All keys and values will be in the range of [0, 1000000].
 * 2. The number of operations will be in the range of [1, 10000].
 * 3. Please do not use the built-in HashMap library.
 * 4. The hash function is not necessary to be a hash function.
 *  
 */
#include <vector>
#include <list>
#include <utility>
using namespace std;

class MyHashMap {
private:
    vector<list<pair<int, int>>> buckets;
    int hash(int key) {
        return key % buckets.size(); // 简单的取模哈希
    }

public:
    MyHashMap() {
        buckets.resize(10007); // 使用质数作为桶的数量，减少冲突
    }
    
    void put(int key, int value) {
        int idx = hash(key);
        auto& lst = buckets[idx];
        // 查找是否已存在，存在则更新
        for (auto& p : lst) {
            if (p.first == key) {
                p.second = value;
                return;
            }
        }
        // 不存在则添加
        lst.push_back({key, value});
    }
    
    int get(int key) {
        int idx = hash(key);
        auto& lst = buckets[idx];
        for (auto& p : lst) {
            if (p.first == key) return p.second;
        }
        return -1;
    }
    
    void remove(int key) {
        int idx = hash(key);
        auto& lst = buckets[idx];
        for (auto it = lst.begin(); it != lst.end(); ++it) {
            if (it->first == key) {
                lst.erase(it);
                return;
            }
        }
    }
};