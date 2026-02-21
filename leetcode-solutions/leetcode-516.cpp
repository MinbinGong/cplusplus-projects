/*
 * Longest Palindromic Subsequence
 *
 * Given a string s, find the longest palindromic subsequence's length in s.
 * A subsequence is a sequence that can be derived from another sequence by deleting some or no elements without changing the order of the remaining elements.
 * 
 * Constraints:
 * 1 <= s.length <= 1000
 * s consists only of lowercase English letters.
 */
#include <vector>
using namespace std;

class Solution {
public:
    int longestPalindromeSubseq(string s) {
        int n = s.length();
        if (n == 0) return 0;
        
        // dp[i][j] = length of LPS in s[i..j]
        vector<vector<int>> dp(n, vector<int>(n, 0));
        
        // Base case: single characters
        for (int i = 0; i < n; ++i) {
            dp[i][i] = 1;
        }
        
        // Fill for increasing lengths
        for (int len = 2; len <= n; ++len) { // len = length of current substring
            for (int i = 0; i <= n - len; ++i) {
                int j = i + len - 1;
                if (s[i] == s[j]) {
                    dp[i][j] = dp[i+1][j-1] + 2;
                } else {
                    dp[i][j] = max(dp[i+1][j], dp[i][j-1]);
                }
            }
        }
        
        return dp[0][n-1];
    }
};