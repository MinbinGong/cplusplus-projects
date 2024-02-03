/*
 * We can scramble a string s to get a string t using the following algorithm:
 *
 * If the length of the string is 1, stop.
 * If the length of the string is > 1, do the following:
 * Split the string into two non-empty substrings at a random index, i.e.,
 * if the string is s, divide it to x and y where s = x + y.
 * Randomly decide to swap the two substrings or to keep them in the same order.
 * i.e., after this step, s may become s = x + y or s = y + x.
 * Apply step 1 recursively on each of the two substrings x and y.
 *
 * Given two strings s1 and s2 of the same length, return true if s2 is a scrambled string of s1,
 *otherwise, return false.
 */
#include <string>
#include <unordered_map>
using namespace std;

unordered_map<string, bool> mp;

bool isScramble(string s1, string s2) {
  int n = s1.size();
  if (n != s2.size()) {
    return false;
  }

  if (s1.compare(s2) == 0) {
    return true;
  }

  if (mp.find(s1 + " " + s2) != mp.end()) {
    return mp[s1 + " " + s2];
  }

  for (int i = 1; i < n; ++i) {
    if (isScramble(s1.substr(0, i), s2.substr(0, i)) && isScramble(s1.substr(i), s2.substr(i))) {
      return mp[s1 + " " + s2] = true;
    }

    if (isScramble(s1.substr(0, i), s2.substr(n - i)) && isScramble(s1.substr(i), s2.substr(0, n - i))) {
      return mp[s1 + " " + s2] = true;
    }
  }

  return mp[s1 + " " + s2] = false;
}
