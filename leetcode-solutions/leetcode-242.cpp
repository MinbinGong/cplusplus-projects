/*
 *  Valid Anagram
 *
 * Constraints:
 * 1. 1 <= s.length, t.length <= 5 * 10^4
 * 2. s and t consist of lowercase English letters.
 */
#include <string>
#include <vector>
using namespace std;

bool isAnagram(string s, string t) {
  if (s.length() != t.length()) {
    return false;
  }

  vector<int> counts(26, 0);
  for (int i = 0; i < s.length(); ++i) {
    ++counts[s[i] - 'a'];
    --counts[t[i] - 'a'];
  }

  for (int i = 0; i < 26; ++i) {
    if (counts[i]) {
      return false;
    }
  }
  return true;
}