/*
 * 215. Find the Kth Largest Element in an Array
 *
 * Given an integer array nums and an integer k, return the kth largest element in the array.
 * 
 * Note that it is the kth largest element in the sorted order, not the kth distinct element.
 * 
 * Can you solve it without sorting?
 * 
 * Example 1:
 * Input: nums = [3,2,1,5,6,4], k = 2
 * Output: 5
 * 
 * Example 2:
 * Input: nums = [3,2,3,1,2,4,5,5,6], k = 4
 * Output: 4
 * 
 * Constraints:
 * 1 <= k <= nums.length <= 105
 * -104 <= nums[i] <= 104
 * 
 */
#include <vector>
using namespace std;

int quickSelection(vector<int>& nums, int l, int r) {
  int i = l + 1, j = r;
  while (true) {
    while (i < r && nums[i] <= nums[l]) {
      ++i;
    }
    while (l < j && nums[j] >= nums[l]) {
      --j;
    }
    if (i >= j) {
      break;
    }
    swap(nums[i], nums[j]);
  }
  swap(nums[l], nums[j]);
  return j;
}

int findKLargest(vector<int>& nums, int k) {
  int l = 0, r = nums.size() - 1, target = nums.size() - k;
  while (l < r) {
    int mid = quickSelection(nums, l, r);
    if (mid == target) {
      return nums[mid];
    }

    if (mid < target) {
      l = mid + 1;
    } else {
      r = mid - 1;
    }
  }
  return nums[l];
}