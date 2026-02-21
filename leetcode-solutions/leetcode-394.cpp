/*
 * Decode String
 *
 * Given an encoded string, return its decoded string.
 * 
 * The encoding rule is: k[encoded_string], where the encoded_string inside the square brackets is being repeated exactly k times. Note that k is guaranteed to be a positive integer.
 * 
 * You may assume that the input string is always valid; No extra white spaces, square brackets are well-formed, etc.
 * 
 * Furthermore, you may assume that the original data does not contain any digits and that digits are only for those repeat numbers, k. For example, there won't be input like 3a or 2[4].
 * 
 */
#include <string>
using namespace std;

string decodeString(string s) {
  bool flag = false, recurred = false, accum = false;
  string ret;
  int counter = 0, startidx = 0, multiplier = 0;
  for (int i = 0; i < s.size(); ++i) {
    if (!flag || accum) {
      if (s[i] >= '0' && s[i] <= '9') {
        startidx = i + 2;
        multiplier = multiplier * 10 + s[i] - '0';
        flag = accum = true;
      } else if (!accum)
        ret += s[i];
      if (s[i + 1] < '0' || s[i + 1] > '9') accum = false;
    } else if (flag) {
      s[i] == '[' ? ++counter : (s[i] == ']' ? --counter : counter += 0);
      if (!counter) {
        string res = decodeString(s.substr(startidx, i - startidx));
        recurred = true, flag = false;
        while (multiplier > 0) ret += res, multiplier--;
      }
    }
  }
  if (!recurred) return s;
  return ret;
}