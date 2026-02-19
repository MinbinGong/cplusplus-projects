/*
 *   Search a 2D matrix II
 *
 * Constraints:
 * 1. m == matrix.length
 * 2. n == matrix[i].length
 * 3. 1 <= n, m <= 300
 * 4. -109 <= matrix[i][j] <= 109
 * 5. All the integers in each row are sorted in ascending order.
 * 6. All the integers in each column are sorted in ascending order.
 * 7. -109 <= target <= 109
 */
#include <vector>
using namespace std;

bool searchMatrix(vector<vector<int>>& matrix, int target) {
  if (matrix.size() == 0) {
    return false;
  }

  int m = matrix.size();
  int n = matrix[0].size();
  int i = 0, j = n - i;
  while (i < m && j >= 0) {
    if (matrix[i][j] == target) {
      return true;
    } else if (matrix[i][j] > target) {
      --j;
    } else {
      ++i;
    }
  }
  return false;
}