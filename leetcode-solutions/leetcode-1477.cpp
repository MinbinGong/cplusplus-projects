/**
 * 1477. Find Two Non-overlapping Sub-arrays Each With Target Sum
 * 
 * Given an array of integers arr and an integer target.
 * 
 * You have to find two non-overlapping sub-arrays of arr each with sum equal target. 
 * There can be multiple answers so you have to find an answer where the sum of the lengths of the two sub-arrays is minimum.
 * 
 * Return the minimum sum of the lengths of the two required sub-arrays, or return -1 if you cannot find such two sub-arrays.
 * 
 * Example 1:
 * 
 * Input: arr = [3,2,2,4,3], target = 3
 * Output: 2
 * Explanation: Only two sub-arrays have sum = 3 ([3] and [3]). The sum of their lengths is 2.
 * 
 * Example 2:
 * 
 * Input: arr = [7,3,4,7], target = 7
 * Output: 2
 * Explanation: Although we have three non-overlapping sub-arrays of sum = 7 ([7], [3,4] and [7]), but we will choose the first and third sub-arrays as the sum of their lengths is 2.
 * 
 * Example 3:
 * 
 * Input: arr = [4,3,2,6,2,3,4], target = 6
 * Output: -1
 * Explanation: We have only one sub-array of sum = 6.
 * 
 * Example 4:
 * 
 * Input: arr = [5,5,4,4,5], target = 3
 * Output: -1
 * Explanation: We cannot find a sub-array of sum = 3.
 * 
 * Example 5:
 * 
 * Input: arr = [3,1,1,1,5,1,2,1], target = 3
 * Output: 3
 * Explanation: Note that sub-arrays [1,2] and [2,1] cannot be an answer because they overlap.
 * 
 * Constraints:
 * 1 <= arr.length <= 10^5
 * 1 <= arr[i] <= 1000
 * 1 <= target <= 10^8
 * 
 */
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int minSumOfLengths(vector<int>& arr, int target) {
        int n = arr.size();
        // dp[i] 表示前 i 个元素（即区间 [0, i-1]）中，和为 target 的最短子数组的长度
        vector<int> dp(n + 1, INT_MAX / 2); // 初始化为一个较大的数，防止溢出
        dp[0] = INT_MAX / 2; // 前 0 个元素中不可能有合法子数组

        unordered_map<int, int> pos; // 记录前缀和及其最后出现的索引
        pos[0] = -1; // 初始化前缀和0出现在索引-1，方便处理从0开始的子数组

        int sum = 0;
        int ans = INT_MAX;

        for (int i = 0; i < n; ++i) {
            sum += arr[i];
            pos[sum] = i; // 记录当前前缀和的位置

            int need = sum - target;
            // 如果存在一个前缀和等于 need，说明找到了一个和为 target 的子数组
            if (pos.count(need)) {
                int j = pos[need]; // 子数组的起始索引是 j+1
                int curr_len = i - j; // 当前子数组的长度

                // 如果 j+1 > 0，说明在它左边有可能存在另一个合法子数组
                // dp[j+1] 存储的就是在索引 j 之前（包括 j）的最短合法子数组长度
                // 注意：j 是 need 的索引，所以左边部分是 [0, j]，其长度信息存储在 dp[j+1] 中
                if (dp[j + 1] < INT_MAX / 2) {
                    ans = min(ans, dp[j + 1] + curr_len);
                }

                // 更新 dp[i+1]，它要么继承 dp[i] 的值，要么是当前子数组的长度（如果更短）
                dp[i + 1] = min(dp[i], curr_len);
            } else {
                // 没有找到以 i 结尾的合法子数组，则 dp[i+1] 继承 dp[i]
                dp[i + 1] = dp[i];
            }
        }

        return ans == INT_MAX ? -1 : ans;
    }
};