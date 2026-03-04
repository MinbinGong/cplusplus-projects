/**
 * 1546. Maximum Number of Non-Overlapping Subarrays With Sum Equals Target
 * 
 * Given an array nums and an integer target.
 * 
 * Return the maximum number of non-empty non-overlapping subarrays such that the sum of values in each subarray is equal to target.
 * 
 * 
 * Example 1:
 * Input: nums = [1,1,1,1,1], target = 2
 * Output: 2
 * Explanation: There are 2 non-overlapping subarrays [1,1,1,1,1] with sum equals to target(2).
 * 
 * Example 2:
 * Input: nums = [-1,3,5,1,4,2,-9], target = 6
 * Output: 2
 * Explanation: There are 3 subarrays with sum equal to 6.
 * ([5,1], [4,2], [3,5,1,4,2,-9]) but only the first 2 are non-overlapping.
 * 
 * Example 3:
 * Input: nums = [4,3,2,1], target = 5
 * Output: 1
 * Explanation: There is 1 non-overlapping subarray [4,3,2,1] with sum equals to target(5).
 * 
 * Constraints:
 * 1 <= nums.length <= 10^5
 * -10^4 <= nums[i] <= 10^4
 * 0 <= target <= 10^6
 * 
 */
#include <vector>
#include <unordered_set>
using namespace std;

class Solution {
public:
    int maxNonOverlapping(vector<int>& nums, int target) {
        unordered_set<int> seen;
        seen.insert(0);
        int sum = 0, ans = 0;
        for (int num : nums) {
            sum += num;
            if (seen.count(sum - target)) {
                ++ans;
                sum = 0;
                seen.clear();
                seen.insert(0);
            } else {
                seen.insert(sum);
            }
        }
        return ans;
    }
};