/*
 * Map Sum Pairs
 *
 * Implement a MapSum class with insert, and sum methods.
 *
 * For the method insert, you'll be given a pair of (string, integer). The string represents the key and the integer represents the value. If the key already existed, then the original key-value pair will be overridden to the new one.
 *
 * For the method sum, you'll be given a string representing the prefix, and you need to return the sum of all the pairs' value whose key starts with the prefix.
 *
 * Example 1:
 *
 * Input: insert("apple", 3), Output: Null
 * Input: sum("ap"), Output: 3
 * Input: insert("app", 2), Output: Null
 * Input: sum("ap"), Output: 5
 * 
 * Note:
 *
 * You may assume that all the inputs are consist of lowercase letters a-z.
 * For contest purpose, the test data is rather small by now. You could think about highly efficient algorithm after the contest.
 * Please remember to RESET your class variables declared in class MapSum, as static/class variables are persisted across multiple test cases. Please see here for more details.
 * 
 */
#include <unordered_map>
using namespace std;

class MapSum {
private:
    // Trie 节点定义
    struct TrieNode {
        TrieNode* children[26];
        int sum;            // 经过该节点的所有键的值的总和
        TrieNode() {
            for (int i = 0; i < 26; ++i) children[i] = nullptr;
            sum = 0;
        }
    };
    
    TrieNode* root;
    unordered_map<string, int> kv;   // 记录每个 key 的当前值，用于处理更新

public:
    MapSum() {
        root = new TrieNode();
    }
    
    // 插入键值对，若 key 已存在则更新值
    void insert(string key, int val) {
        int delta = val;
        if (kv.count(key)) {
            delta -= kv[key];   // 计算新旧值的差值
        }
        kv[key] = val;
        
        TrieNode* node = root;
        for (char c : key) {
            int idx = c - 'a';
            if (!node->children[idx]) {
                node->children[idx] = new TrieNode();
            }
            node = node->children[idx];
            node->sum += delta;   // 更新路径上的前缀和
        }
    }
    
    // 返回所有以 prefix 为前缀的 key 的值的总和
    int sum(string prefix) {
        TrieNode* node = root;
        for (char c : prefix) {
            int idx = c - 'a';
            if (!node->children[idx]) return 0;  // 前缀不存在
            node = node->children[idx];
        }
        return node->sum;
    }
};