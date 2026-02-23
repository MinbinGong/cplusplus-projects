/*
 * Count Different Palindromic Subsequences
 *
 * Given a string S, find the number of different non-empty palindromic subsequences in S, and return that number modulo 10^9 + 7.
 * 
 * A subsequence of a string S is obtained by deleting 0 or more characters from S.
 * 
 * A sequence is palindromic if it is equal to the sequence reversed.
 * 
 * Two sequences A_1, A_2, ... and B_1, B_2, ... are different if there is some i for which A_i != B_i.
 * 
 * Note:
 * 1. The length of S will be in the range [1, 1000].
 * 2. Each character S[i] will be in the set {'a', 'b', 'c', 'd'}.
 * 3. The sum of S[i] will not exceed 10000.
 * 
 */
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    int countPalindromicSubsequences(string s) {
        const int MOD = 1e9 + 7;
        int n = s.size();
        
        // next[i][c] = smallest index >= i with character c (0..25), or n if none
        // prev[i][c] = largest index <= i with character c, or -1 if none
        vector<vector<int>> next(n, vector<int>(26, n));
        vector<vector<int>> prev(n, vector<int>(26, -1));
        
        for (int c = 0; c < 26; ++c) {
            int last = n;
            for (int i = n - 1; i >= 0; --i) {
                if (s[i] - 'a' == c) last = i;
                next[i][c] = last;
            }
            last = -1;
            for (int i = 0; i < n; ++i) {
                if (s[i] - 'a' == c) last = i;
                prev[i][c] = last;
            }
        }
        
        // dp[i][j] = number of distinct palindromic subsequences in s[i..j]
        vector<vector<long long>> dp(n, vector<long long>(n, 0));
        
        for (int len = 1; len <= n; ++len) {
            for (int i = 0; i + len - 1 < n; ++i) {
                int j = i + len - 1;
                if (i == j) {
                    dp[i][j] = 1;
                    continue;
                }
                if (s[i] != s[j]) {
                    long long a = dp[i + 1][j];
                    long long b = dp[i][j - 1];
                    long long c = (i + 1 <= j - 1) ? dp[i + 1][j - 1] : 0;
                    dp[i][j] = a + b - c;
                } else {
                    // s[i] == s[j]
                    int left = next[i + 1][s[i] - 'a'];   // first same char after i
                    int right = prev[j - 1][s[i] - 'a']; // last same char before j
                    long long inner = (i + 1 <= j - 1) ? dp[i + 1][j - 1] : 0;
                    
                    if (left > right) {
                        // no same character inside
                        dp[i][j] = 2 * inner + 2;
                    } else if (left == right) {
                        // exactly one same character inside
                        dp[i][j] = 2 * inner + 1;
                    } else {
                        // at least two same characters inside
                        long long inner2 = (left + 1 <= right - 1) ? dp[left + 1][right - 1] : 0;
                        dp[i][j] = 2 * inner - inner2;
                    }
                }
                // modulo operation
                dp[i][j] %= MOD;
                if (dp[i][j] < 0) dp[i][j] += MOD;
            }
        }
        return dp[0][n - 1];
    }
};