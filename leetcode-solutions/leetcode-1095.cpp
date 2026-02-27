/**
 * 1095. Find in Mountain Array
 * Hard
 *
 * (This problem is an interactive problem.)
 *
 * You may recall that an array arr is a mountain array if and only if:
 *
 * arr.length >= 3
 * There exists some i with 0 < i < arr.length - 1 such that:
 * arr[0] < arr[1] < ... < arr[i - 1] < arr[i]
 * arr[i] > arr[i + 1] > ... > arr[arr.length - 1]
 * Given a mountain array mountainArr, return the minimum index such that mountainArr.get(index) == target. If such an
 * index does not exist, return -1.
 *
 * You cannot access the mountain array directly. You may only access the array using a MountainArray interface:
 *
 * MountainArray.get(k) returns the element of the array at index k (0-indexed).
 * MountainArray.length() returns the length of the array.
 *
 * Example 1:
 * Input: array = [1,2,3,4,5,3,1], target = 3
 * Output: 2
 * Explanation: 3 exists in the array, at index=2 and index=5. Return the minimum index, which is 2.
 *
 * Example 2:
 * Input: array = [0,1,2,4,2,1], target = 3
 * Output: -1
 * Explanation: 3 does not exist in the array, so we return -1.
 *
 * Note:
 * 1 <= mountain_arr.length() <= 1000
 * 0 <= target <= 10^9
 * 0 <= mountain_arr.get(index) <= 10^9
 *
 */
#include <vector>
using namespace std;

/**
 * // This is the MountainArray's API interface.
 * // You should not implement it, or speculate about its implementation
 */
class MountainArray {
 public:
  int get(int index);
  int length();
};

class Solution {
 public:
  int findInMountainArray(int target, MountainArray &mountainArr) {
    int n = mountainArr.length();

    // 1. 二分查找峰值（先递增后递减的转折点）
    int left = 0, right = n - 1;
    while (left < right) {
      int mid = left + (right - left) / 2;
      if (mountainArr.get(mid) < mountainArr.get(mid + 1)) {
        // 峰值在右侧
        left = mid + 1;
      } else {
        // 峰值在左侧或就是 mid
        right = mid;
      }
    }
    int peak = left;  // 峰值索引

    // 2. 在左侧升序区间二分查找目标值
    int idx = binarySearch(mountainArr, target, 0, peak, true);
    if (idx != -1) return idx;

    // 3. 在右侧降序区间二分查找目标值
    return binarySearch(mountainArr, target, peak + 1, n - 1, false);
  }

 private:
  // ascending = true 表示升序区间，false 表示降序区间
  int binarySearch(MountainArray &mountainArr, int target, int left, int right, bool ascending) {
    while (left <= right) {
      int mid = left + (right - left) / 2;
      int val = mountainArr.get(mid);
      if (val == target) return mid;

      if (ascending) {
        // 标准升序二分
        if (val < target) {
          left = mid + 1;
        } else {
          right = mid - 1;
        }
      } else {
        // 降序区间：值越大索引越小
        if (val > target) {
          left = mid + 1;  // 当前值大于目标，说明目标在右侧（更小的值）
        } else {
          right = mid - 1;  // 当前值小于目标，说明目标在左侧（更大的值）
        }
      }
    }
    return -1;
  }
};