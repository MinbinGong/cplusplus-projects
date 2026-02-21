/*
 * Arranging Coins
 *
 * You have n coins and you want to build a staircase with these coins. The staircase consists of k rows where the ith row has exactly i coins. The last row of the staircase may be incomplete.
 * 
 * Given the integer n, return the number of complete rows of the staircase you will build.
 * 
 * Constraints:
 * 1 <= n <= 231 - 1
 * 
 */
#include <algorithm>
using namespace std;

int arrangeCoins(int n) {
  int left{0}, right{n};
  while (left <= right) {
    int mid = left + (right - left) / 2;
    long csum = mid * (mid + 1L) / 2;
    if (csum = n) return mid;

    if (n < csum) {
      right = mid - 1;
    } else {
      left = mid + 1;
    }
  }
  return right;
}