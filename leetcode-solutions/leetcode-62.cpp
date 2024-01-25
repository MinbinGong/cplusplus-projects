/*
  Unique Paths

  There is a robot on an m x n grid. The robot is initially located at the top-left corner (i.e., grid[0][0]).
  The robot tries to move to the bottom-right corner (i.e., grid[m - 1][n - 1]).
  The robot can only move either down or right at any point in time.

  Given the two integers m and n, return the number of possible unique paths that the robot can take to reach the
  bottom-right corner.

  The test cases are generated so that the answer will be less than or equal to 2 * 109.

 */
#include <vector>
using namespace std;

int solve(int m, int n, vector<vector<int>> &dp) {
  if (m == 0 && n == 0) {
    return 1;
  }
  if (m < 0 || n < 0) {
    return 0;
  }
  if (dp[m][n] != -1) {
    return dp[m][n];
  }

  int up = solve(m - 1, n, dp);
  int left = solve(m, n - 1, dp);
  return dp[m][n] = up + left;
}

int uniquePaths(int m, int n) {
  vector<vector<int>> dp(m, vector<int>(n, -1));
  return solve(m - 1, n - 1, dp);
}

int uniquePaths1(int m, int n) {
  vector<int> prev(n, 0);

  for (int i = 0; i < m; ++i) {
    vector<int> temp(n, 0);
    for (int j = 0; j < n; ++j) {
      if (i == 0 && j == 0) {
        temp[j] = 1;
      }
      if (i > 0) {
        temp[j] += prev[j];
      }
      if (j > 0) {
        temp[j] += temp[j - 1];
      }
    }
    prev = temp;
  }
  return prev[n - 1];
}