/*
 * 1712. Ways to Split Array Into Three Subarrays
 * 
 * A split of an integer array is good if:
 * 
 * The array is split into three non-empty contiguous subarrays - named left, mid, right respectively from left to right.
 * The sum of the elements in left is less than or equal to the sum of the elements in mid, and the sum of the elements in mid is less than or equal to the sum of the elements in right.
 * Given nums, an array of non-negative integers, return the number of good ways to split nums. As the number may be too large, return it modulo 10^9 + 7.
 * 
 * Example 1:
 * Input: nums = [1,1,1]
 * Output: 1
 * Explanation: The only good way to split nums is [1] [1] [1].
 * 
 * Example 2:
 * Input: nums = [1,2,2,2,5,0]
 * Output: 3
 * Explanation: There are three good ways of splitting nums:
 * [1] [2] [2,2,5,0]
 * [1] [2,2] [2,5,0]
 * [1,2] [2,2] [5,0]
 * 
 * Constraints:
 * 3 <= nums.length <= 10^5
 * 0 <= nums[i] <= 10^4
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int waysToSplit(vector<int>& nums) {
        int n = nums.size();
        vector<int> prefix(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            prefix[i + 1] = prefix[i] + nums[i];
        }
        long long ans = 0;
        const int MOD = 1e9 + 7;

        // 枚举左边子数组的结束位置 i（左边包含前 i 个元素，即 [0, i-1]）
        for (int i = 1; i <= n - 2; ++i) {
            int left_sum = prefix[i];

            // 二分查找最小的 j 使得中间子数组的和 >= 左边和
            // 即 prefix[j] - prefix[i] >= left_sum  => prefix[j] >= 2 * left_sum
            int low = i + 1, high = n - 1;
            int left_j = -1;
            int l = low, r = high;
            while (l <= r) {
                int mid = (l + r) / 2;
                if (prefix[mid] >= 2 * left_sum) {
                    left_j = mid;
                    r = mid - 1;
                } else {
                    l = mid + 1;
                }
            }
            if (left_j == -1) continue;

            // 二分查找最大的 j 使得中间子数组的和 <= 右边子数组的和
            // 即 prefix[j] - prefix[i] <= prefix[n] - prefix[j]  => 2 * prefix[j] <= prefix[n] + left_sum
            int max_mid = (prefix[n] + left_sum) / 2;
            l = left_j, r = high;
            int right_j = -1;
            while (l <= r) {
                int mid = (l + r) / 2;
                if (prefix[mid] <= max_mid) {
                    right_j = mid;
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
            }
            if (right_j != -1) {
                ans = (ans + (right_j - left_j + 1)) % MOD;
            }
        }
        return ans;
    }
};