/*
 * Longest Substring with At Least K Repeating Characters
 * 
 * Given a string s and an integer k, return the length of the longest substring of s such that the frequency of each character in this substring is greater than or equal to k.
 * 
 * Example 1:
 * Input: s = "aaabb", k = 3
 * Output: 3
 * Explanation: The longest substring is "aaa", as 'a' is repeated 3 times.
 * 
 * Example 2:
 * Input: s = "ababbc", k = 2
 * Output: 5
 * Explanation: The longest substring is "ababb", as 'a' is repeated 2 times and 'b' is repeated 3 times.
 * 
 * Constraints:
 * 1 <= s.length <= 10^4
 * s consists of only lowercase English letters.
 * 1 <= k <= 10^5
 */
#include <string>
#include <vector>
using namespace std;

int longestSubstring(string s, int k) {
  vector<int> vocab(26, 0);
  for (auto ch : s) {
    ++vocab[ch - 'a'];
  }
  vector<int> cands;
  for (int i = 0; i < s.size(); ++i) {
    if (vocab[s[i] - 'a'] < k) {
      cands.emplace_back(i);
    }
  }
  if (cands.empty()) return s.size();
  cands.emplace_back(s.size());
  int start = 0;
  int longest = 0;
  for (auto cand : cands) {
    if (cand - start >= k) {
      longest = max(longestSubstring(s.substr(start, cand - start), k), longest);
    }
    start = cand + 1;
  }
  return longest;
}