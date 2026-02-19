/*
 * Word Break
 * 
 * Given a string s and a dictionary of strings wordDict, return true if s can be segmented into a space-separated sequence of one or more dictionary words.
 * 
 * Note that the same word in the dictionary may be reused multiple times in the segmentation.
 * 
 * Example 1:
 * Input: s = "leetcode", wordDict = ["leet","code"]
 * Output: true
 * Explanation: Return true because "leetcode" can be segmented as "leet code".
 * 
 * Example 2:
 * Input: s = "applepenapple", wordDict = ["apple","pen"]
 * Output: true
 * Explanation: Return true because "applepenapple" can be segmented as "apple pen apple".
 * Note that you are allowed to reuse a dictionary word.
 * 
 * Example 3:
 * Input: s = "catsandog", wordDict = ["cats","dog","sand","and","cat"]
 * Output: false
 */
#include <string>
#include <vector>
using namespace std;

bool workBreak(string &s, vector<string> &wordDict) {
  int n = s.length();
  vector<bool> dp(n + 1, false);
  dp[0] = true;
  for (int i = 1; i <= n; ++i) {
    for (const auto &word : wordDict) {
      int len = word.length();
      if (i >= len && s.substr(i - len, len) == word) {
        dp[i] = dp[i] || dp[i - len];
      }
    }
  }
  return dp[n];
}