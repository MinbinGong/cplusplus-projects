/*
 * Fraction to Recurring Decimal
 *
 * Given two integers representing the numerator and denominator of a fraction,
 * return the fraction in string format.
 *
 * If the fractional part is repeating, enclose the repeating part in
 * parentheses.
 *
 * If multiple answers are possible, return any of them.
 *
 * It is guaranteed that the length of the answer string is less than 104 for
 * all the given inputs.
 */
#include <string>
#include <unordered_map>
using namespace std;

string fractionToDecimal(int numerator, int denominator) {
  if (numerator == 0) {
    return "0";
  }

  string ans{""};
  if (numerator < 0 || denominator < 0) {
    ans += '-';
  }

  long num = labs(numerator), den = labs(denominator);
  long q = num / den;
  long r = num % den;
  ans += to_string(q);

  if (r == 0) {
    return ans;
  }

  ans += '.';
  unordered_map<long, int> mp;
  while (r != 0) {
    if (mp.find(r) != mp.end()) {
      int pos = mp[r];
      ans.insert(pos, "(");
      ans += ')';
      break;
    } else {
      mp[r] = ans.length();
      r *= 10;
      q = r / den;
      r = r % den;
      ans += to_string(q);
    }
  }
  return ans;
}

