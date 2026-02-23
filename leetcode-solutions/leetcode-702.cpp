/*
 * Search in a Sorted Array of Unknown Size
 *
 * Given a sorted array of unknown length and a number to search for, return the index of the number in the array.
 * Accessing an element out of bounds throws exception. If the number occurs multiple times, return the index of any
 * occurrence. If it isn’t present, return -1.
 *
 * Example 1:
 *
 * Input: array = [-1,0,3,5,9,12], target = 9
 * Output: 4
 * Explanation: 9 exists in nums and its index is 4
 *
 * Example 2:
 *
 * Input: array = [-1,0,3,5,9,12], target = 2
 * Output: -1
 * Explanation: 2 does not exist in nums so return -1
 *
 * Note:
 * 1. You may assume that all elements in the array are unique.
 * 2. The value of each element in the array will be in the range [-9999, 9999].
 * 3. The length of the array will be in the range [1, 10000].
 * 4. You must write an algorithm with O(log n) runtime complexity.
 * 5. The array is sorted in ascending order.
 *
 */
#include <climits>

// This is the ArrayReader's API interface.
// You should not implement it, or speculate about its implementation
class ArrayReader {
 public:
  int get(int index);
};

class Solution {
 public:
  int search(const ArrayReader& reader, int target) {
    // 1. 指数搜索确定右边界
    int left = 0;
    int right = 1;
    // 不断将右边界翻倍，直到找到大于等于 target 的值或越界
    while (reader.get(right) < target) {
      left = right;
      right <<= 1;  // 相当于 right *= 2
    }

    // 2. 在 [left, right] 区间内进行二分查找
    while (left <= right) {
      int mid = left + (right - left) / 2;
      int val = reader.get(mid);

      // 处理越界情况：如果 mid 越界，说明 target 在左边
      if (val == INT_MAX) {
        right = mid - 1;
      } else if (val == target) {
        return mid;
      } else if (val < target) {
        left = mid + 1;
      } else {  // val > target
        right = mid - 1;
      }
    }
    return -1;
  }
};