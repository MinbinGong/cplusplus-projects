#include <algorithm>
#include <vector>
using namespace std;

int dfs(vector<vector<int>> &grey, vector<vector<int>> &memo, int i, int j, vector<vector<int>> &matrix) {
  if (memo[i][j] != -1) return memo[i][j];

  grey[i][j] = 1;

  int maxNum{0};
  if (i + 1 < matrix.size() && grey[i + 1][j] == 0 && matrix[i][j] < matrix[i + 1][j])
    maxNum = max(maxNum, 1 + dfs(grey, memo, i + 1, j, matrix));
  if (i > 0 && grey[i - 1][j] == 0 && matrix[i][j] < matrix[i - 1][j])
    maxNum = max(maxNum, 1 + dfs(grey, memo, i - 1, j, matrix));
  if (j + 1 < matrix[0].size() && grey[i][j + 1] == 0 && matrix[i][j] < matrix[i][j + 1])
    maxNum = max(maxNum, 1 + dfs(grey, memo, i, j + 1, matrix));
  if (j > 0 && grey[i][j - 1] == 0 && matrix[i][j] < matrix[i][j - 1])
    maxNum = max(maxNum, 1 + dfs(grey, memo, i, j - 1, matrix));

  grey[i][j] = 0;
  return memo[i][j] = maxNum;
}

int longestIncreasingPath(vector<vector<int>> &matrix) {
  int n = matrix.size();
  if (n == 0) return 0;
  int m = matrix[0].size();
  if (m == 0) return 0;
  int ret = 0;
  vector<vector<int>> grey(n, vector<int>(m, 0));
  vector<vector<int>> memo(n, vector<int>(m, -1));
  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < m; j++) {
      ret = max(ret, dfs(grey, memo, i, j, matrix));
    }
  }
  return ret;
}