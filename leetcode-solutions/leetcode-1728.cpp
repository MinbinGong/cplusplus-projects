/**
 * 1728. Cat and Mouse II
 * 
 * A game is played by a cat and a mouse named Cat and Mouse.
 * The environment is represented by a grid of size rows x cols, where each element is a wall, floor, player (Cat, Mouse), or food.
 * 
 * Players are represented by the characters 'C'(Cat),'M'(Mouse).
 * Floors are represented by the character '.' and can be walked on.
 * Walls are represented by the character '#' and cannot be walked on.
 * Food is represented by the character 'F' and can be walked on.
 * There is only one of each character 'C', 'M', and 'F' in grid.
 * 
 * Mouse and Cat play according to the following rules:
 * Mouse moves first, then they take turns to move.
 * During each turn, Cat and Mouse can jump in one of the four directions (left, right, up, down). They cannot jump over the wall nor outside of the grid.
 * catJump, mouseJump are the maximum lengths Cat and Mouse can jump at a time, respectively. Cat and Mouse can jump less than the maximum length.
 * 
 * Example 1:
 * Input: grid = ["####F","#C...","M...."], catJump = 1, mouseJump = 2
 * Output: true
 * Explanation: Cat cannot catch Mouse on its turn nor can it get the food before Mouse.
 * 
 * Example 2:
 * Input: grid = ["M.C...F"], catJump = 1, mouseJump = 4
 * Output: true
 * Explanation: Mouse can get the food "C.M...F" before Cat.
 * 
 * Example 3:
 * Input: grid = ["M.C...F"], catJump = 1, mouseJump = 3
 * Output: false
 * 
 * Constraints:
 * rows == grid.length
 * cols = grid[i].length
 * 1 <= rows, cols <= 8
 * grid[i][j] is either 'C', 'M', 'F', '.', or '#'.
 * There is only one of each character 'C', 'M', and 'F' in grid.
 * 1 <= catJump, mouseJump <= 8
 * 
 */
#include <vector>
#include <string>
#include <cstring>
using namespace std;

class Solution {
public:
    // dp[cx][cy][mx][my][step]：猫在(cx,cy)，鼠在(mx,my)，已走step步时的胜负状态
    // -1: 未计算, 0: 鼠胜, 1: 猫胜
    int dp[8][8][8][8][200];
    vector<string> grid;
    int n, m;                // 网格大小
    int catJump, mouseJump;  // 跳跃距离
    int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}}; // 四个方向

    bool canMouseWin(vector<string>& grid, int catJump, int mouseJump) {
        this->grid = grid;
        this->catJump = catJump;
        this->mouseJump = mouseJump;
        n = grid.size();
        m = grid[0].size();

        int cx, cy, mx, my, fx, fy;
        // 找到猫、老鼠、食物的初始位置
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 'C') {
                    cx = i; cy = j;
                } else if (grid[i][j] == 'M') {
                    mx = i; my = j;
                } else if (grid[i][j] == 'F') {
                    fx = i; fy = j;
                }
            }
        }

        memset(dp, -1, sizeof(dp));
        // 从初始状态开始，step = 0 表示老鼠先手
        return dfs(cx, cy, mx, my, 0) == 0; // 0 表示老鼠获胜
    }

    // 返回值：0 表示当前状态老鼠获胜，1 表示猫获胜
    int dfs(int cx, int cy, int mx, int my, int step) {
        // 边界条件：步数超过 200，猫赢（题目设定 1000，但状态压缩后 200 足够判断）
        if (step >= 200) return 1;

        // 检查是否已计算过
        int& res = dp[cx][cy][mx][my][step];
        if (res != -1) return res;

        // 胜负判定
        // 如果猫和老鼠在同一位置，猫赢
        if (cx == mx && cy == my) return res = 1;
        // 如果老鼠到达食物，老鼠赢
        if (mx == fx && my == fy) return res = 0;
        // 如果猫到达食物，猫赢
        if (cx == fx && cy == fy) return res = 1;

        // 根据步数奇偶性判断当前是谁的回合
        if (step % 2 == 0) { // 老鼠回合
            // 老鼠尝试所有可能的移动
            for (auto& d : dirs) {
                for (int j = 0; j <= mouseJump; j++) {
                    int nx = mx + d[0] * j;
                    int ny = my + d[1] * j;
                    // 检查是否越界或撞墙
                    if (nx < 0 || nx >= n || ny < 0 || ny >= m) break;
                    if (grid[nx][ny] == '#') break;
                    
                    // 如果老鼠能走到一个让猫必败的状态，则老鼠获胜
                    if (dfs(cx, cy, nx, ny, step + 1) == 0) {
                        return res = 0;
                    }
                }
            }
            // 所有走法都不能让老鼠获胜，则猫获胜
            return res = 1;
        } else { // 猫回合
            // 猫尝试所有可能的移动
            for (auto& d : dirs) {
                for (int j = 0; j <= catJump; j++) {
                    int nx = cx + d[0] * j;
                    int ny = cy + d[1] * j;
                    if (nx < 0 || nx >= n || ny < 0 || ny >= m) break;
                    if (grid[nx][ny] == '#') break;
                    
                    // 如果猫能走到一个让老鼠必败的状态，则猫获胜
                    if (dfs(nx, ny, mx, my, step + 1) == 1) {
                        return res = 1;
                    }
                }
            }
            // 所有走法都不能让猫获胜，则老鼠获胜
            return res = 0;
        }
    }
};
