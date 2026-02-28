/**
 * 1263. Minimum Moves to Move a Box to Their Target Location
 * 
 * A storekeeper is a game in which the player pushes boxes around in a warehouse trying to get them to target locations.
 * 
 * The game is represented by a grid of size n * m, where each element is a wall, floor, or a box.
 * 
 * Your task is move the box 'B' to the target position 'T' under the following rules:
 * 
 * The character 'S' represents the player. The player can move up, down, left, right in the grid if it is a floor (empy cell).
 * The character '.' represents the floor which means a free cell to walk.
 * The character '#' represents the wall which means an obstacle (impossible to walk there).
 * There is only one box 'B' and one target cell 'T' in the grid.
 * 
 * Example 1:
 * Input: grid = [["#","#","#","#","#","#"],
 *                ["#","T","#","#","#","#"],
 *                ["#",".",".","B",".","#"],
 *                ["#",".","#","#",".","#"],
 *                ["#",".",".",".","S","#"],
 *                ["#","#","#","#","#","#"]]
 * Output: 3
 * Explanation: We return only the number of times the box is pushed.
 * 
 * Example 2:
 * Input: grid = [["#","#","#","#","#","#"],
 *                ["#","T","#","#","#","#"],
 *                ["#",".",".","B",".","#"],
 *                ["#","#","#","#",".","#"],
 *                ["#",".",".",".","S","#"],
 *                ["#","#","#","#","#","#"]]
 * Output: -1
 * Explanation: We cannot move the box.
 * 
 * Example 3:
 * Input: grid = [["#","#","#","#","#","#"],
 *                ["#","T",".",".","#","#"],
 *                ["#",".","#","B",".","#"],
 *                ["#",".",".",".",".","#"],
 *                ["#",".",".",".","S","#"],
 *                ["#","#","#","#","#","#"]]
 * Output: 5
 * Explanation:  push the box down, left, left, up and up.
 * 
 * Note:
 * 1 <= grid.length <= 20
 * 1 <= grid[i].length <= 20
 * grid contains only characters '.', '#', 'S', 'T', or 'B'.
 * There is only one character 'S', 'B' and 'T' in the grid.
 * 
 */
#include <vector>
#include <deque>
#include <cstring>

using namespace std;

class Solution {
public:
    int minPushBox(vector<vector<char>>& grid) {
        int m = grid.size(), n = grid[0].size();
        // 方向数组：上下左右
        int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        
        // 记录初始位置
        int si, sj, bi, bj, ti, tj;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 'S') {
                    si = i; sj = j;
                    grid[i][j] = '.'; // 将起点标记为可走
                } else if (grid[i][j] == 'B') {
                    bi = i; bj = j;
                    grid[i][j] = '.';
                } else if (grid[i][j] == 'T') {
                    ti = i; tj = j;
                    grid[i][j] = '.';
                }
            }
        }

        // visited[箱子的x][箱子的y][人的x][人的y]
        bool visited[21][21][21][21];
        memset(visited, 0, sizeof(visited));
        
        // 双端队列，元素为 (箱子x, 箱子y, 人x, 人y)
        deque<tuple<int, int, int, int>> dq;
        dq.push_back({bi, bj, si, sj});
        visited[bi][bj][si][sj] = true;
        
        // 检查坐标是否合法（不越界且不是墙）
        auto isValid = [&](int x, int y) -> bool {
            return x >= 0 && x < m && y >= 0 && y < n && grid[x][y] != '#';
        };
        
        int pushes = 0; // 当前层推动次数
        while (!dq.empty()) {
            int size = dq.size();
            while (size--) {
                auto [bx, by, px, py] = dq.front();
                dq.pop_front();
                
                // 箱子到达目标
                if (bx == ti && by == tj) return pushes;
                
                // 尝试四个方向推动箱子
                for (int d = 0; d < 4; ++d) {
                    int nbx = bx + dirs[d][0]; // 箱子新位置
                    int nby = by + dirs[d][1];
                    int npx = bx - dirs[d][0]; // 人应该站的位置（推动前的位置）
                    int npy = by - dirs[d][1];
                    
                    // 检查箱子新位置和人的目标位置是否合法
                    if (!isValid(nbx, nby) || !isValid(npx, npy)) continue;
                    
                    // 检查人能否从当前位置 (px, py) 走到 (npx, npy)（BFS 检查）
                    if (!canReach(px, py, npx, npy, bx, by, grid)) continue;
                    
                    // 如果新状态未访问
                    if (!visited[nbx][nby][npx][npy]) {
                        visited[nbx][nby][npx][npy] = true;
                        // 推动一次，代价为1，放入队尾
                        dq.push_back({nbx, nby, npx, npy});
                    }
                }
            }
            pushes++; // 完成一层 BFS，推动次数+1
        }
        return -1;
    }

private:
    // 判断人能否从 start 走到 target，不能经过箱子位置 box
    bool canReach(int sx, int sy, int tx, int ty, int boxX, int boxY, vector<vector<char>>& grid) {
        if (sx == tx && sy == ty) return true;
        
        int m = grid.size(), n = grid[0].size();
        bool vis[21][21];
        memset(vis, 0, sizeof(vis));
        int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        
        deque<pair<int, int>> dq;
        dq.push_back({sx, sy});
        vis[sx][sy] = true;
        
        while (!dq.empty()) {
            auto [x, y] = dq.front();
            dq.pop_front();
            if (x == tx && y == ty) return true;
            
            for (int d = 0; d < 4; ++d) {
                int nx = x + dirs[d][0];
                int ny = y + dirs[d][1];
                if (nx < 0 || nx >= m || ny < 0 || ny >= n) continue;
                if (vis[nx][ny]) continue;
                if (grid[nx][ny] == '#') continue;
                if (nx == boxX && ny == boxY) continue; // 不能穿过箱子
                vis[nx][ny] = true;
                dq.push_back({nx, ny});
            }
        }
        return false;
    }
};