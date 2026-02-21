/*
 * Base 7
 *
 * Given an integer num, return a string of its base 7 representation.
 * 
 * Constraints:
 * -107 <= num <= 107
 * 
 */
#include <string>
using namespace std;

string convertToBase7(int n) {
  if (n == 0) {
    return "0";
  }

  bool is_negative = n < 0;
  if (is_negative) {
    n = -n;
  }

  string ans;
  while (n) {
    int a = n / 7, b = n % 7;
    ans = to_string(b) + ans;
    n = a;
  }
  return is_negative ? "-" + ans : ans;
}