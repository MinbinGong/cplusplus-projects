/*
 * All O(1) Data Structure
 *
 * Design a data structure to store the strings' count with the ability to return the strings with minimum and maximum counts.
 * 
 * Implement the AllOne class:
 * 
 * AllOne() Initializes the object of the data structure.
 * inc(String key) Increments the count of the string key by 1. If key does not exist in the data structure, insert it with count 1.
 * dec(String key) Decrements the count of the string key by 1. If the count of key is 0 after the decrement, remove it from the data structure. It is guaranteed that key exists in the data structure before the decrement.
 * getMaxKey() Returns one of the keys with the maximal count. If no element exists, return an empty string "".
 * getMinKey() Returns one of the keys with the minimum count. If no element exists, return an empty string "".
 * 
 * Note that each function must run in O(1) average time complexity.
 * 
 * Constraints:
 * 1 <= key.length <= 10
 * key consists of lowercase English letters.
 * It is guaranteed that for each call to dec, key is existing in the data structure.
 * At most 5 * 10^4 calls will be made to inc, dec, getMaxKey, and getMinKey.
 */
#include <string>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class AllOne {
  class Node {
   public:
    int value;
    unordered_set<string> keys;
  };
  using lit = list<Node>::iterator;
  unordered_map<string, lit> keymap;
  list<Node> counts;

 public:
  /** Initialize your data structure here. */
  AllOne() {
    keymap.clear();
    counts.clear();
  }

  /** Inserts a new key <Key> with value 1. Or increments an existing key by 1. */
  void inc(string key) {
    auto pos = counts.end();
    auto newpos = pos;
    int newcnt = 1;
    if (keymap.find(key) != keymap.end()) {
      // get pos
      pos = keymap[key];
      newpos = pos;
      newpos--;

      // update keymap
      newcnt = pos->value + 1;

      if (pos == counts.begin() || newpos->value != newcnt) {
        newpos = counts.insert(pos, {newcnt, {key}});
      } else {
        newpos->keys.insert(key);
      }

      // update counts
      pos->keys.erase(key);
      if (!pos->keys.size()) counts.erase(pos);
    } else {
      newpos = pos;
      newpos--;
      if (pos == counts.begin() || newpos->value != newcnt) {
        newpos = counts.insert(pos, {newcnt, {key}});
      } else {
        newpos->keys.insert(key);
      }
    }
    keymap[key] = newpos;
    return;
  }

  /** Decrements an existing key by 1. If Key's value is 1, remove it from the data structure. */
  void dec(string key) {
    auto pos = counts.end();
    auto newpos = pos;
    int newcnt = 1;
    if (keymap.find(key) != keymap.end()) {
      // get pos
      pos = keymap[key];
      newpos = pos;
      newpos++;

      // update keymap
      newcnt = pos->value - 1;

      if (newcnt) {
        if (newpos == counts.end() || newpos->value != newcnt) {
          newpos = counts.insert(newpos, {newcnt, {key}});
        } else {
          newpos->keys.insert(key);
        }
        keymap[key] = newpos;
      } else {
        // remove this key
        keymap.erase(key);
      }

      // update counts
      pos->keys.erase(key);
      if (!pos->keys.size()) counts.erase(pos);
    }

    return;
  }

  /** Returns one of the keys with maximal value. */
  string getMaxKey() { return counts.size() ? *counts.front().keys.begin() : ""; }

  /** Returns one of the keys with Minimal value. */
  string getMinKey() { return counts.size() ? *counts.back().keys.begin() : ""; }
};