// LRUCache.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <list>
#include <unordered_map>

class LRUCache {
   private:
    struct CacheNode {
        int key = INT_MIN;
        int value = INT_MIN;
        CacheNode(int k = INT_MIN, int v = INT_MIN) : key(k), value(v) {}
    };

   public:
    LRUCache(int c) : capacity(c) {}

    int get(int key) {
        if (cacheMap.find(key) == cacheMap.end()) {
            return -1;
        }

        cacheList.splice(cacheList.begin(), cacheList, cacheMap[key]);
        cacheMap[key] = cacheList.begin();
        return cacheMap[key]->value;
    }

    void put(int key, int value) {
        if (cacheMap.find(key) == cacheMap.end()) {
            if (cacheList.size() == capacity) {
                cacheMap.erase(cacheList.back().key);
                cacheList.pop_back();
            }

            cacheList.push_front(CacheNode(key, value));
            cacheMap[key] = cacheList.begin();
        } else {
            cacheMap[key]->value = value;
            cacheList.splice(cacheList.begin(), cacheList, cacheMap[key]);
            cacheMap[key] = cacheList.begin();
        }
    }

   private:
    std::list<CacheNode> cacheList;
    std::unordered_map<int, std::list<CacheNode>::iterator> cacheMap;
    int capacity;
};

int main() { std::cout << "Hello World!\n"; }

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files
//   to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
