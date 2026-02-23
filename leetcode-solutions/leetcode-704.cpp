/*
 * Binary Search
 * 
 * Given a sorted array of unknown length and a number to search for, return the index of the number in the array. Accessing an element out of bounds throws exception. If the number occurs multiple times, return the index of any occurrence. If it isn’t present, return -1.
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
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2; // 防止溢出
            if (nums[mid] == target) {
                return mid;
            } else if (nums[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return -1;
    }
};