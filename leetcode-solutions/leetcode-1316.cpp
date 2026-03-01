/**
 * 1316. Distinct Echo Substrings
 * 
 * Return the number of distinct non-empty substrings of text that can be written as the concatenation of some string with itself (i.e. it can be written as a + a where a is some string).
 * 
 * Example 1:
 * Input: text = "abcabcabc"
 * Output: 3
 * Explanation: The 3 substrings are "abcabc", "bcabca" and "cabcab".
 * 
 * Example 2:
 * Input: text = "leetcodeleetcode"
 * Output: 2
 * Explanation: The 2 substrings are "ee" and "leetcodeleetcode".
 * 
 * Note:
 * 1 <= text.length <= 2000
 * text has only lowercase English letters.
 * 
 */
#include <vector>
#include <string>
#include <unordered_set>
using namespace std;

class Solution {
public:
    int distinctEchoSubstrings(string text) {
        int n = text.size();
        // 使用 unsigned long long 让溢出自动取模，降低哈希冲突概率
        using ULL = unsigned long long;
        const int BASE = 131;
        
        // 预处理哈希值和 BASE 的幂
        vector<ULL> h(n + 1, 0);      // h[i] 表示 text[0..i-1] 的哈希值
        vector<ULL> power(n + 1, 1);  // power[i] = BASE^i
        
        for (int i = 1; i <= n; ++i) {
            h[i] = h[i - 1] * BASE + (text[i - 1] - 'a' + 1); // 字符映射到 1-26
            power[i] = power[i - 1] * BASE;
        }
        
        // 辅助函数：获取子串 text[l-1..r-1] 的哈希值（1-indexed）
        auto getHash = [&](int l, int r) -> ULL {
            return h[r] - h[l - 1] * power[r - l + 1];
        };
        
        unordered_set<ULL> seen; // 存储已发现的回文子串哈希值，用于去重
        
        // 枚举所有可能的偶数长度子串
        for (int len = 2; len <= n; len += 2) {
            int half = len / 2;
            for (int i = 1; i + len - 1 <= n; ++i) {
                // 前半段 [i, i+half-1] 和后半段 [i+half, i+len-1]
                ULL leftHash = getHash(i, i + half - 1);
                ULL rightHash = getHash(i + half, i + len - 1);
                
                if (leftHash == rightHash) {
                    seen.insert(leftHash); // 只存哈希值即可，题目要求返回数量
                }
            }
        }
        
        return seen.size();
    }
};