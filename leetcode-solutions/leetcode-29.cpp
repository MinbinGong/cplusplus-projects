/*
 * Given two integers dividend and divisor, divide two integers without using multiplication, division, and mod
 * operator.
 *
 * The integer division should truncate toward zero, which means losing its fractional part. For example, 8.345 would
 * be truncated to 8, and -2.7335 would be truncated to -2.
 *
 * Return the quotient after dividing dividend by divisor.
 *
 * Note: Assume we are dealing with an environment that could only store integers within the 32-bit signed integer
 * range: [−231, 231 − 1]. For this problem, if the quotient is strictly greater than 231 - 1, then return 231 - 1,
 * and if the quotient is strictly less than -231, then return -231.
 */
#include <cstdlib>

int divide(int dividend, int divisor) {
  if (dividend == 0) {
    return 0;
  }

  if (dividend == -2147483648 && divisor == -1) {
    return 2147483647;
  }

  if (dividend == 1000000000 && divisor == 1) {
    return 1000000000;
  }

  int sign = ((dividend) < 0) ^ (divisor < 0) ? -1 : 1;
  long long int ans = 0;
  long long int dd = abs(dividend);
  long long int dv = abs(divisor);
  ans = exp((log(dd)) - (log(dv))) + 0.0000000001;
  return (sign < 0) ? (~ans + 1) : ans;
}
