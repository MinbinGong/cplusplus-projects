/*
 * 542. 01 Matrix
 *
 * Given a matrix consists of 0 and 1, find the distance of the nearest 0 for each cell.
 * 
 * The distance between two adjacent cells is 1.
 * 
 * Example 1: 
 * Input:
 * 0 0 0
 * 0 1 0
 * 0 0 0
 * Output:
 * 0 0 0
 * 0 1 0
 * 0 0 0
 * 
 * Example 2: 
 * Input:
 * 0 0 0
 * 0 1 0
 * 1 1 1
 * Output:
 * 0 0 0
 * 0 1 0
 * 1 2 1
 * 
 * Note:
 * 1. The number of elements of the given matrix will not exceed 10,000.
 * 2. There are at least one 0 in the given matrix.
 * 3. The cells are adjacent in only four directions: up, down, left and right.
 * 
 */
#include <climits>
#include <vector>
using namespace std;

vector<vector<int>> updateMatrix(vector<vector<int>>& matrix) {
  if (matrix.empty()) {
    return {};
  }
  int n = matrix.size(), m = matrix[0].size();
  vector<vector<int>> dp(n, vector<int>(n, INT_MAX - 1));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (matrix[i][j] == 0) {
        dp[i][j] = 0;
      } else {
        if (j > 0) {
          dp[i][j] = min(dp[i][j], dp[i][j - 1] + 1);
        }
        if (i > 0) {
          dp[i][j] = min(dp[i][j], dp[i - 1][j] + 1);
        }
      }
    }
  }

  for (int i = n - 1; i >= 0; --i) {
    for (int j = m - 1; j >= 0; --j) {
      if (matrix[i][j] != 0) {
        if (j < m - 1) {
          dp[i][j] = min(dp[i][j], dp[i][j + 1] + 1);
        }
        if (i < n - 1) {
          dp[i][j] = min(dp[i][j], dp[i + 1][j] + 1);
        }
      }
    }
  }
  return dp;
}