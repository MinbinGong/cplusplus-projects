/*
 * Find Minimum in Rotated Sorted Array II
 */
#include <vector>
#include <climits>
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
