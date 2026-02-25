/*
 * 959. Regions Cut By Slashes
 *
 * An n x n grid is composed of 1 x 1 squares where each 1 x 1 square consists of a '/', '\', or blank space ' '. These characters divide the square into contiguous regions.
 *
 * Given the grid grid represented as a string array, return the number of regions.
 *
 * Note that backslash characters are escaped, so a '\' is represented as '\\'.
 *
 * Example 1:
 *
 * Input: grid = [" /","/ "]
 * Output: 2
 * 
 * Example 2:
 *
 * Input: grid = [" /","  "]
 * Output: 1
 * 
 * Example 3:
 *
 * Input: grid = ["/\\","\\/"]
 * Output: 5
 * Explanation: Recall that because \ characters are escaped, "\\/" refers to \/, and "/\\" refers to /\.
 * 
 * Note:
 *
 * n == grid.length == grid[i].length
 * 1 <= n <= 30
 * grid[i][j] is either '/', '\', or ' '.
 * 
 */
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    int regionsBySlashes(vector<string>& grid) {
        int n = grid.size();
        // 将每个单元格放大为 3x3 的网格
        vector<vector<int>> g(3 * n, vector<int>(3 * n, 0));

        // 根据斜线方向填充障碍物
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == '/') {
                    // 左上到右下对角线
                    g[3 * i][3 * j + 2] = 1;
                    g[3 * i + 1][3 * j + 1] = 1;
                    g[3 * i + 2][3 * j] = 1;
                } else if (grid[i][j] == '\\') {
                    // 右上到左下对角线
                    g[3 * i][3 * j] = 1;
                    g[3 * i + 1][3 * j + 1] = 1;
                    g[3 * i + 2][3 * j + 2] = 1;
                }
                // 空格保持为 0
            }
        }

        // DFS 统计连通区域数量
        int ans = 0;
        int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        function<void(int, int)> dfs = [&](int x, int y) {
            g[x][y] = 2; // 标记已访问
            for (auto& d : dirs) {
                int nx = x + d[0], ny = y + d[1];
                if (nx >= 0 && nx < 3 * n && ny >= 0 && ny < 3 * n && g[nx][ny] == 0) {
                    dfs(nx, ny);
                }
            }
        };

        for (int i = 0; i < 3 * n; ++i) {
            for (int j = 0; j < 3 * n; ++j) {
                if (g[i][j] == 0) {
                    ++ans;
                    dfs(i, j);
                }
            }
        }
        return ans;
    }
};