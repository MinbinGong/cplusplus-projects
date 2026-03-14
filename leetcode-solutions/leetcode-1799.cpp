/**
 * 1799. Maximize Score After N Operations
 * 
 * You are given nums, an array of positive integers of size 2 * n. You must perform n operations on this array.
 * 
 * In the ith operation (1-indexed), you will:
 * 
 * Choose two elements, x and y.
 * Receive a score of i * gcd(x, y).
 * Remove x and y from nums.
 * Return the maximum score you can receive after performing n operations.
 * 
 * The function gcd(x, y) is the greatest common divisor of x and y.
 * 
 *  
 * 
 * Example 1:
 * 
 * Input: nums = [1,2]
 * Output: 1
 * Explanation: The optimal choice of operations is:
 * (1 * gcd(1, 2)) = 1
 * Example 2:
 * 
 * Input: nums = [3,4,6,8]
 * Output: 11
 * Explanation: The optimal choice of operations is:
 * (1 * gcd(3, 6)) + (2 * gcd(4, 8)) = 3 + 8 = 11
 * Example 3:
 * 
 * Input: nums = [1,2,3,4,5,6]
 * Output: 14
 * Explanation: The optimal choice of operations is:
 * (1 * gcd(1, 5)) + (2 * gcd(2, 4)) + (3 * gcd(3, 6)) = 1 + 4 + 9 = 14
 *  
 * 
 * Constraints:
 * 
 * n == nums.length
 * 2 <= n <= 14
 * n is even.
 * 1 <= nums[i] <= 100
 * 
 */

#include <vector>
#include <algorithm>
#include <numeric> // for gcd (C++17)
#include <cstring> // for memset
using namespace std;

class Solution {
public:
    int maxScore(vector<int>& nums) {
        int m = nums.size();
        // 1. 预处理任意两个数之间的最大公约数 (GCD)
        // 使用一个 m x m 的二维数组存储，避免重复计算
        vector<vector<int>> gcdCache(m, vector<int>(m, 0));
        for (int i = 0; i < m; ++i) {
            for (int j = i + 1; j < m; ++j) {
                // C++17 标准库提供了 std::gcd
                gcdCache[i][j] = gcd(nums[i], nums[j]);
                // 矩阵是对称的，所以可以同时赋值
                gcdCache[j][i] = gcdCache[i][j];
            }
        }

        // 2. 动态规划数组 dp[mask]
        // mask 是一个二进制数，第 i 位为 1 表示 nums[i] 已经被选走（已使用）
        // dp[mask] 表示在状态 mask 下，已经获得的最大分数和
        int totalStates = 1 << m; // 总状态数，2^m
        vector<int> dp(totalStates, 0);

        // 3. 遍历所有状态，进行状态转移
        // 从全未选状态 (0) 开始向全选状态递推，或者反过来。
        // 这里采用从全未选 (0) 开始递推到全选 (totalStates-1) 的方式。
        for (int mask = 0; mask < totalStates; ++mask) {
            // 计算当前状态 mask 中已经选了多少个数（即二进制中 1 的个数）
            int selectedCount = __builtin_popcount(mask);
            
            // 如果选了奇数个数，说明之前的状态转移有问题（一次操作选两个数）
            // 理论上，根据我们的转移规则，不会进入奇数状态，这里可以跳过确保安全
            if (selectedCount % 2 != 0) {
                continue;
            }

            // 当前是第几次操作？操作次数 = 已选数量 / 2
            // 注意：下一次操作的系数是 (操作次数 + 1)
            int nextOpIndex = selectedCount / 2 + 1;

            // 尝试从当前状态 mask 中，选择两个未被选中的数 i 和 j
            for (int i = 0; i < m; ++i) {
                // 如果 i 已经被选了，跳过
                if (mask & (1 << i)) continue;
                for (int j = i + 1; j < m; ++j) {
                    // 如果 j 已经被选了，跳过
                    if (mask & (1 << j)) continue;

                    // 新状态：将 i 和 j 也选上
                    int newMask = mask | (1 << i) | (1 << j);
                    
                    // 状态转移方程：
                    // dp[newMask] 可以由 dp[mask] 加上当前操作的分数得到
                    // 当前操作分数 = 操作系数 * gcd(nums[i], nums[j])
                    dp[newMask] = max(dp[newMask], 
                                      dp[mask] + nextOpIndex * gcdCache[i][j]);
                }
            }
        }

        // 最终答案是所有数都选上的状态，即 mask 全为 1
        return dp[totalStates - 1];
    }
};
