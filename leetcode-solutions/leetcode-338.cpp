/*
 * Counting Bits
 *
 * Given an integer n, return an array ans of length n + 1 such that for each i (0 <= i <= n), ans[i] is the number of
 * 1's in the binary representation of i.
 *
 * Example 1:
 * Input: n = 2
 * Output: [0,1,1]
 * Explanation:
 * 0 --> 0
 * 1 --> 1
 * 2 --> 10
 *
 * Example 2:
 * Input: n = 5
 * Output: [0,1,1,2,1,2]
 * Explanation:
 * 0 --> 0
 * 1 --> 1
 * 2 --> 10
 * 3 --> 11
 * 4 --> 100
 * 5 --> 101
 *
 */

#include <vector>
using namespace std;

vector<int> countBits(int num) {
  if (num == 0) return {0};
  vector<int> dp(num + 1, 0);
  dp[0] = 0;
  dp[1] = 1;
  for (int i = 2; i <= num; i++) {
    if (i & 1)
      dp[i] = dp[i >> 1] + 1;  // i&1 is bitwise AND which is used to check whether last bit is 1 or not.
    else
      dp[i] = dp[i >> 1];
  }
  return dp;
}

vector<int> countBits1(int num) {
  vector<int> dp(num + 1, 0);
  for (int i = 1; i <= num; ++i) {
    dp[i] = i & 1 ? dp[i - 1] + 1 : dp[i >> 1];
  }
  return dp;
}