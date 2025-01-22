/*
  Valid Anagram

  题目描述
  判断两个字符串包含的字符是否完全相同。

  题解
  我们可以利用哈希表或者数组统计两个数组中每个数字出现的频次，若频次相同，则说明它
  们包含的字符完全相同。
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