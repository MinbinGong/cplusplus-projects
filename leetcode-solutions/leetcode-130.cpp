/*
  Surrounded Regions

  Given an m x n matrix board containing 'X' and 'O',
  capture all regions that are 4-directionally surrounded by 'X'.

  A region is captured by flipping all 'O's into 'X's in that surrounded region.
*/
#include <vector>
using namespace std;

void dfs(int row, int col, vector<vector<int>>& vis, vector<vector<char>>& board, int delrow[], int delcol[], int n,
         int m) {
  vis[row][col] = 1;
  for (int i = 0; i < 4; i++) {
    int nrow = row + delrow[i];
    int ncol = col + delcol[i];
    if (nrow >= 0 && nrow < n && ncol >= 0 && ncol < m && vis[nrow][ncol] == 0 && board[nrow][ncol] == 'O') {
      dfs(nrow, ncol, vis, board, delrow, delcol, n, m);
    }
  }
}

void solve(vector<vector<char>>& board) {
  int n = board.size();
  int m = board[0].size();
  vector<vector<int>> vis(n, vector<int>(m, 0));
  int delrow[] = {-1, 0, 1, 0};
  int delcol[] = {0, 1, 0, -1};
  // left to right
  for (int i = 0; i < m; i++) {
    if (!vis[0][i] && board[0][i] == 'O') {
      dfs(0, i, vis, board, delrow, delcol, n, m);
    }
    if (!vis[n - 1][i] && board[n - 1][i] == 'O') {
      dfs(n - 1, i, vis, board, delrow, delcol, n, m);
    }
  }
  // top to buttom
  for (int j = 0; j < n; j++) {
    if (!vis[j][0] && board[j][0] == 'O') {
      dfs(j, 0, vis, board, delrow, delcol, n, m);
    }
    if (!vis[j][m - 1] && board[j][m - 1] == 'O') {
      dfs(j, m - 1, vis, board, delrow, delcol, n, m);
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (!vis[i][j] && board[i][j] == 'O') {
        board[i][j] = 'X';
      }
    }
  }
}
void solve1(vector<vector<char>>& board) {
    if (board.empty() || board[0].empty()) return;
    int m = board.size();
    int n = board[0].size();
    queue<pair<int, int>> q;
    
    // Push all border 'O's into queue and mark as visited (e.g., 'T')
    for (int i = 0; i < m; ++i) {
        if (board[i][0] == 'O') { board[i][0] = 'T'; q.push({i, 0}); }
        if (board[i][n - 1] == 'O') { board[i][n - 1] = 'T'; q.push({i, n - 1}); }
    }
    for (int j = 0; j < n; ++j) {
        if (board[0][j] == 'O') { board[0][j] = 'T'; q.push({0, j}); }
        if (board[m - 1][j] == 'O') { board[m - 1][j] = 'T'; q.push({m - 1, j}); }
    }
    
    // Directions: up, down, left, right
    vector<pair<int, int>> dirs = {{1,0}, {-1,0}, {0,1}, {0,-1}};
    
    // BFS
    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        for (auto [dx, dy] : dirs) {
            int nx = x + dx;
            int ny = y + dy;
            if (nx >= 0 && nx < m && ny >= 0 && ny < n && board[nx][ny] == 'O') {
                board[nx][ny] = 'T';
                q.push({nx, ny});
            }
        }
    }
    
    // Final pass: flip 'O' to 'X', revert 'T' to 'O'
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (board[i][j] == 'O') board[i][j] = 'X';
            else if (board[i][j] == 'T') board[i][j] = 'O';
        }
    }
}