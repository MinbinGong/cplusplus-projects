/**
 * 1682. Longest Palindromic Subsequence II
 * 
 * A subsequence of a string s is considered a good palindromic subsequence if:
 * 
 * It is a subsequence of s.
 * It is a palindrome (has the same value if reversed).
 * It has an even length.
 * No two consecutive characters are equal, except the two middle ones.
 * For example, if s = "abcabcabb", then "abba" is considered a good palindromic subsequence, while "bcb" (not even length) and "bb" (has equal consecutive characters) are not.
 * 
 * Given a string s, return the length of the longest good palindromic subsequence in s.
 * 
 * Example 1:
 * Input: s = "bbabab"
 * Output: 4
 * Explanation: The longest good palindromic subsequence of s is "baab".
 * 
 * Example 2:
 * Input: s = "dcbccacdb"
 * Output: 4
 * Explanation: The longest good palindromic subsequence of s is "dccd".
 * 
 * Constraints:
 * 1 <= s.length <= 250
 * s consists of lowercase English letters.
 * 
 */
#include <vector>
#include <string>
#include <cstdint>
#include <algorithm>
using namespace std;

class Solution {
public:
    int longestPalindromeSubseq(string s) {
        int n = s.size();
        if (n == 0) return 0;
        
        // data for an interval [l, r] (l <= r)
        struct Interval {
            uint16_t best[26];          // longest palindrome starting and ending with each character
            uint16_t max1_val;           // largest value among best[]
            uint8_t  max1_char;          // character that gives max1_val
            uint16_t max2_val;           // second largest value
            uint8_t  max2_char;          // character that gives max2_val
        };
        
        // dp[l][offset] where offset = r - l
        vector<vector<Interval>> dp(n);
        for (int i = 0; i < n; ++i) {
            dp[i].resize(n - i);
        }
        
        // length 1 intervals
        for (int i = 0; i < n; ++i) {
            Interval& inter = dp[i][0];
            int ch = s[i] - 'a';
            for (int c = 0; c < 26; ++c) {
                inter.best[c] = (c == ch) ? 1 : 0;
            }
            uint16_t max1 = 0, max2 = 0;
            uint8_t max1c = 0, max2c = 0;
            for (int c = 0; c < 26; ++c) {
                uint16_t v = inter.best[c];
                if (v > max1) {
                    max2 = max1; max2c = max1c;
                    max1 = v; max1c = c;
                } else if (v > max2) {
                    max2 = v; max2c = c;
                }
            }
            inter.max1_val = max1;
            inter.max1_char = max1c;
            inter.max2_val = max2;
            inter.max2_char = max2c;
        }
        
        // longer intervals
        for (int len = 2; len <= n; ++len) {
            for (int l = 0; l + len <= n; ++l) {
                int r = l + len - 1;
                Interval& inter = dp[l][len - 1];
                Interval& left = dp[l + 1][len - 2];   // [l+1, r]
                Interval& right = dp[l][len - 2];      // [l, r-1]
                
                for (int c = 0; c < 26; ++c) {
                    uint16_t val = max(left.best[c], right.best[c]);
                    
                    // can we use s[l] and s[r] as the two ends?
                    if (s[l] - 'a' == c && s[r] - 'a' == c) {
                        if (len >= 3) {
                            Interval& inner = dp[l + 1][len - 3]; // [l+1, r-1]
                            uint16_t innerBest;
                            if (inner.max1_char != c) {
                                innerBest = inner.max1_val;
                            } else {
                                innerBest = inner.max2_val;
                            }
                            if (innerBest > 0) {   // need a non‑empty inner part to separate the two c's
                                val = max(val, (uint16_t)(2 + innerBest));
                            }
                        }
                        // for len == 2, using both ends would give two equal adjacent characters -> invalid
                    }
                    inter.best[c] = val;
                }
                
                // update max1 / max2 for this interval
                uint16_t max1 = 0, max2 = 0;
                uint8_t max1c = 0, max2c = 0;
                for (int c = 0; c < 26; ++c) {
                    uint16_t v = inter.best[c];
                    if (v > max1) {
                        max2 = max1; max2c = max1c;
                        max1 = v; max1c = c;
                    } else if (v > max2) {
                        max2 = v; max2c = c;
                    }
                }
                inter.max1_val = max1;
                inter.max1_char = max1c;
                inter.max2_val = max2;
                inter.max2_char = max2c;
            }
        }
        
        Interval& full = dp[0][n - 1];
        int ans = 0;
        for (int c = 0; c < 26; ++c) {
            if (full.best[c] > ans) ans = full.best[c];
        }
        return ans;
    }
};
