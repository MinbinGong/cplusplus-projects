/*
 * First Unique Character in a String
 * 
 * Given a string s, find the first non-repeating character in it and return its index. If it does not exist, return -1.
 * 
 * Example 1:
 * Input: s = "leetcode"
 * Output: 0
 * 
 * Example 2:
 * Input: s = "loveleetcode"
 * Output: 2
 * 
 * Example 3:
 * Input: s = "aabb"
 * Output: -1
 * 
 * Constraints:
 * 1 <= s.length <= 10^5
 * s consists of only lowercase English letters.
 * 
 */
#include <string>
#include <vector>
using namespace std;

int firstUniqChar(string s) {
  vector<int> cnt(26, 0);
  vector<int> lastpos(26, 0);
  for (int i = 0; i < s.size(); ++i) {
    ++cnt[s[i] - 'a'];
    lastpos[s[i] - 'a'] = i;
  }

  int res = s.size();
  for (char c = 0; c < 26; ++c)
    if (cnt[c] == 1 && res > lastpos[c]) res = lastpos[c];

  return (res == s.size()) ? -1 : res;
}