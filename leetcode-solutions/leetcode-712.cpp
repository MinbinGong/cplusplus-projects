/*
 * Minimum ASCII Delete Sum for Two Strings
 *
 * Given two strings s1, s2, find the lowest ASCII sum of deleted characters to make two strings equal.
 * 
 * Input: s1 = "sea", s2 = "eat"
 * Output: 231
 * Explanation: Deleting "s" from "sea" adds the ASCII value of "s" (115) to the sum.
 * Deleting "t" from "eat" adds 116 to the sum.
 * At the end, both strings are equal, and 115 + 116 = 231 is the minimum sum possible to achieve this.
 * 
 * Input: s1 = "delete", s2 = "leet"
 * Output: 403
 * Explanation: Deleting "dee" from "delete" to turn the string into "let",
 * adds 100[d]+101[e]+101[e] to the sum.  Deleting "e" from "leet" adds 101[e] to the sum.
 * At the end, both strings are equal to "let", and the answer is 100+101+101+101 = 403.
 * If instead we turned both strings into "lee" or "eet", we would get answers of 433 or 417, which are higher.
 * 
 * Note:
 * 1. 0 < s1.length, s2.length <= 1000.
 * 2. All elements of each string will have an ASCII value in [97, 122].
 * 3. The sum of the ASCII values of every character in s1 and s2 will be in the range [0, 10^6].
 * 4. The strings s1 and s2 are non-empty.
 * 
 */
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    int minimumDeleteSum(string s1, string s2) {
        int m = s1.size(), n = s2.size();
        // dp[i][j] 表示使 s1[0..i-1] 和 s2[0..j-1] 相等的最小删除 ASCII 和
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

        // 初始化第一列：s2 为空，需要删除 s1 的所有字符
        for (int i = 1; i <= m; ++i) {
            dp[i][0] = dp[i - 1][0] + s1[i - 1];
        }
        // 初始化第一行：s1 为空，需要删除 s2 的所有字符
        for (int j = 1; j <= n; ++j) {
            dp[0][j] = dp[0][j - 1] + s2[j - 1];
        }

        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (s1[i - 1] == s2[j - 1]) {
                    // 字符相等，无需删除
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    // 删除 s1[i-1] 或删除 s2[j-1]，取较小代价
                    dp[i][j] = min(dp[i - 1][j] + s1[i - 1],
                                   dp[i][j - 1] + s2[j - 1]);
                }
            }
        }
        return dp[m][n];
    }
};