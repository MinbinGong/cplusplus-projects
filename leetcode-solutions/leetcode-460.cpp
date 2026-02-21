/*
 * LFU Cache
 *
 * Design and implement a data structure for a Least Frequently Used (LFU) cache.
 *
 * Implement the LFUCache class:
 * LFUCache(int capacity) Initializes the object with the capacity of the data structure.
 * int get(int key) Gets the value of the key if the key exists in the cache. Otherwise, returns -1.
 * void put(int key, int value) Update the value of the key if present, or inserts the key if not already present. When
 * the cache reaches its capacity, it should invalidate and remove the least frequently used key before inserting a new
 * item. For this problem, when there is a tie (i.e., two or more keys with the same frequency), the least recently used
 * key would be invalidated. To determine the least frequently used key, a use counter is maintained for each key in the
 * cache. The key with the smallest use counter is the least frequently used key.
 *
 * When a key is first inserted into the cache, its use counter is set to 1 (due to the put operation). The use counter
 * for a key in the cache is incremented either a get or put operation is called on it.
 *
 * The frequency of a key is the number of times the key was accessed (either a get or put operation).
 *
 * Constraints:
 * 1 <= capacity <= 104
 * 0 <= key <= 105
 * 0 <= value <= 109
 * At most 2 * 105 calls will be made to get and put.
 *
 */
#include <list>
#include <unordered_map>
using namespace std;

class LFUCache {
 private:
  struct LFU {
    int key;
    int value;
    int freq;

    LFU(int k, int v, int f) : key(k), value(v), freq(f) {}
  };

  unordered_map<int, list<LFU>::iterator> mp;
  unordered_map<int, list<LFU>> fqMp;

  int size;
  int minFreq;

 public:
  LFUCache(int capacity) : size(capacity), minFreq(0) {}

  int get(int key) {
    if (mp.find(key) == mp.end()) {
      return -1;
    }

    int val = mp[key]->value;
    put(key, val);
    return val;
  }

  void put(int key, int value) {
    if (size <= 0) {
      return;
    }

    if (mp.find(key) != mp.end()) {
      auto it = mp[key];
      int curFreq = it->freq;
      fqMp[curFreq].erase(it);

      fqMp[curFreq + 1].push_back({key, value, curFreq + 1});

      mp[key] = prev(fqMp[curFreq + 1].end());

      if (fqMp[minFreq].empty()) {
        minFreq++;
      }
    } else {
      if (mp.size() >= size) {
        auto it = fqMp[minFreq].begin();
        int key = it->key;

        mp.erase(key);

        fqMp[minFreq].pop_front();
      }

      minFreq = 1;
      fqMp[minFreq].push_back({key, value, minFreq});
      mp[key] = prev(fqMp[minFreq].end());
    }
  }
};