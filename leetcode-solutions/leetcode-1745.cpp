/**
 * 1745. Palindrome Partitioning IV
 * 
 * Given a string s, return true if it is possible to split the string s into
 * three non-empty palindromic substrings. Otherwise, return false.​​​​​
 * 
 * A string is said to be palindrome if it the same string when reversed.
 * 
 * Example 1:
 * 
 * Input: s = "abcbdd"
 * Output: true
 * Explanation: "abcbdd" = "a" + "bcb" + "dd", and all three substrings are
 * palindromes.
 * 
 * Example 2:
 * 
 * Input: s = "bcbddxy"
 * Output: false
 * Explanation: s cannot be split into 3 palindromes.
 * 
 * Constraints:
 * 
 * 3 <= s.length <= 2000
 * s​​​​​​ consists only of lowercase English letters.
 * 
 */
#include <vector>
#include <string>
using namespace std;

class Solution1 {
public:
    bool checkPartitioning(string s) {
        int n = s.size();
        // dp[i][j] 表示 s[i..j] 是否为回文串
        vector<vector<bool>> dp(n, vector<bool>(n, false));

        // 1. 预处理所有子串的回文状态
        // i 从大到小遍历，j 从小到大遍历
        for (int i = n - 1; i >= 0; --i) {
            for (int j = i; j < n; ++j) {
                if (s[i] == s[j]) {
                    // 如果子串长度小于等于2，或者去掉首尾后是回文
                    if (j - i <= 2) {
                        dp[i][j] = true;
                    } else {
                        dp[i][j] = dp[i + 1][j - 1];
                    }
                }
                // 如果 s[i] != s[j]，则 dp[i][j] 保持 false
            }
        }

        // 2. 枚举分割点
        for (int i = 0; i < n - 2; ++i) { // 第一段结束于 i，需要为后面留两个非空段
            for (int j = i + 1; j < n - 1; ++j) { // 第二段结束于 j
                if (dp[0][i] && dp[i + 1][j] && dp[j + 1][n - 1]) {
                    return true;
                }
            }
        }
        return false;
    }
};

class Solution2 {
public:
    bool checkPartitioning(string s) {
        int n = s.size();
        // isPal[i][j] 表示 s[i..j] 是否为回文串
        vector<vector<bool>> isPal(n, vector<bool>(n, false));

        // 中心扩展法填充 isPal
        // 奇数长度回文中心
        for (int center = 0; center < n; ++center) {
            int l = center, r = center;
            while (l >= 0 && r < n && s[l] == s[r]) {
                isPal[l][r] = true;
                l--;
                r++;
            }
        }
        // 偶数长度回文中心
        for (int center = 0; center < n - 1; ++center) {
            int l = center, r = center + 1;
            while (l >= 0 && r < n && s[l] == s[r]) {
                isPal[l][r] = true;
                l--;
                r++;
            }
        }

        // 枚举分割点
        for (int i = 0; i < n - 2; ++i) {
            for (int j = i + 1; j < n - 1; ++j) {
                if (isPal[0][i] && isPal[i + 1][j] && isPal[j + 1][n - 1]) {
                    return true;
                }
            }
        }
        return false;
    }
};

class Solution {
public:
    bool checkPartitioning(string s) {
        int n = s.size();
        vector<vector<bool>> dp(n, vector<bool>(n, false));

        // 预处理部分与标准DP相同
        for (int i = n - 1; i >= 0; --i) {
            for (int j = i; j < n; ++j) {
                if (s[i] == s[j]) {
                    if (j - i <= 2) {
                        dp[i][j] = true;
                    } else {
                        dp[i][j] = dp[i + 1][j - 1];
                    }
                }
            }
        }

        // 枚举分割点，找到即返回
        for (int i = 0; i < n - 2; ++i) {
            if (!dp[0][i]) continue; // 第一段不是回文，直接跳过
            for (int j = i + 1; j < n - 1; ++j) {
                if (dp[i + 1][j] && dp[j + 1][n - 1]) {
                    return true;
                }
            }
        }
        return false;
    }
};