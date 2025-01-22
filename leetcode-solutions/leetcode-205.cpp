/*
  Isomorphic Strings

  题目描述
  判断两个字符串是否同构。同构的定义是，可以通过把一个字符串的某些相同的字符转换成
  另一些相同的字符，使得两个字符串相同，且两种不同的字符不能够被转换成同一种字符。

  题解
  我们可以将问题转化一下：记录两个字符串每个位置的字符第一次出现的位置，如果两个字
  符串中相同位置的字符与它们第一次出现的位置一样，那么这两个字符串同构。举例来说，对于
  “paper”和“title”
  ，假设我们现在遍历到第三个字符“p”和“t”
  ，发现它们第一次出现的位置都
  在第一个字符，则说明目前位置满足同构。
 */
#include <climits>
#include <string>
#include <vector>
using namespace std;

bool isIsomorphic(string s, string t) {
  vector<int> mp_s(CHAR_MAX + 1), mp_t(CHAR_MAX + 1);
  for (int i = 0, ns = 0, nt = 0; i < s.length(); ++i) {
    if (!mp_s[s[i]]) mp_s[s[i]] = ++ns;
    if (!mp_t[t[i]]) mp_t[t[i]] = ++nt;
    if (mp_s[s[i]] != mp_t[t[i]]) return false;
  }
  return true;
}

bool isIsomorphic1(string s, string t) {
  vector<int> sFirstIndex(256, 0), tFirstIndex(256, 0);
  for (int i = 0; i < s.length(); ++i) {
    if (sFirstIndex[s[i]] != tFirstIndex[t[i]]) {
      return false;
    }
    sFirstIndex[s[i]] = tFirstIndex[t[i]] = i + 1;
  }
  return true;
}