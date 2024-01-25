/*
Valid Number

  A valid number can be split up into these components (in order):

  A decimal number or an integer.
  (Optional) An 'e' or 'E', followed by an integer.
  A decimal number can be split up into these components (in order):

  (Optional) A sign character (either '+' or '-').
  One of the following formats:
  One or more digits, followed by a dot '.'.
  One or more digits, followed by a dot '.', followed by one or more digits.
  A dot '.', followed by one or more digits.
  An integer can be split up into these components (in order):

  (Optional) A sign character (either '+' or '-').
  One or more digits.
  For example, all the following are valid numbers:
    ["2", "0089", "-0.1", "+3.14", "4.", "-.9", "2e10", "-90E3", "3e+7", "+6e-1", "53.5e93", "-123.456e789"],
  while the following are not valid numbers:
    ["abc", "1a", "1e", "e3", "99e2.5", "--6", "-+3", "95a54e53"].

  Given a string s, return true if s is a valid number.

  Approach
  What we need to iterate and check:

  1. Iterate over sign
  2. If it is at the end return false
  3. Iterate over the digits
  4. If we reach the end of the string return true
  5. Iterate dot and the check the valid number condition
  6. Check digits after dot
  7. Iterate decimals until we reach the last index or e
  8. If we reach the end of the string return true
  9. Iterate over the sign
  10.Iterate over the digits
 */
#include <string>
using namespace std;

bool is_valid_number(string s) {
  if (s.empty()) {
    return false;
  }

  int i = 0;
  if (s[i] == '+' || s[i] == '-') {
    i++;
  }

  bool has_integer_part = false;
  while (i < s.size() && isdigit(s[i])) {
    has_integer_part = true;
    i++;
  }

  bool has_decimal_part = false;
  if (i < s.size() && s[i] == '.') {
    i++;
    while (i < s.size() && isdigit(s[i])) {
      has_decimal_part = true;
      i++;
    }
  }

  if (i < s.size() && (s[i] == 'e' || s[i] == 'E')) {
    i++;
    if (i < s.size() && (s[i] == '+' || s[i] == '-')) {
      i++;
    }

    if (i == s.size() || !isdigit(s[i])) {
      return false;
    }
    while (i < s.size() && isdigit(s[i])) {
      i++;
    }
  }
  return i == s.size() && (has_integer_part || has_decimal_part);
}