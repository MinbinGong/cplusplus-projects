/*
 * remove-k-digits
 * 
 * Given string num representing a non-negative integer num, and an integer k, return the smallest possible integer after removing k digits from num.
 * 
 * Example 1:
 * Input: num = "1432219", k = 3
 * Output: "1219"
 * Explanation: Remove the three digits 4, 3, and 2 to form the new number 1219 which is the smallest.
 * 
 * Example 2:
 * Input: num = "10200", k = 1
 * Output: "200"
 * Explanation: Remove the leading 1 and the number is 200. Note that the output must not contain leading zeroes.
 * 
 * Example 3:
 * Input: num = "10", k = 2
 * Output: "0"
 * Explanation: Remove all the digits from the number and it is left with nothing which is 0.
 * 
 * Constraints:
 * 1 <= k <= num.length <= 10^5
 * num consists of only digits.
 * num does not have any leading zeroes.
 * 
 */
#include <string>
using namespace std;

string remove(string s, int k) {
  if (k == 0) return s;
  if (s.length() == k) return "";
  char c = s[0];
  int ind = 0;
  for (int i = 1; i <= k; i++) {
    if (s[i] < c) {
      c = s[i];
      ind = i;
    }
  }
  return c + remove(s.substr(ind + 1), k - ind);
}

string removeKdigits(string s, int k) {
  int n = s.length();
  if (n == k) return "0";
  string d = remove(s, k);
  while (d[0] == '0' && d != "0") d.erase(d.begin());
  return d;
}