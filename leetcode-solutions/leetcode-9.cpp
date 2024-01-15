/*
 * Palindrome number
 */
#include <string>
using namespace std;

bool isPalindrome(int x) {
  if (x < 0) return false;

  string exp = to_string(x);
  int len = exp.length();

  if (len == 1) return true;

  int rem = len % 2, half = len / 2, i = half - 1, j = 0;

  if (rem == 0)  // even length
    j = half;
  else  // odd length
    j = half + 1;

  while (i >= 0) {
    if (exp[i--] != exp[j++]) {
      return false;
    }
  }

  return true;
}