/*
 * Nth Digit
 * 
 * Given an integer n, return the nth digit of the infinite integer sequence [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, ...].
 * 
 * Example 1:
 * Input: n = 3
 * Output: 3
 * 
 * Example 2:
 * Input: n = 11
 * Output: 0
 * Explanation: The 11th digit of the sequence 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, ... is a 0, which is part of the number 10.
 * 
 * Constraints:
 * 1 <= n <= 2^31 - 1
 */
#include <string>
using namespace std;

int findNthDigit(int n) {
  long long int x = 9;
  long long int y = 1;
  long long int quo = 0;
  long long int rem = 0;
  int pre = 1;
  int res = 0;

  while (n - (x * y) > 0) {
    n -= (x * y);
    x = x * 10;
    y += 1;
    pre *= 10;
  }
  pre -= 1;
  quo = n / y;
  rem = n % y;
  if (rem == 0) {
    int ans = pre + quo;
    string a = to_string(ans);
    res = (int)a[y - 1] - (int)'0';
  }

  else {
    int ans = pre + quo + 1;
    string a = to_string(ans);
    res = (int)a[rem - 1] - (int)'0';
  }

  return res;
}