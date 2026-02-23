/*
 * Minimum Window Subsequence
 *
 * Given strings S and T, find the minimum (contiguous) substring W of S, so that T is a subsequence of W.
 * 
 * If there is no such window in S that covers all characters in T, return the empty string "". If there are multiple such minimum-length windows, return the one with the left-most starting index.
 * 
 * Example 1:
 * 
 * Input: 
 * S = "abcdebdde", T = "bde"
 * Output: "bcde"
 * Explanation: 
 * "bcde" is the answer because it occurs before "bdde" which has the same length.
 * "deb" is not a smaller window because the elements of T in the window must occur in order.
 * 
 * Note:
 * 1. All the strings in the input will only contain lowercase letters.
 * 2. The length of S will be in the range [1, 20000].
 * 3. The length of T will be in the range [1, 100].
 * 
 */
#include <string>
#include <vector>
using namespace std;

class Solution1 {
public:
    string minWindow(string S, string T) {
        int m = S.size(), n = T.size();
        int minLen = INT_MAX;
        int startIdx = -1;
        
        int i = 0, j = 0;
        while (i < m) {
            if (S[i] == T[j]) {
                j++;
                // Found a complete match of T
                if (j == n) {
                    int right = i;
                    // Backward scan to find the minimal left boundary
                    j--;
                    while (j >= 0) {
                        while (S[i] != T[j]) {
                            i--;
                        }
                        i--;
                        j--;
                    }
                    i++;  // Move to the actual left boundary
                    j++;  // Reset j for next search
                    
                    // Update result if this window is smaller
                    if (right - i + 1 < minLen) {
                        minLen = right - i + 1;
                        startIdx = i;
                    }
                    // Move i forward to continue searching
                    i++;
                }
            }
            i++;
        }
        
        return startIdx == -1 ? "" : S.substr(startIdx, minLen);
    }
};

class Solution2 {
public:
    string minWindow(string S, string T) {
        int m = S.size(), n = T.size();
        if (m == 0 || n == 0) return "";
        
        // dp[i][j] = starting index in S where T[0..j] is a subsequence of S[dp[i][j]..i]
        // -1 means not found
        vector<vector<int>> dp(m, vector<int>(n, -1));
        
        // Initialize first column: match T[0] with S[i]
        if (S[0] == T[0]) dp[0][0] = 0;
        for (int i = 1; i < m; i++) {
            if (S[i] == T[0]) {
                dp[i][0] = i;
            } else {
                dp[i][0] = dp[i-1][0];
            }
        }
        
        // Fill DP table
        for (int j = 1; j < n; j++) {
            for (int i = 1; i < m; i++) {
                if (S[i] == T[j]) {
                    dp[i][j] = dp[i-1][j-1];
                } else {
                    dp[i][j] = dp[i-1][j];
                }
            }
        }
        
        // Find the minimal window
        int minLen = INT_MAX;
        int start = -1;
        for (int i = 0; i < m; i++) {
            if (dp[i][n-1] != -1) {
                int len = i - dp[i][n-1] + 1;
                if (len < minLen) {
                    minLen = len;
                    start = dp[i][n-1];
                }
            }
        }
        
        return start == -1 ? "" : S.substr(start, minLen);
    }
};