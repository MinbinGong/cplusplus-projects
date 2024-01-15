#include <algorithm>
#include <queue>
#include <utility>
#include <vector>

void bfs(std::vector<std::vector<char>>& board, int i, int j) {
  typedef std::pair<int, int> state_t;

  std::queue<state_t> q;
  const int m = board.size();
  const int n = board[0].size();

  auto state_is_valid = [&](const state_t& s) {
    const int x = s.first;
    const int y = s.second;
    if (x < 0 || x >= m || y < 0 || y >= n || board[x][y] != 'o') {
      return false;
    }

    return true;
  };

  auto state_extend = [&](const state_t& s) {
    std::vector<state_t> result;
    const int x = s.first;
    const int y = s.second;

    const state_t new_states[4] = {{x - 1, y}, {x + 1, y}, {x, y - 1}, {x, y + 1}};

    for (int k = 0; k < 4; k++) {
      if (state_is_valid(new_states[k])) {
        board[new_states[k].first][new_states[k].second] = '+';
        result.push_back(new_states[k]);
      }
    }
    return result;
  };

  state_t start = {i, j};
  if (state_is_valid(start)) {
    board[i][j] = '+';
    q.push(start);
  }

  while (!q.empty()) {
    auto cur = q.front();
    q.pop();
    auto new_states = state_extend(cur);
    for (auto s : new_states) {
      q.push(s);
    }
  }
}

void solve(std::vector<std::vector<char>>& board) {
  if (board.empty()) {
    return;
  }

  const int m = board.size();
  const int n = board[0].size();
  for (size_t i = 0; i < n; i++) {
    bfs(board, 0, i);
    bfs(board, m - 1, i);
  }

  for (size_t j = 1; j < m - 1; j++) {
    bfs(board, j, 0);
    bfs(board, j, n - 1);
  }

  for (size_t i = 0; i < m; i++) {
    for (size_t j = 0; j < n; j++) {
      if (board[i][j] == 'o') {
        board[i][j] = 'x';
      } else if (board[i][j] == '+') {
        board[i][j] = 'o';
      }
    }
  }
}