/*
  Palindromic substrings

  题目描述
  给定一个字符，求其有多少个回文子字符串。回文的定义是左右对称。

  题解
  我们可以从字符串的每个位置开始，向左向右延长，判断存在多少以当前位置为中轴的回文
  子字符串。
 */
#include <string>
using namespace std;

int extendSubstrings(string s, int l, int r) {
  int count = 0;
  while (l >= 0 && r < s.length() && s[l] == s[r]) {
    --l;
    ++r;
    ++count;
  }
  return count;
}

int countSubstring(string s) {
  int count = 0;
  for (int i = 0; i < s.length(); i++) {
    count += extendSubstrings(s, i, i);
    count += extendSubstrings(s, i, i + 1);
  }
  return count;
}