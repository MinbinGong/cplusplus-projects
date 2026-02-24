/*
 * Sort an Array
 *
 * Given an array of integers nums, sort the array in ascending order.
 * 
 * Example 1:
 * Input: nums = [5,2,3,1]
 * Output: [1,2,3,5]
 * 
 * Example 2:
 * Input: nums = [5,1,1,2,0,0]
 * Output: [0,0,1,1,2,5]
 * 
 * Note:
 * 1 <= nums.length <= 50000
 * -50000 <= nums[i] <= 50000
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        // Using merge sort for guaranteed O(n log n) performance
        vector<int> temp(nums.size());
        mergeSort(nums, 0, nums.size() - 1, temp);
        return nums;
    }

private:
    void mergeSort(vector<int>& nums, int left, int right, vector<int>& temp) {
        if (left >= right) return;
        int mid = left + (right - left) / 2;
        mergeSort(nums, left, mid, temp);
        mergeSort(nums, mid + 1, right, temp);
        merge(nums, left, mid, right, temp);
    }

    void merge(vector<int>& nums, int left, int mid, int right, vector<int>& temp) {
        int i = left, j = mid + 1, k = left;
        while (i <= mid && j <= right) {
            if (nums[i] <= nums[j]) {
                temp[k++] = nums[i++];
            } else {
                temp[k++] = nums[j++];
            }
        }
        while (i <= mid) temp[k++] = nums[i++];
        while (j <= right) temp[k++] = nums[j++];
        // copy back to original array
        for (int idx = left; idx <= right; ++idx) {
            nums[idx] = temp[idx];
        }
    }
};