/**
 * 885. Spiral Matrix III
 *
 * You start at the cell (rStart, cStart) of an rows x cols grid facing east. The northwest corner is at the first row and column in the grid, and the southeast corner is at the last row and column.
 * You will walk in a clockwise spiral shape to visit every position in this grid. Whenever you move outside the grid's boundary, we continue our walk outside the grid (but may return to the grid boundary later.). Eventually, we reach all rows * cols spaces of the grid.
 * Return an array of coordinates representing the positions of the grid in the order you visited them.
 *
 * Example 1:
 * Input: rows = 1, cols = 4, rStart = 0, cStart = 0
 * Output: [[0,0],[0,1],[0,2],[0,3]]
 *
 * Example 2:
 * Input: rows = 5, cols = 6, rStart = 1, cStart = 4
 * Output: [[1,4],[1,5],[2,5],[2,4],[2,3],[1,3],[0,3],[0,4],[0,5],[3,5],[3,4],[3,3],[3,2],[2,2],[1,2],[0,2],[4,5],[4,4],[4,3],[4,2],[4,1],[3,1],[2,1],[1,1],[0,1],[4,0],[3,0],[2,0],[1,0],[0,0]]
 *
 * Note:
 * 1 <= rows <= 100
 * 1 <= cols <= 100
 * 0 <= rStart < rows
 * 0 <= cStart < cols
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> spiralMatrixIII(int R, int C, int r0, int c0) {
        vector<vector<int>> res;
        int total = R * C;
        int step = 1;          // 当前步长
        int dir = 0;           // 方向: 0东,1南,2西,3北
        int r = r0, c = c0;
        vector<vector<int>> dirs = {{0,1}, {1,0}, {0,-1}, {-1,0}};
        res.push_back({r, c});
        
        while (res.size() < total) {
            for (int i = 0; i < 2; ++i) {          // 每两个方向步长相同
                for (int s = 0; s < step; ++s) {
                    r += dirs[dir][0];
                    c += dirs[dir][1];
                    if (r >= 0 && r < R && c >= 0 && c < C) {
                        res.push_back({r, c});
                    }
                }
                dir = (dir + 1) % 4;                // 切换到下一个方向
            }
            step++;                                  // 步长增加
        }
        return res;
    }
};