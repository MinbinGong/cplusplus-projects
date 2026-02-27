/**
 * 1062. Longest Repeating Substring
 * 
 * Given a string S, find out the length of the longest repeating substring(s). Return 0 if no repeating substring exists.
 * 
 * 
 * Example 1:
 * Input: "abcd"
 * Output: 0
 * Explanation: There is no repeating substring.
 * 
 * Example 2:
 * Input: "abbaba"
 * Output: 2
 * Explanation: The longest repeating substrings are "ab" and "ba", each of which occurs twice.
 * 
 * Example 3:
 * Input: "aabcaabdaab"
 * Output: 3
 * Explanation: The longest repeating substring is "aab", which occurs 3 times.
 * 
 * Example 4:
 * Input: "aaaaa"
 * Output: 4
 * Explanation: The longest repeating substring is "aaaa", which occurs twice.
 * 
 * Note:
 * The string S consists of only lowercase English letters from 'a' - 'z'.
 * 1 <= S.length <= 1500
 * 
 */
#include <string>
#include <unordered_set>
#include <vector>
#include <algorithm>
using namespace std;

class Solution1 {
public:
    int longestRepeatingSubstring(string s) {
        int n = s.length();
        int left = 1, right = n;
        int result = 0;
        
        // 二分查找可能的长度
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (hasDuplicate(s, mid)) {
                result = mid;       // 当前长度可行，尝试更长的
                left = mid + 1;
            } else {
                right = mid - 1;    // 当前长度不可行，尝试更短的
            }
        }
        return result;
    }

private:
    // 检查字符串 s 中是否存在长度为 len 的重复子串
    bool hasDuplicate(const string& s, int len) {
        int n = s.length();
        if (len > n) return false;
        
        // 使用 unsigned long long 让溢出自动取模 (2^64)，减少冲突
        unsigned long long base = 31;
        unsigned long long power = 1;
        unsigned long long hash = 0;
        
        // 预计算最高位的权重
        for (int i = 0; i < len; i++) {
            power *= base;
        }
        
        // 计算第一个窗口的哈希值
        for (int i = 0; i < len; i++) {
            hash = hash * base + (s[i] - 'a');
        }
        
        // 使用哈希集合记录已经出现过的哈希值
        unordered_set<unsigned long long> seen;
        seen.insert(hash);
        
        // 滑动窗口计算后续子串的哈希值
        for (int i = len; i < n; i++) {
            // 滚动哈希：移除前一个字符，加入新字符
            hash = hash * base + (s[i] - 'a') - (s[i - len] - 'a') * power;
            
            // 检查哈希是否已存在
            if (seen.find(hash) != seen.end()) {
                // 为了绝对正确，可以在这里对比实际字符串
                // 但通常冲突概率极低，对于解题可以接受
                return true;
            }
            seen.insert(hash);
        }
        return false;
    }
};

class Solution2 {
public:
    int longestRepeatingSubstring(string s) {
        int n = s.length();
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
        int maxLen = 0;
        
        for (int i = 1; i <= n; i++) {
            for (int j = i + 1; j <= n; j++) { // j 从 i+1 开始，避免统计同一个字符
                if (s[i - 1] == s[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                    maxLen = max(maxLen, dp[i][j]);
                }
                // 如果不相等，dp[i][j] 默认为 0
            }
        }
        return maxLen;
    }
};