/*
 * Minimum Falling Path Sum
 *
 * Given a square array of integers A, we want the minimum sum of a falling path through A.
 *
 * A falling path starts at any element in the first row, and chooses one element from each row.  The next row's choice must be in a column that is different from the previous row's column by at most one.
 *
 * Example 1:
 * Input: [[1,2,3],[4,5,6],[7,8,9]]
 * Output: 12
 * Explanation:
 * The possible falling paths are:
 * [1,4,7], [1,4,8], [1,5,7], [1,5,8], [1,5,9]
 * [2,4,7], [2,4,8], [2,5,7], [2,5,8], [2,5,9], [2,6,8], [2,6,9]
 * 
 * Example 2:
 * Input: [[-19,57],[-40,-5]]
 * Output: -59
 * Explanation:
 * The falling path with the smallest sum is: [-19,-40].
 * 
 * Note:
 * 1 <= A.length == A[0].length <= 100
 * -100 <= A[i][j] <= 100
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& matrix) {
        int n = matrix.size();
        if (n == 0) return 0;

        // Start from the second row and update each cell with the minimum falling sum
        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                int best = matrix[i-1][j]; // directly above
                if (j > 0) best = min(best, matrix[i-1][j-1]); // top-left
                if (j < n-1) best = min(best, matrix[i-1][j+1]); // top-right
                matrix[i][j] += best;
            }
        }

        // Answer is the minimum value in the last row
        return *min_element(matrix[n-1].begin(), matrix[n-1].end());
    }
};
