/*
 * Find Minimum in Rotated Sorted Array II
 *
 * Suppose an array of length n sorted in ascending order is rotated between
 * 1 and n times. For example, the array nums = [0,1,4,4,5,6,7] might become:
 *
 * [4,5,6,7,0,1,4] if it was rotated 4 times.
 * [0,1,4,4,5,6,7] if it was rotated 7 times.
 * Notice that rotating an array [a[0], a[1], a[2], ..., a[n-1]] 1 time results
 * in the array [a[n-1], a[0], a[1], a[2], ..., a[n-2]].
 *
 * Given the sorted rotated array nums that may contain duplicates, return the
 * minimum element of this array.
 *
 * You must decrease the overall operation steps as much as possible.
 */
#include <algorithm>
#include <climits>
#include <vector>
using namespace std;

int findMin(vector<int>& nums) {
    int start = 0, end = nums.size() - 1, ans = INT_MAX;
    while (start <= end) {
        int mid = start + (end - start) / 2;
        ans = min(ans, nums[mid]);

        if (nums[mid] == nums[start] && nums[mid] == nums[end]) {
            start++;
            end--;
            continue;
        }

        if (nums[start] <= nums[mid]) {
            ans = min(ans, nums[start]);
            start = mid + 1;
        } else {
            end = mid - 1;
        }
    }
    return ans;
}
