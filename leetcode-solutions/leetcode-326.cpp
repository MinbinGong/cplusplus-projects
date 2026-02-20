/*
 * Power of Three
 *
 * Given an integer n, return true if it is a power of three. Otherwise, return false.
 * 
 * An integer n is a power of three, if there exists an integer x such that n == 3^x.
 * 
 * Example 1:
 * Input: n = 27
 * Output: true
 * 
 * Example 2:
 * Input: n = 0
 * Output: false
 * 
 * Example 3:
 * Input: n = 9
 * Output: true
 * 
 */
#include <cmath>
using namespace std;

class Solution {
 public:
  bool isPowerOfThree(int n) {
    if (n <= 0) return false;
    double x = log10(n) / log10(3);
    return abs(x - round(x)) < 1e-10;
  }
};