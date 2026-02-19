/*
 * Range Bitwise AND
 * Given two integers left and right that represent the range [left, right], return the bitwise AND of all numbers in
 * this range, inclusive.
 *
 * Constraints:
 * 1. 0 <= left <= right <= 2^31 - 1
 * 2. left <= right
 * 3. right - left <= 10^9
 * 4. left and right are both integers.
 */
int rangeBitwiseAnd(int m, int n) {
  while (n > m) {
    n &= (n - 1);  // Clear the lowest set bit of n
  }
  return n;
}