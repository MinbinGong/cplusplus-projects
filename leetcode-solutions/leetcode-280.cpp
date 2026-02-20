/*
 * Wiggle Sort
 * 
 * Given an integer array nums, reorder it such that nums[0] <= nums[1] >= nums[2] <= nums[3]....
 * 
 * You may assume the input array always has a valid answer.
 * 
 * Example 1:
 * Input: nums = [3,5,2,1,6,4]
 * Output: [3,5,1,6,2,4]
 * Explanation: [1,6,2,5,3,4] is also accepted.
 * 
 * Example 2:
 * Input: nums = [6,6,5,6,3,8]
 * Output: [6,6,5,6,3,8]
 * 
 * Constraints:
 * 1 <= nums.length <= 5 * 104
 * 0 <= nums[i] <= 104
 * nums is guaranteed to have a valid answer.
 */
#include <vector>
using namespace std;

class Solution {
public:
    void wiggleSort(vector<int>& nums) {
        for (int i = 1; i < nums.size(); ++i) {
            // For odd index (1,3,5...), we want nums[i] >= nums[i-1]
            // For even index (2,4,6...), we want nums[i] <= nums[i-1]
            if ((i % 2 == 1 && nums[i] < nums[i-1]) ||
                (i % 2 == 0 && nums[i] > nums[i-1])) {
                swap(nums[i], nums[i-1]);
            }
        }
    }
};