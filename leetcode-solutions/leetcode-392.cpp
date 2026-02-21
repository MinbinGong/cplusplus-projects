/*
 * Is Subsequence
 * 
 * Given two strings s and t, return true if s is a subsequence of t, or false otherwise.
 * 
 * A subsequence of a string is a new string that is formed from the original string by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. (i.e., "ace" is a subsequence of "abcde" while "aec" is not).
 * 
 * Example 1:
 * Input: s = "abc", t = "ahbgdc"
 * Output: true
 * 
 * Example 2:
 * Input: s = "axc", t = "ahbgdc"
 * Output: false
 * 
 * Constraints:
 * 0 <= s.length <= 100
 * 0 <= t.length <= 10^4
 * s and t consist only of lowercase English letters.
 * 
 */
#include <string>
using namespace std;

bool isSubsequent(string s, string t) {
  if (s.length() > t.length()) return false;
  if (s.empty() || t.empty()) return true;
  int sidx = 0;
  for (int i = 0; i < t.length(); i++) {
    if (t[i] == s[sidx] && ++sidx == s.length()) return true;
  }
  return false;
}