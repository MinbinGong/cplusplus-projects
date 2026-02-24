/*
 * 840. Magic Squares In Grid
 * 
 * A 3 x 3 magic square is a 3 x 3 grid filled with distinct numbers from 1 to 9 such that each row, column, and both diagonals all have the same sum.
 * 
 * Given a row x col grid of integers, how many 3 x 3 "magic square" subgrids are there?  (Each subgrid is contiguous).
 * 
 * Example 1:
 * Input: grid = [[4,3,8,4],[9,5,1,9],[2,7,6,2]]
 * Output: 1
 * 
 * Example 2:
 * Input: grid = [[8]]
 * Output: 0
 * 
 * Note:
 * 1 <= row, col <= 10
 * 0 <= grid[i][j] <= 15
 * 
 */
#include <vector>
#include <cstring> // for memset

class Solution1 {
public:
    int numMagicSquaresInside(std::vector<std::vector<int>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();
        int ans = 0;

        // 遍历所有可能的 3x3 子矩阵的左上角顶点
        for (int i = 0; i <= rows - 3; ++i) {
            for (int j = 0; j <= cols - 3; ++j) {
                if (isMagicSquare(grid, i, j)) {
                    ans++;
                }
            }
        }
        return ans;
    }

private:
    bool isMagicSquare(const std::vector<std::vector<int>>& grid, int x, int y) {
        // 1. 快速检查：中心必须是 5
        if (grid[x + 1][y + 1] != 5) return false;

        // 2. 检查数字是否在 1-9 之间且不重复
        bool seen[10] = {false}; // 索引 0-9，记录数字是否出现过
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                int num = grid[x + i][y + j];
                if (num < 1 || num > 9) return false; // 超出范围
                if (seen[num]) return false;          // 出现重复
                seen[num] = true;
            }
        }

        // 3. 检查每一行、每一列、两条对角线的和是否为 15
        // 检查行
        for (int i = 0; i < 3; ++i) {
            if (grid[x + i][y] + grid[x + i][y + 1] + grid[x + i][y + 2] != 15) return false;
        }
        // 检查列
        for (int j = 0; j < 3; ++j) {
            if (grid[x][y + j] + grid[x + 1][y + j] + grid[x + 2][y + j] != 15) return false;
        }
        // 检查主对角线 (\)
        if (grid[x][y] + grid[x + 1][y + 1] + grid[x + 2][y + 2] != 15) return false;
        // 检查副对角线 (/)
        if (grid[x][y + 2] + grid[x + 1][y + 1] + grid[x + 2][y] != 15) return false;

        return true;
    }
};

class Solution2 {
public:
    int numMagicSquaresInside(std::vector<std::vector<int>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();
        int ans = 0;

        for (int i = 0; i <= rows - 3; ++i) {
            for (int j = 0; j <= cols - 3; ++j) {
                // 1. 快速检查：中心必须是 5
                if (grid[i + 1][j + 1] != 5) continue;

                // 2. 使用位掩码检查数字是否在1-9且不重复
                int mask = 0;
                int row_sum[3] = {0, 0, 0};
                int col_sum[3] = {0, 0, 0};

                // 遍历 3x3 矩阵
                for (int r = 0; r < 3; ++r) {
                    for (int c = 0; c < 3; ++c) {
                        int val = grid[i + r][j + c];
                        // 检查范围并更新位掩码 (将第 val 位置为 1)
                        mask |= 1 << val;
                        row_sum[r] += val;
                        col_sum[c] += val;
                    }
                }

                // 3. 最终验证
                // mask == (1 << 10) - 2 表示第1到9位都是1，第0位是0，即包含了1-9各一次
                if (mask == (1 << 10) - 2 &&
                    row_sum[0] == 15 && row_sum[1] == 15 &&
                    col_sum[0] == 15 && col_sum[1] == 15) {
                    // 注意：这里只检查了前两行和前两列。根据幻方的性质，如果前两行和前两列和为15，
                    // 且包含了1-9，那么剩余的行、列和对角线也必然是15[citation:1]。
                    ans++;
                }
            }
        }
        return ans;
    }
};