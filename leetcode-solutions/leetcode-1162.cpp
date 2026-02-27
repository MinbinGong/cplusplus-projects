/**
 * 1162. As Far from Land as Possible
 * Medium
 * 
 * (This problem is an interactive problem.)
 * 
 * Given an N x N grid containing only values 0 and 1, where 0 represents water and 1 represents land, find a water cell such that its distance to the nearest land cell is maximized and return the distance.
 * 
 * The distance used in this problem is the Manhattan distance: the distance between two cells (x0, y0) and (x1, y1) is |x0 - x1| + |y0 - y1|.
 * 
 * If no land or water exists in the grid, return -1.
 * 
 * Example 1:
 * Input: [[1,0,1],[0,0,0],[1,0,1]]
 * Output: 2
 * Explanation: 
 * The cell (1, 1) is as far as possible from all the land with distance 2.
 * 
 * Example 2:
 * Input: [[1,0,0],[0,0,0],[0,0,0]]
 * Output: 4
 * Explanation: 
 * The cell (2, 2) is as far as possible from all the land with distance 4.
 * 
 * Note:
 * 1 <= grid.length == grid[0].length <= 100
 * grid[i][j] is 0 or 1
 * 
 */
#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    int maxDistance(vector<vector<int>>& grid) {
        int n = grid.size();
        queue<pair<int, int>> q;
        // 将所有陆地入队，并标记距离为0
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 1) {
                    q.push({i, j});
                }
            }
        }
        // 如果没有陆地或者全是陆地，返回-1
        if (q.empty() || q.size() == n * n) return -1;

        int dirs[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
        int ans = 0;
        while (!q.empty()) {
            auto [x, y] = q.front(); q.pop();
            for (auto& d : dirs) {
                int nx = x + d[0], ny = y + d[1];
                if (nx >= 0 && nx < n && ny >= 0 && ny < n && grid[nx][ny] == 0) {
                    // 海洋格子第一次被访问时的距离就是最近陆地的距离
                    grid[nx][ny] = grid[x][y] + 1; // 直接复用原数组记录距离
                    ans = max(ans, grid[nx][ny] - 1); // 注意起点陆地值为1，所以距离要减1
                    q.push({nx, ny});
                }
            }
        }
        return ans;
    }
};