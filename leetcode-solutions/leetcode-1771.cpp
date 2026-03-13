/**
 * 1771. Maximize Palindrome Length From Subsequences
 * 
 * You are given two strings, word1 and word2. You want to construct a string in the following manner:
 * 
 * Choose some non-empty subsequence subsequence1 from word1.
 * Choose some non-empty subsequence subsequence2 from word2.
 * Concatenate the subsequences: subsequence1 + subsequence2, to make the string.
 * Return the length of the longest palindrome that can be constructed in the described manner. If no palindromes can be constructed, return 0.
 * 
 * A subsequence of a string s is a string that can be made by deleting some (possibly none) characters from s without changing the order of the remaining characters.
 * 
 * A palindrome is a string that reads the same forward as well as backward.
 * 
 * Example 1:
 * 
 * Input: word1 = "cacb", word2 = "cbba"
 * Output: 5
 * Explanation: The longest palindrome we can construct is "abccba", with length 5.
 * 
 * Example 2:
 * 
 * Input: word1 = "ab", word2 = "pqrs"
 * Output: 0
 * Explanation: We cannot construct any palindrome from the described method.
 * 
 * Example 3:
 * 
 * Input: word1 = "aa", word2 = "bb"
 * Output: 2
 * Explanation: The longest palindrome we can construct is "abba", with length 2.
 * 
 * Constraints:
 * 
 * 1 <= word1.length, word2.length <= 1000
 * word1 and word2 consist of lowercase English letters.
 * 
 */

#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Solution {
public:
    int longestPalindrome(string word1, string word2) {
        string s = word1 + word2;
        int n = s.size();
        int len1 = word1.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));
        int ans = 0;
        
        for (int i = n - 1; i >= 0; i--) {
            dp[i][i] = 1;
            for (int j = i + 1; j < n; j++) {
                if (s[i] == s[j]) {
                    int inner = (i + 1 <= j - 1) ? dp[i + 1][j - 1] : 0;
                    dp[i][j] = inner + 2;
                } else {
                    dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
                }
                if (i < len1 && j >= len1) {
                    ans = max(ans, dp[i][j]);
                }
            }
        }
        
        return ans;
    }
};