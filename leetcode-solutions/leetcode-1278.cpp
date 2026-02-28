/**
 * 1278. Palindrome Partitioning III
 * 
 * You are given a string s containing lowercase letters and an integer k. You need to :
 * 
 * First, change some characters of s to other lowercase English letters.
 * Then divide s into k non-empty disjoint substrings such that each substring is palindrome.
 * Return the minimal number of characters that you need to change to divide the string.
 * 
 * Example 1:
 * Input: s = "abc", k = 2
 * Output: 1
 * Explanation: You can split the string into "ab" and "c", and change 1 character in "ab" to make it palindrome.
 * 
 * Example 2:
 * Input: s = "aabbc", k = 3
 * Output: 0
 * Explanation: You can split the string into "aa", "bb" and "c", all of them are palindrome.
 * 
 * Example 3:
 * Input: s = "leetcode", k = 8
 * Output: 0
 * 
 * Note:
 * 1 <= k <= s.length <= 100.
 * s only contains lowercase English letters.
 * 
 */
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    int palindromePartition(string s, int k) {
        int n = s.size();
        // cost[i][j] = min changes to make s[i..j] palindrome
        vector<vector<int>> cost(n, vector<int>(n, 0));
        for (int len = 2; len <= n; ++len) {          // substring length
            for (int i = 0; i + len - 1 < n; ++i) {
                int j = i + len - 1;
                // base case: if length 2, cost is 0 if chars equal else 1
                // but we can compute recursively
                cost[i][j] = cost[i+1][j-1] + (s[i] == s[j] ? 0 : 1);
            }
        }
        // dp[i][p] = min cost for first i characters (0..i-1) partitioned into p palindromes
        const int INF = 1e9;
        vector<vector<int>> dp(n+1, vector<int>(k+1, INF));
        // p = 1
        for (int i = 1; i <= n; ++i) {
            dp[i][1] = cost[0][i-1];
        }
        for (int p = 2; p <= k; ++p) {
            for (int i = p; i <= n; ++i) {          // need at least p chars
                for (int j = p-1; j < i; ++j) {     // last palindrome is s[j..i-1]
                    dp[i][p] = min(dp[i][p], dp[j][p-1] + cost[j][i-1]);
                }
            }
        }
        return dp[n][k];
    }
};