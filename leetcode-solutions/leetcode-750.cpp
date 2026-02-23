/*
 * 750. Number Of Corner Rectangles
 *
 * Given a grid where each entry is only 0 or 1, find the number of corner rectangles.
 *
 * A corner rectangle is 4 distinct 1s on the grid that form an axis-aligned rectangle.
 * Note that only the corners need to have the value 1. Also, all four 1s used must be distinct.
 * 
 * Example 1:
 * 
 * Input: grid = 
 * [[1, 0, 0, 1, 0],
 *  [0, 0, 1, 0, 1],
 *  [0, 0, 0, 1, 0],
 *  [1, 0, 1, 0, 1]]
 * Output: 1
 * Explanation: There is only one corner rectangle, with corners grid[1][2], grid[1][4], grid[3][2], grid[3][4].
 * 
 * Note:
 * 1. The number of rows and columns of grid will each be in the range [1, 200].
 * 2. Each grid[i][j] will be either 0 or 1.
 * 3. The number of 1s in the grid will be at most 6000.
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    int countCornerRectangles(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        int ans = 0;
        
        // Iterate over all pairs of rows
        for (int i = 0; i < m; ++i) {
            for (int j = i + 1; j < m; ++j) {
                int count = 0;
                // Count columns where both rows have 1's
                for (int k = 0; k < n; ++k) {
                    if (grid[i][k] == 1 && grid[j][k] == 1) {
                        count++;
                    }
                }
                // If there are 'count' columns with 1's in both rows,
                // then number of rectangles using these two rows is C(count, 2)
                if (count >= 2) {
                    ans += count * (count - 1) / 2;
                }
            }
        }
        
        return ans;
    }
};