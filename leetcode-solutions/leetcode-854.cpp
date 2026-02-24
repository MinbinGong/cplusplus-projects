/*
 * 854. K-Similar Strings
 * 
 * Strings A and B are K-similar (for some non-negative integer K) if we can swap the positions of two letters in A exactly K times so that the resulting string equals B.
 * 
 * Given two anagrams A and B, return the smallest K for which A and B are K-similar.
 * 
 * Example 1:
 * Input: A = "ab", B = "ba"
 * Output: 1
 * 
 * Example 2:
 * Input: A = "abc", B = "bca"
 * Output: 2
 * 
 * Example 3:
 * Input: A = "abac", B = "baca"
 * Output: 2
 * 
 * Example 4:
 * Input: A = "aabc", B = "abca"
 * Output: 2
 * 
 * Note:
 * 1 <= A.length == B.length <= 20
 * A and B contain only lowercase letters from the set {'a', 'b', 'c', 'd', 'e', 'f'}
 * 
 * 
 */
#include <string>
#include <queue>
#include <unordered_set>
using namespace std;

class Solution {
public:
    int kSimilarity(string A, string B) {
        if (A == B) return 0;
        queue<string> q;
        unordered_set<string> visited;
        q.push(A);
        visited.insert(A);
        int steps = 0;
        
        while (!q.empty()) {
            int size = q.size();
            for (int k = 0; k < size; ++k) {
                string cur = q.front(); q.pop();
                if (cur == B) return steps;
                
                // 找到第一个不同的位置
                int i = 0;
                while (i < cur.size() && cur[i] == B[i]) ++i;
                
                // 尝试交换 i 与后面所有满足条件的 j
                for (int j = i + 1; j < cur.size(); ++j) {
                    if (cur[j] == B[i] && cur[j] != B[j]) {
                        string next = cur;
                        swap(next[i], next[j]);
                        if (!visited.count(next)) {
                            visited.insert(next);
                            q.push(next);
                        }
                    }
                }
            }
            ++steps;
        }
        return -1; // 理论上不会执行到这里
    }
};