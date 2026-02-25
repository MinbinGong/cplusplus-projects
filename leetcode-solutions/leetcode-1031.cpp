/*
 * 1031. Maximum Sum of Two Non-Overlapping Subarrays
 *
 * Given an array A of non-negative integers, return the maximum sum of elements in two non-overlapping (contiguous)
 * subarrays, which have lengths L and M.  (For clarification, the L-length subarray could occur before or after the
 * M-length subarray.)
 *
 * Formally, return the largest V for which V = (A[i] + A[i+1] + ... + A[i+L-1]) + (A[j] + A[j+1] + ... + A[j+M-1]) and
 * either:
 *
 * 0 <= i < i + L - 1 < j < j + M - 1 < A.length, or
 * 0 <= j < j + M - 1 < i < i + L - 1 < A.length.
 *
 * Example 1:
 *
 * Input: A = [0,6,5,2,2,5,1,9,4], L = 1, M = 2
 * Output: 20
 * Explanation: One choice of subarrays is [9] with length 1, and [6,5] with length 2.
 *
 * Example 2:
 *
 * Input: A = [3,8,1,3,2,1,8,9,0], L = 3, M = 2
 * Output: 29
 * Explanation: One choice of subarrays is [3,8,1] with length 3, and [8,9] with length 2.
 *
 * Note:
 * 1 <= L <= M <= A.length <= 1000
 * 0 <= A[i] <= 1000
 */
#include <climits>
#include <vector>

using namespace std;

class Solution {
 public:
  int maxSumTwoNoOverlap(vector<int>& A, int L, int M) {
    int n = A.size();
    // prefix sums
    vector<int> ps(n + 1, 0);
    for (int i = 0; i < n; ++i) ps[i + 1] = ps[i] + A[i];

    // helper to compute leftMax and rightMax for a given length
    auto build = [&](int len) -> pair<vector<int>, vector<int>> {
      vector<int> left(n, INT_MIN);   // best sum ending at or before i
      vector<int> right(n, INT_MIN);  // best sum starting at or after i

      // left: i is the ending index of the subarray
      for (int i = len - 1; i < n; ++i) {
        int sum = ps[i + 1] - ps[i + 1 - len];
        left[i] = max(i > 0 ? left[i - 1] : INT_MIN, sum);
      }

      // right: i is the starting index
      for (int i = n - len; i >= 0; --i) {
        int sum = ps[i + len] - ps[i];
        right[i] = max(i + 1 < n ? right[i + 1] : INT_MIN, sum);
      }
      return {left, right};
    };

    auto [leftL, rightL] = build(L);
    auto [leftM, rightM] = build(M);

    int ans = INT_MIN;
    for (int p = 0; p < n - 1; ++p) {
      // L left, M right
      if (leftL[p] != INT_MIN && rightM[p + 1] != INT_MIN) ans = max(ans, leftL[p] + rightM[p + 1]);
      // M left, L right
      if (leftM[p] != INT_MIN && rightL[p + 1] != INT_MIN) ans = max(ans, leftM[p] + rightL[p + 1]);
    }
    return ans;
  }
};