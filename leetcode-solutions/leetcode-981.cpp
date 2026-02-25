/*
 * 981. Time Based Key-Value Store
 * 
 * Design a time-based key-value data structure that can store multiple values for the same key at different time stamps and retrieve the key's value at a certain timestamp.
 * 
 * Implement the TimeMap class:
 * 
 * TimeMap() Initializes the object of the data structure.
 * void set(String key, String value, int timestamp) Stores the key key with the value value at the given time timestamp.
 * String get(String key, int timestamp) Returns a value such that set was called previously, with timestamp_prev <= timestamp. If there are multiple such values, it returns the value associated with the largest timestamp_prev. If there are no values, it returns "".
 * 
 * Example 1:
 * 
 * Input
 * ["TimeMap", "set", "get", "get", "set", "get", "get"]
 * [[], ["foo", "bar", 1], ["foo", 1], ["foo", 3], ["foo", "bar2", 4], ["foo", 4], ["foo", 5]]
 * Output
 * [null, null, "bar", "bar", null, "bar2", "bar2"]
 * Explanation
 * TimeMap timeMap = new TimeMap();
 * timeMap.set("foo", "bar", 1);  // store the key "foo" and value "bar" along with timestamp = 1.
 * timeMap.get("foo", 1);         // return "bar"
 * timeMap.get("foo", 3);         // return "bar", since there is no value corresponding to foo at timestamp 3 and timestamp 2, then the only value is at timestamp 1 is "bar".
 * timeMap.set("foo", "bar2", 4); // store the key "foo" and value "bar2" along with timestamp = 4.
 * timeMap.get("foo", 4);         // return "bar2"
 * timeMap.get("foo", 5);         // return "bar2"
 * 
 * Example 2:
 * 
 * Input
 * ["TimeMap", "set", "get", "get", "set", "get", "get"]
 * [[], ["foo", "bar", 1], ["foo", 1], ["foo", 3], ["foo", "bar2", 4], ["foo", 4], ["foo", 5]]
 * Output
 * [null, null, "bar", "bar", null, "bar2", "bar2"]
 * Explanation
 * TimeMap timeMap = new TimeMap();
 * timeMap.set("foo", "bar", 1);  // store the key "foo" and value "bar" along with timestamp = 1.
 * timeMap.get("foo", 1);         // return "bar"
 * timeMap.get("foo", 3);         // return "bar", since there is no value corresponding to foo at timestamp 3 and timestamp 2, then the only value is at timestamp 1 is "bar".
 * timeMap.set("foo", "bar2", 4); // store the key "foo" and value "bar2" along with timestamp = 4.
 * timeMap.get("foo", 4);         // return "bar2"
 * timeMap.get("foo", 5);         // return "bar2"
 * 
 * Note:
 * 
 * 1 <= key.length, value.length <= 100
 * key and value consist of lowercase English letters and digits.
 * 1 <= timestamp <= 107
 * All the timestamps timestamp of set are strictly increasing.
 * At most 2 * 105 calls will be made to set and get.
 * 
 */
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class TimeMap {
public:
    /** Initialize your data structure here. */
    TimeMap() {}
    
    void set(string key, string value, int timestamp) {
        // Guarantee: timestamp is strictly increasing for the same key.
        data[key].emplace_back(timestamp, value);
    }
    
    string get(string key, int timestamp) {
        auto it = data.find(key);
        if (it == data.end()) return "";          // key not found
        
        const vector<pair<int, string>>& vec = it->second;
        // Binary search: find the first element with timestamp > timestamp
        auto comp = [](const pair<int, string>& p, int ts) {
            return p.first <= ts;   // true for elements <= ts, false for > ts
        };
        // upper_bound with custom comparator gives first element > ts
        auto ub = upper_bound(vec.begin(), vec.end(), timestamp,
                              [](int val, const pair<int, string>& p) {
                                  return val < p.first;
                              });
        if (ub == vec.begin()) return "";   // all timestamps > given
        --ub;                                 // last element with timestamp <= given
        return ub->second;
    }

private:
    unordered_map<string, vector<pair<int, string>>> data;
};