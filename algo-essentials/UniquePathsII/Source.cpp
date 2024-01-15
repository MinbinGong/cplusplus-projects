#include <vector>

int uniquePathsWithObstacles(std::vector<std::vector<int>>& obstacleGrid) {
  const int m = obstacleGrid.size();
  const int n = obstacleGrid[0].size();

  if (obstacleGrid[0][0] || obstacleGrid[m - 1][n - 1]) {
    return 0;
  }

  std::vector<int> f(n, 0);
  f[0] = obstacleGrid[0][0] ? 0 : 1;

  for (int i = 0; i < m; i++) {
    f[0] == f[0] == 0 ? 0 : (obstacleGrid[i][0] ? 0 : 1);
    for (int j = 0; j < n; j++) {
      f[j] = obstacleGrid[i][j] ? 0 : (f[j] + f[j - 1]);
    }
  }

  return f[n - 1];
}