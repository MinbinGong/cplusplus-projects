/*
 * 4Sum II
 *
 * Given four integer arrays nums1, nums2, nums3, and nums4 all of length n, return the number of tuples (i, j, k, l) such that:
 * 0 <= i, j, k, l < n
 * nums1[i] + nums2[j] + nums3[k] + nums4[l] == 0
 *
 * Constraints:
 * n == nums1.length
 * n == nums2.length
 * n == nums3.length
 * n == nums4.length
 * 1 <= n <= 200
 * -228 <= nums1[i], nums2[i], nums3[i], nums4[i] <= 228
 * 
 */
#include <unordered_map>
#include <vector>
using namespace std;

int fourSumCount(vector<int> &A, vector<int> &B, vector<int> &C, vector<int> &D) {
  int n = D.size();
  unordered_map<int, int> map;
  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < n; j++) {
      map[(-1) * (C[i] + D[j])]++;
    }
  }
  int count = 0;
  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < n; j++) {
      int num = (A[i] + B[j]);
      if (map.count(num) != 0) {
        count += map[num];
      }
    }
  }
  return count;
}