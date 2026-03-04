/**
 * 1531. String Compression II
 * 
 * Run-length encoding is a string compression method that works by replacing consecutive identical characters (repeated 2 or more times) with the concatenation of the character and the number marking the count of the characters (length of the run). For example, to compress the string "aabccc" we replace "aa" by "a2" and replace "ccc" by "c3". Thus the compressed string becomes "a2bc3".
 * 
 * Notice that in this problem, we are not adding '1' after single characters.
 * 
 * Given a string s and an integer k. You need to delete at most k characters from s such that the run-length encoded version of s has minimum length.
 * 
 * Find the minimum length of the run-length encoded version of s after deleting at most k characters.
 * 
 * 
 * Example 1:
 * Input: s = "aaabcccd", k = 2
 * Output: 4
 * Explanation: Delete 2 'b' and 1 'd', then the compressed string becomes "a2c3".
 * 
 * Example 2:
 * Input: s = "aabbaa", k = 2
 * Output: 2
 * Explanation: Delete 2 'b' characters, then the compressed string becomes "a4".
 * 
 * Example 3:
 * Input: s = "aaaaaaaaaaa", k = 0
 * Output: 3
 * Explanation: Since k is zero, we cannot delete anything. The compressed string is "a11".
 * 
 * 
 * Constraints:
 * 1 <= s.length <= 100
 * 0 <= k <= s.length
 * s contains only lowercase English letters.
 * 
 */
#include <vector>
#include <string>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    int getLength(int cnt) {
        if (cnt == 1) return 1;
        if (cnt < 10) return 2;
        if (cnt < 100) return 3;
        return 4; // cnt == 100
    }

    int getLengthOfOptimalCompression(string s, int k) {
        int n = s.size();
        const int INF = 1e9;
        vector<vector<int>> dp(n + 1, vector<int>(k + 1, INF));
        // empty suffix: zero length only if no deletions left
        dp[n][0] = 0;
        // dp[n][j] for j>0 remains INF

        for (int i = n - 1; i >= 0; --i) {
            // initialize with deletion option
            for (int j = 0; j <= k; ++j) {
                if (j > 0) {
                    dp[i][j] = min(dp[i][j], dp[i + 1][j - 1]);
                }
            }

            // try all runs starting at i
            int cnt = 0;
            for (int r = i; r < n; ++r) {
                if (s[r] == s[i]) ++cnt;
                int del = (r - i + 1) - cnt;       // chars to delete in [i, r]
                int runLen = getLength(cnt);

                for (int j = del; j <= k; ++j) {
                    dp[i][j] = min(dp[i][j], runLen + dp[r + 1][j - del]);
                }
            }
        }

        int ans = INF;
        for (int j = 0; j <= k; ++j) {
            ans = min(ans, dp[0][j]);
        }
        return ans;
    }
};