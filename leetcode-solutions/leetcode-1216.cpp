/**
 * 1216. Valid Palindrome III
 *
 * Given a string s and an integer k, find out if the given string is a K-Palindrome or not.
 *
 * A string is K-Palindrome if it can be transformed into a palindrome by removing at most k characters from it.
 *
 *
 *
 * Example 1:
 *
 * Input: s = "abcdeca", k = 2
 * Output: true
 * Explanation: Remove 'b' and 'e' characters.
 *
 *
 * Constraints:
 *
 * 1 <= s.length <= 1000
 * s has only lowercase English letters.
 * 1 <= k <= s.length
 *
 */
#include <string>
#include <vector>

class Solution1 {
public:
    bool isValidPalindrome(std::string s, int k) {
        int n = s.length();
        // dp[i][j] 表示子串 s[i..j] 成为回文串最少需要删除的字符数
        std::vector<std::vector<int>> dp(n, std::vector<int>(n, 0));
        
        // 从长度为2的子串开始计算
        for (int l = 2; l <= n; ++l) {
            for (int i = 0; i <= n - l; ++i) {
                int j = i + l - 1;
                if (s[i] == s[j]) {
                    // 如果两端字符相等，则删除次数与去掉两端后的子串相同
                    dp[i][j] = dp[i + 1][j - 1];
                } else {
                    // 如果两端字符不等，则删除一端字符，取较小值加1
                    dp[i][j] = 1 + std::min(dp[i + 1][j], dp[i][j - 1]);
                }
            }
        }
        
        // 检查整个字符串删除dp[0][n-1]个字符是否能成为回文串
        return dp[0][n - 1] <= k;
    }
};

// 优化版：使用滚动数组优化空间复杂度
class Solution2 {
public:
    bool isValidPalindrome(std::string s, int k) {
        int n = s.length();
        std::vector<int> dp(n, 0);
        std::vector<int> prev(n, 0);
        
        for (int i = n-1; i >= 0; --i) {
            dp[i] = 0;
            for (int j = i+1; j < n; ++j) {
                if (s[i] == s[j]) {
                    dp[j] = prev[j-1];
                } else {
                    dp[j] = 1 + std::min(prev[j], dp[j-1]);
                }
            }
            prev = dp;
        }
        
        return dp[n-1] <= k;
    }
};
