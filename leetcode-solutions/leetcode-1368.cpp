/**
 * 1368. Minimum Cost to Make at Least One Valid Path in a Grid
 *
 * Given a m x n grid. Each cell of the grid has a sign pointing to the next cell you should visit if you are currently in this cell. The sign of grid[i][j] can be:
 * 1 which means go to the cell to the right. (i.e go from grid[i][j] to grid[i][j + 1])
 * 2 which means go to the cell to the left. (i.e go from grid[i][j] to grid[i][j - 1])
 * 3 which means go to the lower cell. (i.e go from grid[i][j] to grid[i + 1][j])
 * 4 which means go to the upper cell. (i.e go from grid[i][j] to grid[i - 1][j])
 * Notice that there could be some invalid signs on the cells of the grid which points outside the grid.
 *
 * Example 1:
 * Input: grid = [[1,1,1,1],[2,2,2,2],[1,1,1,1],[2,2,2,2]]
 * Output: 3
 * Explanation: You will start at cell (0, 0).
 * Moving to (0, 1) or (0, 2) will cost 1.
 * Moving to (1, 2) or (2, 2) will cost 2.
 * Moving to (2, 1) or (2, 0) will cost 1.
 * Moving to (3, 2) or (3, 1) will cost 2.
 * So the total cost will be 3.
 * 
 * Example 2:
 * Input: grid = [[1,2,3],[4,5,6]]
 * Output: 2
 * Explanation: You will start at cell (0, 0).
 * Moving to (0, 1) will cost 1.
 * Moving to (1, 2) will cost 2.
 * Moving to (1, 1) will cost 1.
 * So the total cost will be 2.
 * 
 * Note:
 * The number of nodes in the tree will be in the range [1, 2500].
 * The number of nodes in the list will be in the range [1, 100].
 * 1 <= Node.val <= 100 for each node in the linked list and binary tree.
 * 
 */
#include <vector>
#include <string>
#include <algorithm>
#include <deque>
using namespace std;

class Solution {
public:
    int minCost(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        // 方向映射：1右，2左，3下，4上
        int dirs[5][2] = {{0,0}, {0,1}, {0,-1}, {1,0}, {-1,0}};
        vector<vector<int>> cost(m, vector<int>(n, INT_MAX));
        deque<pair<int,int>> dq;
        dq.push_front({0,0});
        cost[0][0] = 0;

        while (!dq.empty()) {
            auto [x, y] = dq.front();
            dq.pop_front();
            for (int d = 1; d <= 4; ++d) {
                int nx = x + dirs[d][0];
                int ny = y + dirs[d][1];
                if (nx < 0 || nx >= m || ny < 0 || ny >= n) continue;
                int newCost = cost[x][y] + (grid[x][y] == d ? 0 : 1);
                if (newCost < cost[nx][ny]) {
                    cost[nx][ny] = newCost;
                    if (grid[x][y] == d) {
                        dq.push_front({nx, ny}); // 不改变方向，优先扩展
                    } else {
                        dq.push_back({nx, ny});  // 改变方向，后扩展
                    }
                }
            }
        }
        return cost[m-1][n-1];
    }
};