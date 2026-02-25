/*
 * 1043. Partition Array for Maximum Sum
 *
 * Given an integer array A, you partition the array into (contiguous) subarrays of length at most K.  After partitioning, each subarray has their values changed to become the maximum value of that subarray.
 * 
 * Return the largest sum of the given array after partitioning.
 * 
 * Example 1:
 * Input: A = [1,15,7,9,2,5,10], K = 3
 * Output: 84
 * Explanation: A becomes [15,15,15,9,10,10,10]
 * 
 * Example 2:
 * Input: A = [1,4,1,5,7,3,6,1,9,9,3], K = 4
 * Output: 83
 * 
 * Example 3:
 * Input: A = [1], K = 1
 * Output: 1
 * 
 * Note:
 * 1. 1 <= K <= A.length <= 500
 * 2. 0 <= A[i] <= 10^6
 * 3. The answer is guaranteed to fit in a 32-bit integer.
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    int maxSumAfterPartitioning(vector<int>& arr, int k) {
        int n = arr.size();
        vector<int> dp(n + 1, 0); // dp[i]表示前i个元素的最大和
        
        for (int i = 1; i <= n; i++) {
            int maxVal = 0; // 当前子数组的最大值
            // 尝试最后一段子数组的长度j（1到k，且不超过i）
            for (int j = 1; j <= k && j <= i; j++) {
                maxVal = max(maxVal, arr[i - j]); // 更新当前子数组的最大值
                dp[i] = max(dp[i], dp[i - j] + maxVal * j);
            }
        }
        
        return dp[n];
    }
};