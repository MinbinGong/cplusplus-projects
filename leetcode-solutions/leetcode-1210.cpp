/**
 * 1210. Minimum Moves to Reach Target with Rotations
 *
 * In an n*n grid, there is a snake that spans 2 cells and starts moving from the top left corner at (0, 0) and (0, 1). The grid has empty cells represented by zeros and blocked cells represented by ones. The snake wants to reach the lower right corner at (n-1, n-2) and (n-1, n-1).
 *
 * In one move the snake can:
 *
 * Move one cell to the right if there are no blocked cells there. This move keeps the horizontal/vertical position of the snake as it is.
 * Move down one cell if there are no blocked cells there. This move keeps the horizontal/vertical position of the snake as it is.
 * Rotate clockwise if it's in a horizontal position and the two cells under it are both empty. In that case the snake moves from (r, c) and (r, c+1) to (r, c) and (r+1, c).
 * Rotate counterclockwise if it's in a vertical position and the two cells to its right are both empty. In that case the snake moves from (r, c) and (r+1, c) to (r, c) and (r, c+1).
 *
 * Return the minimum number of moves to reach the target.
 *
 * If there is no way to reach the target, return -1.
 *
 *
 *
 * Example 1:
 *
 * Input: grid = [[0,0,0,0,0,1],
 *                [1,1,0,0,1,0],
 *                [0,0,0,0,1,1],
 *                [0,0,1,0,1,0],
 *                [0,1,1,0,0,0],
 *                [0,1,1,0,0,0]]
 * Output: 11
 * Explanation:
 * One possible solution is [right, right, rotate clockwise, right, down, down, down, down, rotate counterclockwise, right, down].
 *
 * Example 2:
 *
 * Input: grid = [[0,0,1,1,1,1],
 *                [0,0,0,0,1,1],
 *                [1,1,0,0,0,1],
 *                [1,1,1,0,0,1],
 *                [1,1,1,0,0,1],
 *                [1,1,1,0,0,0]]
 * Output: 9
 * Explanation:
 * One possible solution is [right, right, rotate clockwise, right, down, down, rotate counterclockwise, right, down].
 * 
 * Note:
 *
 * 2 <= n <= 100
 * 0 <= grid[i][j] <= 1
 * It is guaranteed that the snake starts at empty cells.
 *
 */
#include <vector>
#include <queue>
#include <tuple>

class Solution {
public:
    int minimumMoves(std::vector<std::vector<int>>& grid) {
        int n = grid.size();
        
        // 状态：蛇尾位置 (tailX, tailY) 和方向 (horizontal = 0, vertical = 1)
        // visited[tailX][tailY][orientation]
        std::vector<std::vector<std::vector<bool>>> visited(
            n, std::vector<std::vector<bool>>(n, std::vector<bool>(2, false)));
        
        std::queue<std::tuple<int, int, int, int>> q; // (tailX, tailY, orientation, steps)
        q.push({0, 0, 0, 0}); // 初始状态：水平，蛇尾在(0,0)，蛇头在(0,1)
        visited[0][0][0] = true;
        
        while (!q.empty()) {
            auto [x, y, dir, steps] = q.front();
            q.pop();
            
            // 到达目标状态：蛇尾在(n-1, n-2)，水平方向
            if (x == n-1 && y == n-2 && dir == 0) {
                return steps;
            }
            
            // 向右移动
            if (dir == 0) { // 水平
                // 检查蛇头右侧是否在边界内且不是障碍物
                if (y+2 < n && grid[x][y+2] == 0) {
                    if (!visited[x][y+1][dir]) {
                        visited[x][y+1][dir] = true;
                        q.push({x, y+1, dir, steps+1});
                    }
                }
            } else { // 垂直
                // 检查蛇尾和蛇头右侧是否在边界内且不是障碍物
                if (y+1 < n && grid[x][y+1] == 0 && grid[x+1][y+1] == 0) {
                    if (!visited[x][y+1][dir]) {
                        visited[x][y+1][dir] = true;
                        q.push({x, y+1, dir, steps+1});
                    }
                }
            }
            
            // 向下移动
            if (dir == 0) { // 水平
                // 检查蛇尾和蛇头下方是否在边界内且不是障碍物
                if (x+1 < n && grid[x+1][y] == 0 && grid[x+1][y+1] == 0) {
                    if (!visited[x+1][y][dir]) {
                        visited[x+1][y][dir] = true;
                        q.push({x+1, y, dir, steps+1});
                    }
                }
            } else { // 垂直
                // 检查蛇头下方是否在边界内且不是障碍物
                if (x+2 < n && grid[x+2][y] == 0) {
                    if (!visited[x+1][y][dir]) {
                        visited[x+1][y][dir] = true;
                        q.push({x+1, y, dir, steps+1});
                    }
                }
            }
            
            // 顺时针旋转（水平变垂直）
            if (dir == 0 && x+1 < n) {
                // 需要检查蛇头下方和蛇头右下方的单元格
                if (grid[x+1][y] == 0 && grid[x+1][y+1] == 0) {
                    if (!visited[x][y][1]) {
                        visited[x][y][1] = true;
                        q.push({x, y, 1, steps+1});
                    }
                }
            }
            
            // 逆时针旋转（垂直变水平）
            if (dir == 1 && y+1 < n) {
                // 需要检查蛇头右侧和蛇头右上方的单元格
                if (grid[x][y+1] == 0 && grid[x+1][y+1] == 0) {
                    if (!visited[x][y][0]) {
                        visited[x][y][0] = true;
                        q.push({x, y, 0, steps+1});
                    }
                }
            }
        }
        
        return -1;
    }
};