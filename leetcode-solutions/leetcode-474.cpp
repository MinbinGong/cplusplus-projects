/*
 * Ones and Zeros
 *
 *  You are given an array of binary strings strs and two integers m and n.
 *
 *  Return the size of the largest subset of strs such that there are at most m 0's and n 1's in the subset.
 *
 *  A set x is a subset of a set y if all elements of x are also elements of y.
 *
 *  Constraints:
 *  1 <= strs.length <= 600
 *  1 <= strs[i].length <= 100
 *  strs[i] consists of only digits '0' and '1'.
 *  1 <= m, n <= 100
 * 
 */
#include <string>
#include <utility>
#include <vector>
using namespace std;

pair<int, int> count(const string &s) {
  int count0 = s.length(), count1 = 0;
  for (const char &c : s) {
    if (c == '1') {
      ++count1;
      --count0;
    }
  }
  return make_pair(count0, count1);
}

int findMaxForm(vector<string> &strs, int m, int n) {
  vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
  for (const string &str : strs) {
    auto [count0, count1] = count(str);
    for (int i = m; i >= count0; --i) {
      for (int j = n; j >= count1; --j) {
        dp[i][j] = max(dp[i][j], 1 + dp[i - count0][j - count1]);
      }
    }
  }
  return dp[m][n];
}