/**
 * 976. Largest Perimeter Triangle
 *
 * Given an integer array nums, return the largest perimeter of a triangle with a non-zero area, formed from three of these lengths. If it is impossible to form any triangle of a non-zero area, return 0.
 *
 * Example 1:
 *
 * Input: nums = [2,1,2]
 * Output: 5
 * Explanation: You can form a triangle with three side lengths: 1, 2, and 2.
 * 
 * Example 2:
 *
 * Input: nums = [1,2,1]
 * Output: 0
 * Explanation: You cannot use the three lengths to form a triangle of non-zero area.
 * 
 * Note:
 *
 * 3 <= nums.length <= 104
 * 1 <= nums[i] <= 106
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int largestPerimeter(vector<int>& nums) {
        // 先对数组进行排序
        sort(nums.begin(), nums.end());
        
        // 从后往前遍历，检查三个连续的元素是否能构成三角形
        for (int i = nums.size() - 1; i >= 2; --i) {
            // 三角形条件：两边之和大于第三边
            // 由于已排序，只需检查 nums[i-2] + nums[i-1] > nums[i]
            if (nums[i-2] + nums[i-1] > nums[i]) {
                return nums[i-2] + nums[i-1] + nums[i];
            }
        }
        
        // 无法构成三角形
        return 0;
    }
};