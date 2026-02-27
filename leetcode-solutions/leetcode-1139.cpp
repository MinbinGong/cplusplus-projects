/**
 * 1139. Largest 1-Bordered Square
 * Medium
 * 
 * (This problem is an interactive problem.)
 * 
 * Given a 2D grid of 0s and 1s, return the number of elements in the largest square subgrid that has all 1s on its border, or 0 if such a subgrid doesn't exist in the grid.
 * 
 * Example 1:
 * Input: grid = [[1,1,1],[1,0,1],[1,1,1]]
 * Output: 9
 * 
 * Example 2:
 * Input: grid = [[1,1,0,0]]
 * Output: 1
 * 
 * Note:
 * 1 <= grid.length <= 100
 * 1 <= grid[0].length <= 100
 * grid[i][j] is 0 or 1
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    int largest1BorderedSquare(vector<vector<int>>& grid) {
        int m = grid.size();
        if (m == 0) return 0;
        int n = grid[0].size();

        // 预处理向右和向下的连续1个数
        vector<vector<int>> right(m, vector<int>(n, 0));
        vector<vector<int>> down(m, vector<int>(n, 0));

        for (int i = 0; i < m; ++i) {
            for (int j = n - 1; j >= 0; --j) {
                if (grid[i][j] == 1) {
                    right[i][j] = (j + 1 < n) ? right[i][j + 1] + 1 : 1;
                }
            }
        }

        for (int j = 0; j < n; ++j) {
            for (int i = m - 1; i >= 0; --i) {
                if (grid[i][j] == 1) {
                    down[i][j] = (i + 1 < m) ? down[i + 1][j] + 1 : 1;
                }
            }
        }

        int maxLen = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 0) continue;
                // 以(i,j)为左上角可能的最大边长
                int maxPossible = min(right[i][j], down[i][j]);
                for (int L = maxPossible; L > maxLen; --L) {
                    // 检查下边界和右边界是否满足条件
                    if (down[i][j + L - 1] >= L && right[i + L - 1][j] >= L) {
                        maxLen = L;
                        break;  // 因为从大到小，第一个找到的就是当前左上角的最大可能
                    }
                }
            }
        }
        return maxLen * maxLen;
    }
};