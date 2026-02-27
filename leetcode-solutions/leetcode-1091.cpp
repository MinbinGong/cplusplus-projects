/*
 * 1091. Shortest Path in Binary Matrix
 *
 * In an N by N square grid, each cell is either empty (0) or blocked (1).
 * A clear path from top-left to bottom-right has length k if and only if it is composed of cells C_1, C_2, ..., C_k such that:
 * Adjacent cells C_i and C_{i+1} are connected 8-directionally (ie., they are different and share an edge or corner)
 * C_1 is at location (0, 0) (ie. has value grid[0][0])
 * C_k is at location (N-1, N-1) (ie. has value grid[N-1][N-1])
 * If C_i is located at (r, c), then grid[r][c] is empty (ie. grid[r][c] == 0).
 * Return the length of the shortest such clear path from top-left to bottom-right.  If such a path does not exist, return -1.
 * 
 * Example 1:
 * Input: [[0,1],[1,0]]
 * Output: 2
 * 
 * Example 2:
 * Input: [[0,0,0],[1,1,0],[1,1,0]]
 * Output: 4
 * 
 * Note:
 * 1 <= grid.length == grid[0].length <= 100
 * grid[r][c] is 0 or 1
 * 
 */
#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        int n = grid.size();
        // 如果起点或终点被阻塞，直接返回 -1
        if (grid[0][0] == 1 || grid[n-1][n-1] == 1) return -1;
        // 只有一个单元格且为 0
        if (n == 1) return 1;

        // 距离矩阵，同时用作 visited 标记（-1 表示未访问）
        vector<vector<int>> dist(n, vector<int>(n, -1));
        queue<pair<int, int>> q;
        dist[0][0] = 1;
        q.push({0, 0});

        // 八个方向
        int dirs[8][2] = {{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};

        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();
            for (auto& d : dirs) {
                int nx = x + d[0], ny = y + d[1];
                // 检查边界、是否可走、是否未访问
                if (nx >= 0 && nx < n && ny >= 0 && ny < n && grid[nx][ny] == 0 && dist[nx][ny] == -1) {
                    dist[nx][ny] = dist[x][y] + 1;
                    // 如果到达终点，立即返回
                    if (nx == n-1 && ny == n-1) return dist[nx][ny];
                    q.push({nx, ny});
                }
            }
        }
        // 队列为空仍未到达终点
        return -1;
    }
};
