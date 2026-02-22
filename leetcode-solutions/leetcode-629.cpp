/*
 * K Inverse Pairs Array
 *
 * For an integer array nums, an inverse pair is a pair of integers [i, j] where 0 <= i < j < nums.length and
 * nums[i] > nums[j].
 * 
 * Given two integers n and k, return the number of different arrays consist of numbers from 1 to n such that there are
 * exactly k inverse pairs. Since the answer can be huge, return it modulo 109 + 7.
 * 
 * Example 1:
 * Input: n = 3, k = 0
 * Output: 1
 * Explanation: Only the array [1,2,3] which consists of numbers from 1 to 3 has exactly 0 inverse pair.
 * 
 * Example 2:
 * Input: n = 3, k = 1
 * Output: 2
 * Explanation: The array [1,3,2] and [2,1,3] have exactly 1 inverse pair.
 * 
 * Constraints:
 * 1 <= n <= 1000
 * 0 <= k <= 1000
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int kInversePairs(int n, int k) {
        const int MOD = 1e9 + 7;
        vector<int> dp(k + 1, 0);
        dp[0] = 1; // 空排列有一个（即0个逆序对）

        for (int i = 1; i <= n; ++i) {
            vector<int> new_dp(k + 1, 0);
            long long sum = 0; // 维护窗口内 dp 值的和
            for (int j = 0; j <= k; ++j) {
                sum += dp[j];
                if (j >= i) sum -= dp[j - i]; // 窗口宽度为 i
                sum = (sum + MOD) % MOD;       // 防止负数
                new_dp[j] = sum % MOD;
            }
            dp = move(new_dp);
        }
        return dp[k];
    }
};