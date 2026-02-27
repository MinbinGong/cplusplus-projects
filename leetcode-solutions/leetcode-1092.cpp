/*
 * 1092. Shortest Common Supersequence
 *
 * Given two strings str1 and str2, return the shortest string that has both str1 and str2 as subsequences.
 * If multiple answers exist, you may return any of them.
 * (A string S is a subsequence of string T if deleting some number of characters from T (possibly 0, and the characters are chosen anywhere from T) results in the string S.)
 * 
 * Example 1:
 * Input: str1 = "abac", str2 = "cab"
 * Output: "cabac"
 * Explanation: 
 * str1 = "abac" is a subsequence of "cabac" because we can delete the first "c".
 * str2 = "cab" is a subsequence of "cabac" because we can delete the last "ac".
 * The answer provided is the shortest such string that satisfies these properties.
 * 
 * Note:
 * 1 <= str1.length, str2.length <= 1000
 * str1 and str2 consist of lowercase English
 * letters.
 * 
 */
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    string shortestCommonSupersequence(string str1, string str2) {
        int m = str1.size(), n = str2.size();
        // dp[i][j] 表示 str1[0..i-1] 和 str2[0..j-1] 的 LCS 长度
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (str1[i - 1] == str2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }

        // 回溯构造最短公共超序列
        string res;
        int i = m, j = n;
        while (i > 0 && j > 0) {
            if (str1[i - 1] == str2[j - 1]) {
                // 公共字符，只添加一次
                res.push_back(str1[i - 1]);
                --i;
                --j;
            } else if (dp[i - 1][j] > dp[i][j - 1]) {
                // 来自上方，说明 str1 的当前字符不在 LCS 中，添加它
                res.push_back(str1[i - 1]);
                --i;
            } else {
                // 来自左方，添加 str2 的当前字符
                res.push_back(str2[j - 1]);
                --j;
            }
        }
        // 添加剩余字符
        while (i > 0) {
            res.push_back(str1[i - 1]);
            --i;
        }
        while (j > 0) {
            res.push_back(str2[j - 1]);
            --j;
        }
        // 因为我们是从后往前构建的，需要反转
        reverse(res.begin(), res.end());
        return res;
    }
};