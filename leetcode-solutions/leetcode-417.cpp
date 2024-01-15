#include <vector>
using namespace std;

vector<int> direction = {0, 1, 0, -1, 0};

bool outOfBound(int i, int j, int m, int n) { return (i < 0 || j < 0 || i >= m || j >= n); }

void dfs(vector<vector<int>> &matrix, vector<vector<bool>> &visited, int i, int j) {
  int m = matrix.size();
  int n = matrix[0].size();

  visited[i][j] = true;

  for (int k = 1; k < direction.size(); k++) {
    int row = i + direction[k - 1];
    int col = j + direction[k];

    if (!outOfBound(row, col, m, n) && !visited[row][col] && matrix[row][col] >= matrix[i][j])
      dfs(matrix, visited, row, col);
  }
}

vector<vector<int>> pacificAtlantic(vector<vector<int>> &matrix) {
  if (matrix.size() == 0) return {};

  int m = matrix.size();
  int n = matrix[0].size();

  vector<vector<bool>> pacific(m, vector<bool>(n, false));
  vector<vector<bool>> atlantic(m, vector<bool>(n, false));

  for (int i = 0; i < m; i++) {
    if (!pacific[i][0]) dfs(matrix, pacific, i, 0);
    if (!atlantic[i][n - 1]) dfs(matrix, atlantic, i, n - 1);
  }

  for (int j = 0; j < n; j++) {
    if (!pacific[0][j]) dfs(matrix, pacific, 0, j);
    if (!atlantic[m - 1][j]) dfs(matrix, atlantic, m - 1, j);
  }

  vector<vector<int>> res;

  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      if (pacific[i][j] && atlantic[i][j]) res.push_back({i, j});
    }
  }

  return res;
}
