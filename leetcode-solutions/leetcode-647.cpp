/*
 * Palindromic substrings
 *
 * Given a string, your task is to count how many palindromic substrings in this string.
 *
 * The substrings with different start indexes or end indexes are counted as different substrings even they consist of same characters.
 *
 * Note:
 *
 * The input string length won't exceed 1000.
 *
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