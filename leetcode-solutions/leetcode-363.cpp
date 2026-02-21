/*
 * leetcode-363: Max Sum of Rectangle No Larger Than K
 *
 * Given an m x n matrix matrix and an integer k, return the max sum of a rectangle in the matrix such that its sum is no larger than k.
 * 
 * Note: The rectangle inside the matrix must have an area > 0.
 * 
 * Example 1:
 * Input: matrix = [[1,0,1],[0,-2,3]], k = 2
 * Output: 2
 * Explanation: Because the sum of the blue rectangle [[0, 1], [-2, 3]] is 2, and 2 is the max number no larger than k (k = 2).
 * 
 * Example 2:
 * Input: matrix = [[2,2,-1]], k = 3
 * Output: 3
 * 
 * Constraints:
 * m == matrix.length
 * n == matrix[i].length
 * 1 <= m, n <= 100
 * -100 <= matrix[i][j] <= 100
 * -105 <= k <= 105
 * 
 */
#include <algorithm>
#include <set>
#include <vector>
using namespace std;

int maxSumSubmatrix(vector<vector<int>> &matrix, int k) {
  if (matrix.empty()) return 0;
  int row = matrix.size(), col = matrix[0].size(), res = INT_MIN;
  for (int l = 0; l < col; ++l) {
    vector<int> sums(row, 0);
    for (int r = l; r < col; ++r) {
      for (int i = 0; i < row; ++i) {
        sums[i] += matrix[i][r];
      }

      // Find the max subarray no more than K
      set<int> accuSet;
      accuSet.insert(0);
      int curSum = 0, curMax = INT_MIN;
      for (int sum : sums) {
        curSum += sum;
        set<int>::iterator it = accuSet.lower_bound(curSum - k);
        if (it != accuSet.end()) curMax = std::max(curMax, curSum - *it);
        accuSet.insert(curSum);
      }
      res = std::max(res, curMax);
    }
  }
  return res;
}