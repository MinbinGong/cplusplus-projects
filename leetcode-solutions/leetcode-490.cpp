/*
 * The Maze
 *
 *  There is a ball in a maze with empty spaces (represented as 0) and walls (represented as 1). The ball can go through
 * the empty spaces by rolling up, down, left or right, but it won't stop rolling until hitting a wall. When the ball
 * stops, it could choose the next direction.
 *
 *  Given the m x n maze, the ball's start position and the destination, where start = [startrow, startcol] and
 * destination = [destinationrow, destinationcol], return true if the ball can stop at the destination, otherwise return
 * false.
 *
 *  You may assume that the borders of the maze are all walls (see examples).
 *
 *  Constraints:
 *  m == maze.length
 *  n == maze[i].length
 *  1 <= m, n <= 100
 *  maze[i][j] is 0 or 1.
 *  start.length == 2
 *  destination.length == 2
 *  0 <= startrow, destinationrow <= m
 *  0 <= startcol, destinationcol <= n
 *  Both the ball and the destination exist in an empty space, and they will not be in the same position initially.
 *  The maze contains at least 2 empty spaces.
 *
 */
#include <queue>
#include <vector>
using namespace std;

class Solution {
 public:
  bool hasPath(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
    int m = maze.size(), n = maze[0].size();
    vector<vector<bool>> visited(m, vector<bool>(n, false));
    queue<pair<int, int>> q;
    q.push({start[0], start[1]});
    visited[start[0]][start[1]] = true;

    vector<pair<int, int>> dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    while (!q.empty()) {
      auto [x, y] = q.front();
      q.pop();
      if (x == destination[0] && y == destination[1]) return true;

      for (auto [dx, dy] : dirs) {
        int nx = x, ny = y;
        // 沿当前方向滚动直到遇到墙或边界
        while (nx + dx >= 0 && nx + dx < m && ny + dy >= 0 && ny + dy < n && maze[nx + dx][ny + dy] == 0) {
          nx += dx;
          ny += dy;
        }
        // 此时 (nx, ny) 是停止的位置（墙的前一个格子）
        if (!visited[nx][ny]) {
          visited[nx][ny] = true;
          q.push({nx, ny});
        }
      }
    }
    return false;
  }
};