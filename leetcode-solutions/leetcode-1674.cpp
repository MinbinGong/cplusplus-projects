/*
 * 1674. Minimum Moves to Make Array Complementary
 * 
 * You are given an integer array nums of even length n and an integer limit. In one move, you can replace any integer from nums with another integer between 1 and limit, inclusive.
 * 
 * The array nums is complementary if for all indices i (0-indexed), nums[i] + nums[n - 1 - i] equals the same number. For example, the array [1,2,3,4] is complementary because for all indices i, nums[i] + nums[n - 1 - i] = 5.
 * 
 * Return the minimum number of moves required to make nums complementary.
 * 
 * Example 1:
 * Input: nums = [1,2,4,3], limit = 4
 * Output: 1
 * Explanation: In 1 move, you can change nums to [1,2,2,3] (underlined elements are changed).
 * nums[0] + nums[3] = 1 + 3 = 4.
 * nums[1] + nums[2] = 2 + 2 = 4.
 * nums[2] + nums[1] = 2 + 2 = 4.
 * nums[3] + nums[0] = 3 + 1 = 4.
 * 
 * Example 2:
 * Input: nums = [1,2,2,1], limit = 2
 * Output: 2
 * Explanation: In 2 moves, you can change nums to [2,2,2,2]. You cannot change any number to 3 since 3 > limit.
 * 
 * Example 3:
 * Input: nums = [1,2,1,2], limit = 2
 * Output: 0
 * Explanation: nums is already complementary.
 * 
 * Constraints:
 * n == nums.length
 * 2 <= n <= 105
 * 1 <= nums[i] <= limit <= 105
 * n is even.
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    int minMoves(vector<int>& nums, int limit) {
        int n = nums.size();
        int pairs = n / 2;
        // 差分数组，下标范围 0 ~ 2*limit+1，实际有效区间 [2, 2*limit]
        vector<int> diff(2 * limit + 2, 0);
        int base = n; // 每个数对初始贡献2次，总基础操作次数 = n

        for (int i = 0; i < pairs; ++i) {
            int a = nums[i];
            int b = nums[n - 1 - i];
            int lo = min(a, b);
            int hi = max(a, b);
            int sum = a + b;

            // 区间 [lo+1, hi+limit] 内操作次数减1（从2变成1）
            int left = lo + 1;
            int right = hi + limit;
            // left 最小为2，right 最大为 2*limit，区间一定非空
            diff[left] -= 1;
            diff[right + 1] += 1;

            // 点 sum 处再减1（从1变成0）
            diff[sum] -= 1;
            diff[sum + 1] += 1;
        }

        int cur = base;
        int ans = INT_MAX;
        for (int t = 2; t <= 2 * limit; ++t) {
            cur += diff[t];
            ans = min(ans, cur);
        }
        return ans;
    }
};