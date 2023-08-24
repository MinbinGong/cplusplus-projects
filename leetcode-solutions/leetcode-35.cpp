/*
 * Given a sorted array of distinct integers and a target value, return the
 * index if the target is found. If not, return the index where it would be
 * if it were inserted in order.
 *
 * You must write an algorithm with O(log n) runtime complexity.  
 */
#include <vector>

int search_insert(std::vector<int>& nums, int target) {
    int n = nums.size();
    int l = 0, r = n - 1;

    while (l <= r) {
        int m = l + (r-l) >> 1;

        if (nums[m] == target) {
            return m;
        }

        if (nums[m] < target) {
            l = m + 1;
        } else {
            r = m - 1;
        }
    }
    return l;
}
