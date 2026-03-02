/*
 * 1351. Count Negative Numbers in a Sorted Matrix
 *
 * Given a m * n matrix grid which is sorted in non-increasing order both row-wise and column-wise. 
 * 
 * Return the number of negative numbers in grid.
 * 
 * Example 1:
 * Input: grid = [[4,3,2,-1],[3,2,1,-1],[1,1,-1,-2],[-1,-1,-2,-3]]
 * Output: 8
 * Explanation: There are 8 negatives number in the matrix.
 * 
 * Example 2:
 * Input: grid = [[3,2],[1,0]]
 * Output: 0
 * 
 * Note:
 * m == grid.length
 * n == grid[i].length
 * 1 <= m, n <= 100
 * -100 <= grid[i][j] <= 100
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    int countNegatives(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        int row = m - 1, col = 0;
        int count = 0;
        
        while (row >= 0 && col < n) {
            if (grid[row][col] < 0) {
                // All elements to the right in this row are also negative
                count += (n - col);
                row--; // move up
            } else {
                col++; // move right
            }
        }
        return count;
    }
};