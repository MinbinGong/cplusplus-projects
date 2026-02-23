/*
 * 764. Largest Plus Sign
 *
 * In a 2D grid from (0, 0) to (N-1, N-1), every cell contains a 1, except those cells in the given list mines which are 0. What is the largest axis-aligned plus sign of 1s contained in the grid? Return the order of the plus sign. If there is none, return 0.
 * 
 * Example 1:
 * Input: N = 5, mines = [[4, 2]]
 * Output: 2
 * Explanation:
 * 11111
 * 11111
 * 11111
 * 11111
 * 11011
 * In the above grid, the largest plus sign can only be order 2.  One of them is marked in bold.
 * 
 * Note:
 * 1. N will be an integer in the range [1, 500].
 * 2. mines will have length in range [0, 5000].
 * 3. mines[i] will be length 2 and consist of integers in the range [0, N-1].
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int orderOfLargestPlusSign(int n, vector<vector<int>>& mines) {
        // Initialize grid with all 1's
        vector<vector<int>> grid(n, vector<int>(n, 1));
        for (auto& m : mines) {
            grid[m[0]][m[1]] = 0;
        }

        // left[i][j]: consecutive 1's to the left of (i,j) including itself
        vector<vector<int>> left(n, vector<int>(n, 0));
        vector<vector<int>> right(n, vector<int>(n, 0));
        vector<vector<int>> up(n, vector<int>(n, 0));
        vector<vector<int>> down(n, vector<int>(n, 0));

        // Compute left and up in one pass
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 0) {
                    left[i][j] = up[i][j] = 0;
                } else {
                    left[i][j] = 1 + (j > 0 ? left[i][j - 1] : 0);
                    up[i][j]   = 1 + (i > 0 ? up[i - 1][j] : 0);
                }
            }
        }

        // Compute right and down in reverse pass
        for (int i = n - 1; i >= 0; --i) {
            for (int j = n - 1; j >= 0; --j) {
                if (grid[i][j] == 0) {
                    right[i][j] = down[i][j] = 0;
                } else {
                    right[i][j] = 1 + (j < n - 1 ? right[i][j + 1] : 0);
                    down[i][j]  = 1 + (i < n - 1 ? down[i + 1][j] : 0);
                }
            }
        }

        int ans = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                int arm = min({left[i][j], right[i][j], up[i][j], down[i][j]});
                ans = max(ans, arm);
            }
        }
        return ans;
    }
};