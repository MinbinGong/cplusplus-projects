/**
 * 1727. Largest Submatrix With Rearrangements
 * 
 * You are given a binary matrix matrix of size m x n, and you are allowed to rearrange the columns of the matrix in any order.
 * Return the area of the largest submatrix within matrix where every element of the submatrix is 1 after reordering the columns optimally.
 * 
 * Example 1:
 * Input: matrix = [[0,0,1],[1,1,1],[1,0,1]]
 * Output: 4
 * Explanation: You can rearrange the columns as shown above.
 * The largest submatrix of 1s, in bold, has an area of 4.
 * 
 * Example 2:
 * Input: matrix = [[1,0,1,0,1]]
 * Output: 3
 * Explanation: You can rearrange the columns as shown above.
 * The largest submatrix of 1s, in bold, has an area of 3.
 * 
 * Example 3:
 * Input: matrix = [[1,1,0],[1,0,1]]
 * Output: 2
 * Explanation: Notice that you must rearrange entire columns, and there is no way to make a submatrix of 1s larger than an area of 2.
 * 
 * Constraints:
 * m == matrix.length
 * n == matrix[i].length
 * 1 <= m * n <= 105
 * matrix[i][j] is either 0 or 1.
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int largestSubmatrix(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();

        // Step 1: Build height of consecutive 1's for each column
        // Starting from the second row, update each cell:
        // if it's 1, add the value from the cell directly above it.
        for (int i = 1; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (matrix[i][j] == 1) {
                    matrix[i][j] += matrix[i - 1][j];
                }
            }
        }

        int ans = 0;

        // Step 2: For each row, sort heights in descending order (simulate column rearrangement)
        // Then the largest rectangle with this row as base is max over i of (i+1) * sortedRow[i]
        for (auto& row : matrix) {
            sort(row.rbegin(), row.rend()); // descending order
            for (int i = 0; i < n; ++i) {
                ans = max(ans, (i + 1) * row[i]);
            }
        }

        return ans;
    }
};