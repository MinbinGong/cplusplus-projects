/*
 * 1044. Longest Duplicate Substring
 *
 * Given a string S, consider all duplicated substrings: (contiguous) substrings of S that occur 2 or more times.  (The occurrences may overlap.)
 * 
 * Return any duplicated substring that has the longest possible length.  (If S does not have a duplicated substring, the answer is "".)
 * 
 * Example 1:
 * Input: "banana"
 * Output: "ana"
 * 
 * Example 2:
 * Input: "abcd"
 * Output: ""
 * 
 * Note:
 * 1. 2 <= S.length <= 10^5
 * 2. S consists of lowercase English letters.
 * 
 */
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    string longestDupSubstring(string s) {
        int n = s.size();
        
        // 准备两个模数减少哈希冲突
        const long long mod1 = 1e9 + 7;
        const long long mod2 = 1e9 + 9;
        const long long base = 26;
        
        vector<long long> power1(n, 1), power2(n, 1);
        for (int i = 1; i < n; i++) {
            power1[i] = (power1[i-1] * base) % mod1;
            power2[i] = (power2[i-1] * base) % mod2;
        }
        
        // 二分查找
        int left = 1, right = n;
        string result = "";
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            int pos = findDuplicate(s, mid, power1, power2, mod1, mod2);
            
            if (pos != -1) {
                result = s.substr(pos, mid);
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return result;
    }
    
private:
    int findDuplicate(const string& s, int len, 
                     const vector<long long>& power1, 
                     const vector<long long>& power2,
                     long long mod1, long long mod2) {
        if (len == 0) return -1;
        
        unordered_map<long long, vector<int>> seen;
        
        long long hash1 = 0, hash2 = 0;
        for (int i = 0; i < len; i++) {
            hash1 = (hash1 * 26 + (s[i] - 'a')) % mod1;
            hash2 = (hash2 * 26 + (s[i] - 'a')) % mod2;
        }
        
        long long hash = (hash1 << 32) | hash2;
        seen[hash].push_back(0);
        
        for (int i = len; i < s.size(); i++) {
            hash1 = ((hash1 - (s[i-len] - 'a') * power1[len-1]) % mod1 + mod1) % mod1;
            hash2 = ((hash2 - (s[i-len] - 'a') * power2[len-1]) % mod2 + mod2) % mod2;
            
            hash1 = (hash1 * 26 + (s[i] - 'a')) % mod1;
            hash2 = (hash2 * 26 + (s[i] - 'a')) % mod2;
            
            hash = (hash1 << 32) | hash2;
            int start = i - len + 1;
            
            if (seen.find(hash) != seen.end()) {
                string current = s.substr(start, len);
                for (int prevStart : seen[hash]) {
                    if (s.substr(prevStart, len) == current) {
                        return prevStart;
                    }
                }
            }
            
            seen[hash].push_back(start);
        }
        
        return -1;
    }
};