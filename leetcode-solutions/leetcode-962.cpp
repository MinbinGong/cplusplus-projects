/*
 * 962. Maximum Width Ramp
 *
 * A ramp in an integer array nums is a pair (i, j) for which i < j and nums[i] <= nums[j]. The width of such a ramp is j - i.
 *
 * Given an integer array nums, return the maximum width of a ramp in nums. If there is no ramp in nums, return 0.
 *
 * Example 1:
 *
 * Input: nums = [6,0,8,2,1,5]
 * Output: 4
 * Explanation: The maximum width ramp is achieved at (i, j) = (1, 5): nums[1] = 0 and nums[5] = 5.
 * 
 * Example 2:
 *
 * Input: nums = [9,8,1,0,1,9,4,0,4,1]
 * Output: 7
 * Explanation: The maximum width ramp is achieved at (i, j) = (2, 9): nums[2] = 1 and nums[9] = 1.
 * 
 * Note:
 * 2 <= nums.length <= 5 * 10^4
 * 0 <= nums[i] <= 5 * 10^4
 * 
 */
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxWidthRamp(vector<int>& nums) {
        int n = nums.size();
        vector<int> idx(n);
        iota(idx.begin(), idx.end(), 0);                     // 生成索引 0..n-1
        // 按值升序，值相同时按索引升序
        sort(idx.begin(), idx.end(), [&](int i, int j) {
            return nums[i] == nums[j] ? i < j : nums[i] < nums[j];
        });

        int ans = 0, min_i = n;                              // min_i 记录已遍历的最小索引
        for (int j : idx) {
            if (j > min_i) ans = max(ans, j - min_i);        // 当前索引作为 j，与之前最小 i 形成候选
            min_i = min(min_i, j);                            // 更新最小索引
        }
        return ans;
    }
};