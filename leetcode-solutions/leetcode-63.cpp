/*
  Unique Paths with obstacles

  You are given an m x n integer array grid. There is a robot initially located at the top-left corner
  (i.e., grid[0][0]). The robot tries to move to the bottom-right corner (i.e., grid[m - 1][n - 1]).
  The robot can only move either down or right at any point in time.

  An obstacle and space are marked as 1 or 0 respectively in grid.
  A path that the robot takes cannot include any square that is an obstacle.

  Return the number of possible unique paths that the robot can take to reach the bottom-right corner.

  The testcases are generated so that the answer will be less than or equal to 2 * 109.
 */
#include <vector>
using namespace std;

int uniquePathsWithObstacles(vector<vector<int>>& grid) {
  int n = grid.size(), m = grid[0].size();

  vector<vector<int>> dp(n + 4, vector<int>(m + 4, 0));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (i == 0 && j == 0 && !grid[i][j]) {
        dp[i][j] = 1;
      } else if (!grid[i][j]) {
        if (i != 0) {
          dp[i][j] += dp[i - 1][j];
        }
        if (j != 0) {
          dp[i][j] += dp[i][j - 1];
        }
      }
    }
  }
  return dp[n - 1][m - 1];
}