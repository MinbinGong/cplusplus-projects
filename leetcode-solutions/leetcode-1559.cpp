/**
 * 1559. Detect Cycles in 2D Grid
 * 
 * Given a 2D array of characters grid of size m x n, you need to find if there exists any cycle consisting of the same value in grid.
 * 
 * A cycle is a path of length 4 or more in the grid that starts and ends at the same cell. From a given cell, you can move to one of the cells adjacent to it - in one of the four directions (up, down, left, or right), if it has the same value of the current cell.
 * 
 * Also, you cannot move to the cell that you visited in your last move. For example, the cycle (1, 1) -> (1, 2) -> (1, 1) is invalid because from (1, 2) we visited (1, 1) which was the last visited cell.
 * 
 * Return true if any cycle of the same value exists in grid, otherwise, return false.
 * 
 * Example 1:
 * Input: grid = [["a","a","a","a"],["a","b","b","a"],["a","b","b","a"],["a","a","a","a"]]
 * Output: true
 * Explanation: There are two valid cycles shown in different colors in the image below:
 * 
 * Example 2:
 * Input: grid = [["c","c","c","a"],["c","d","c","c"],["c","c","e","c"],["f","c","c","c"]]
 * Output: true
 * Explanation: There is only one valid cycle highlighted in the image below:
 * 
 * Constraints:
 * m == grid.length
 * n == grid[i].length
 * 1 <= m <= 500
 * 1 <= n <= 500
 * grid consists only of lowercase English letters.
 * 
 */
#include <vector>
#include <functional>
using namespace std;

class Solution1 {
public:
    bool containsCycle(vector<vector<char>>& grid) {
        int m = grid.size(), n = grid[0].size();
        // 访问标记数组
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        // 方向数组：上，右，下，左
        int dirs[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

        // 辅助 DFS 函数，使用 lambda 表达式以便捕获外部变量
        function<bool(int, int, int, int)> dfs = [&](int x, int y, int px, int py) -> bool {
            visited[x][y] = true;
            for (int k = 0; k < 4; ++k) {
                int nx = x + dirs[k][0];
                int ny = y + dirs[k][1];
                // 检查边界和字符是否相同
                if (nx >= 0 && nx < m && ny >= 0 && ny < n && grid[nx][ny] == grid[x][y]) {
                    // 如果不是父节点
                    if (!(nx == px && ny == py)) {
                        // 如果下一个节点已被访问，说明找到了环
                        if (visited[nx][ny]) {
                            return true;
                        }
                        // 否则递归搜索
                        if (dfs(nx, ny, x, y)) {
                            return true;
                        }
                    }
                }
            }
            return false;
        };

        // 遍历每个未被访问的单元格作为起点
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (!visited[i][j]) {
                    if (dfs(i, j, -1, -1)) {
                        return true;
                    }
                }
            }
        }
        return false;
    }
};

class Solution2 {
public:
    // 查找函数，带路径压缩
    int find(vector<int>& parent, int x) {
        if (parent[x] != x) {
            parent[x] = find(parent, parent[x]);
        }
        return parent[x];
    }

    bool containsCycle(vector<vector<char>>& grid) {
        int m = grid.size(), n = grid[0].size();
        // 初始化并查集，将二维坐标映射到一维： index = i * n + j
        vector<int> parent(m * n);
        for (int i = 0; i < m * n; ++i) {
            parent[i] = i;
        }

        // 只需要检查每个单元格的右边和下边，避免重复检查
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                // 检查右边的邻居 (i, j+1)
                if (j + 1 < n && grid[i][j] == grid[i][j + 1]) {
                    int a = i * n + j;
                    int b = i * n + (j + 1);
                    int pa = find(parent, a);
                    int pb = find(parent, b);
                    // 如果两个节点的根相同，说明存在环
                    if (pa == pb) {
                        return true;
                    }
                    // 否则合并
                    parent[pa] = pb;
                }
                // 检查下边的邻居 (i+1, j)
                if (i + 1 < m && grid[i][j] == grid[i + 1][j]) {
                    int a = i * n + j;
                    int b = (i + 1) * n + j;
                    int pa = find(parent, a);
                    int pb = find(parent, b);
                    if (pa == pb) {
                        return true;
                    }
                    parent[pa] = pb;
                }
            }
        }
        return false;
    }
};