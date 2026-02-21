/*
 * Hamming Distance
 *
 * The Hamming distance between two integers is the number of positions at which the corresponding bits are different.
 *
 * Given two integers x and y, return the Hamming distance between them.
 *
 * Constraints:
 * 0 <= x, y <= 231 - 1
 * 
 */
int hammingDistance(int x, int y) {
  int diff = x ^ y;
  int res = 0;
  while (diff) {
    res += diff & 1;
    diff >>= 1;
  }
  return res;
}