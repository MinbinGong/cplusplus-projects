/*
LRU Cache

题目描述
设计一个固定大小的，最少最近使用缓存 (least recently used cache, LRU)。每次将信息插入未
满的缓存的时候，以及更新或查找一个缓存内存在的信息的时候，将该信息标为最近使用。在缓
存满的情况下将一个新信息插入的时候，需要移除最旧的信息，插入新信息，并将该信息标为最
近使用。

题解
我们采用一个链表 list<pair<int, int>> 来储存信息的 key 和 value，链表的链接顺序即为最
近使用的新旧顺序，最新的信息在链表头节点。同时我们需要一个嵌套着链表的迭代器的 un-
ordered_map<int, list<pair<int, int»::iterator> 进行快速搜索，存迭代器的原因是方便调用链表的
splice 函数来直接更新查找成功（cash hit）时的信息，即把迭代器对应的节点移动为链表的头节
点。
 */
#include <list>
#include <unordered_map>
#include <utility>
using namespace std;

class LRUCache {
  unordered_map<int, list<pair<int, int>>::iterator> hashMap;
  list<pair<int, int>> cache;
  int size;

 public:
  LRUCache(int capacity) : size(capacity) {}

  int get(int key) {
    auto it = hashMap.find(key);
    if (it == hashMap.end()) {
      return -1;
    }
    cache.splice(cache.begin(), cache, it->second);
    return it->second->second;
  }

  void put(int key, int value) {
    auto it = hashMap.find(key);
    if (it != hashMap.end()) {
      it->second->second = value;
      return cache.splice(cache.begin(), cache, it->second);
    }

    cache.insert(cache.begin(), make_pair(key, value));
    hashMap[key] = cache.begin();
    if (cache.size > size) {
      hashMap.erase(cache.back().first);
      cache.pop_back();
    }
  }
};