/*
 * 1293. Shortest Path in a Grid with Obstacles Elimination
 * 
 * You are given an m x n integer matrix grid where each cell is either 0 (empty) or 1 (obstacle).
 * You can move up, down, left, or right from and to an empty cell in one step.
 * 
 * Return the minimum number of steps to walk from the upper left corner (0, 0) to the lower right corner (m - 1, n - 1)
 * given that you can eliminate at most k obstacles. If it is not possible to find such walk return -1.
 * 
 * Example 1:
 * Input: grid = [[0,0,0],[1,1,0],[0,0,0],[0,1,1],[0,0,0]], k = 1
 * Output: 6
 * Explanation: 
 * The shortest path without eliminating any obstacle is 10.
 * 
 * Example 2:
 * Input: grid = [[0,1,1],[1,1,1],[1,0,0]], k = 1
 * Output: -1
 * Explanation: 
 * We need to eliminate at least two obstacles to find such a walk.
 * 
 * Note:
 * 1. m == grid.length
 * 2. n == grid[i].length
 * 3. 1 <= m, n <= 40
 * 4. 1 <= k <= m * n
 * 5. grid[i][j] is either 0 or 1.
 * 6. grid[0][0] == grid[m - 1][n - 1] == 0
 * 
 */
#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    int shortestPath(vector<vector<int>>& grid, int k) {
        int m = grid.size(), n = grid[0].size();

        // 优化：如果 k 足够大，可以直接走曼哈顿距离路径
        if (k >= m + n - 3) {
            return m + n - 2;
        }

        // 方向数组：上、下、左、右
        int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        // 三维 visited 数组：visited[x][y][剩余消除次数]
        vector<vector<vector<bool>>> visited(m, vector<vector<bool>>(n, vector<bool>(k + 1, false)));
        queue<vector<int>> q;

        q.push({0, 0, k});  // 起点状态
        visited[0][0][k] = true;

        int steps = 0;

        while (!q.empty()) {
            int levelSize = q.size();
            for (int i = 0; i < levelSize; ++i) {
                auto cur = q.front();
                q.pop();
                int x = cur[0], y = cur[1], rest = cur[2];

                // 到达终点
                if (x == m - 1 && y == n - 1) {
                    return steps;
                }

                for (auto& d : dirs) {
                    int nx = x + d[0], ny = y + d[1];
                    if (nx < 0 || nx >= m || ny < 0 || ny >= n) continue;

                    int newRest = rest;
                    if (grid[nx][ny] == 1) {
                        if (rest == 0) continue;   // 无消除机会，不能走障碍
                        newRest = rest - 1;
                    }

                    if (!visited[nx][ny][newRest]) {
                        visited[nx][ny][newRest] = true;
                        q.push({nx, ny, newRest});
                    }
                }
            }
            steps++; // 每层步数加一
        }

        return -1; // 无法到达
    }
};