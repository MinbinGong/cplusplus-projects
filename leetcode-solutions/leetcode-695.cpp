/*
  题目描述
      给定一个二维的 0-1 矩阵，其中 0 表示海洋，1 表示陆地。单独的或相邻的陆地可以形成岛
  屿，每个格子只与其上下左右四个格子相邻。求最大的岛屿面积。

  题解
      此题是十分标准的搜索题，我们可以拿来练手深度优先搜索。一般来说，深度优先搜索类型
  的题可以分为主函数和辅函数，主函数用于遍历所有的搜索位置，判断是否可以开始搜索，如果
  可以即在辅函数进行搜索。辅函数则负责深度优先搜索的递归调用。
 */
#include <stack>
#include <utility>
#include <vector>
using namespace std;

const vector<int> direction{-1, 0, 1, 0, -1};

int maxAreaOfIsland(vector<vector<int>> &grid) {
    int m = grid.size(), n = m == 0 ? 0 : grid[0].size();
    int area = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 0) {
                continue;
            }

            int local_area = 1;
            grid[i][j] = 0;
            stack<pair<int, int>> island;
            island.push({i, j});
            while (!island.empty()) {
                auto [r, c] = island.top();
                island.pop();
                for (int k = 0; k < 4; k++) {
                    int x = r + direction[k], y = c + direction[k + 1];
                    if (x >= 0 && x < m && y >= 0 && y < n && grid[x][y] == 1) {
                        grid[x][y] = 0;
                        ++local_area;
                        island.push({x, y});
                    }
                }
            }
            area = max(area, local_area);
        }
    }

    return area;
}

int dfs1(vector<vector<int>> &grid, int r, int c) {
    if (grid[r][c] == 0) {
        return 0;
    }

    grid[r][c] = 0;
    int area = 1;
    for (int i = 0; i < 4; ++i) {
        int x = r + direction[i], y = c + direction[i + 1];
        if (x >= 0 && x < m && y >= 0 && y < n && grid[x][y] == 1) {
            area += dfs(grid, x, y);
        }
    }
    return area;
}

int maxAreaOfIsland1(vector<vector<int>> &grid) {
    if (grid.empty() || grid[0].empty()) {
        return 0;
    }

    int max_area = 0;
    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[0].size(); ++j) {
            if (grid[i][j] == 1) {
                max_area = max(max_area, dfs1(grid, i, j));
            }
        }
    }
    return max_area;
}

int dfs2(vector<vector<int>> &grid, int r, int c) {
    if (r < 0 || r >= grid.size() || c < 0 || c >= grid[0].size() || grid[r][c] == 0) {
        return 0;
    }
    grid[r][c] = 0;
    return 1 + dfs2(grid, r + 1, c) + dfs2(grid, r - 1, c) + dfs2(grid, r, c + 1) + dfs2(grid, r, c - 1);
}

int maxAreaOfIsland2(vector<vector<int>> &grid) {
    if (grid.empty() || grid[0].empty()) {
        return 0;
    }
    int max_area = 0;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            max_area = max(max_area, dfs2(grid, i, j));
        }
    }
    return max_area;
}