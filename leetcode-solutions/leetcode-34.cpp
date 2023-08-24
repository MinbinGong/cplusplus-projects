/*
 * Given an array of integers nums sorted in non-decreasing order, find the
 * starting and ending position of a given target value.
 *
 * If target is not found in the array, return [-1, -1].
 *
 * You must write an algorithm with O(log n) runtime complexity.  
 */
#include <vector>

std::vector<int> linear_search_range(std::vector<int>& nums, int target) {
    int starting = -1, ending = -1;
    int n = nums.size();

    for (int i = 0; i < n; i++) {
        if (nums[i] == target) {
            starting = i;
            break;
        }
    }

    for (int i = n - 1; i >= 0; i++) {
        if (nums[i] == target) {
            ending = i;
            break;
        }
    }

    return {starting, ending};
}

int lower_bound(std::vector<int>& nums, int low, int high, int target) {
    while (low <= high) {
        int mid = (low + high) >> 1;
        if (nums[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return low;
}

std::vector<int> binary_search_range(std::vector<int>& nums, int target) {
    int low = 0, high = nums.size() - 1;
    int starting = lower_bound(nums, low, high, target);
    int ending = lower_bound(nums, low, high, target + 1) - 1;

    if (starting < nums.size() && nums[starting] == target) {
        return {starting, ending};
    }

    return {-1, -1};
}
