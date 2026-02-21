/*
 * Arithmetic Slices
 *
 * A sequence of numbers is called arithmetic if it consists of at least three elements and if the difference between any two consecutive elements is the same.
 *
 * For example, these are arithmetic sequences:
 *
 * 1, 3, 5, 7, 9
 * 7, 7, 7, 7
 * 3, -1, -5, -9
 * The following sequence is not arithmetic:
 *
 * 1, 1, 2, 5, 7
 * A zero-indexed array A consisting of N numbers is given. A slice of that array is any pair of integers (P, Q) such that 0 <= P < Q < N.
 *
 * A slice (P, Q) of array A is called arithmetic if the sequence:
 * A[P], A[p + 1], ..., A[Q - 1], A[Q] is arithmetic. In particular, this means that P + 1 < Q.
 *
 * The function should return the number of arithmetic slices in the array A.
 * 
 * Example 1:
 * Input: A = [1, 2, 3, 4]
 * Output: 3
 * Explanation: We have 3 arithmetic slices in A: [1, 2, 3], [2, 3, 4] and [1, 2, 3, 4] itself.
 * 
 * Example 2:
 * Input: A = [1, 3, 5, 7, 9]
 * Output: 6
 * Explanation: We have 6 arithmetic slices in A: [1, 3, 5], [3, 5, 7], [5, 7, 9], [1, 3, 5, 7], [3, 5, 7, 9], [1, 3, 5, 7, 9].
 * 
 * Constraints:
 * 1 <= A.length <= 5000
 * -10000 <= A[i] <= 10000
 * 
 */
#include <vector>
using namespace std;

int numberOfArithmeticSlices1(vector<int> &A) {
  int i, n = A.size(), res = 0, cur = 1;
  for (i = 2; i < n; i++) {
    if (A[i] - A[i - 1] == A[i - 1] - A[i - 2]) {
      cur++;
    } else {
      res = res + (cur * (cur - 1)) / 2;
      cur = 1;
    }
  }
  res = res + (cur * (cur - 1)) / 2;
  return res;
}

int numberOfArithmeticSlices2(vector<int> &A) {
  if (A.size() < 3) return 0;
  int result = 0;
  vector<int> currentElements;
  int currentDifference = A[1] - A[0];
  currentElements.push_back(A[1] - A[0]);
  for (int i = 1; i < A.size(); i++) {
    if (A[i] - A[i - 1] == currentDifference) {
      currentElements.push_back(A[i - 1]);
      if (currentElements.size() >= 3) {
        result += currentElements.size() - 2;
      }
    } else {
      currentElements.clear();
      currentDifference = A[i] - A[i - 1];
      currentElements.push_back(A[i - 1]);
      currentElements.push_back(A[i]);
    }
  }

  return result;
}

int numberOfArithmeticSlices3(vector<int> &nums) {
  int n = nums.size();
  if (n < 3) {
    return 0;
  }
  vector<int> dp(n, 0);
  for (int i = 0; i < n; ++i) {
    if (nums[i] - nums[i - 1] == nums[i - 1] - nums[i - 2]) {
      dp[i] = dp[i - 1] + 1;
    }
  }

  int res;
  for (const auto item : dp) {
    res += item;
  }

  return res;
}