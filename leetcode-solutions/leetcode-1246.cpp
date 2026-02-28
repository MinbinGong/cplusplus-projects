/*
 * 1246. Palindrome Removal
 *
 * Given an integer array arr, in one move you can select a palindromic subarray arr[i], arr[i+1], ..., arr[j] where i <= j, and remove that subarray from the given array. Note that after removing a subarray, the elements on the left and on the right of that subarray move to fill the gap left by the removal.
 *
 * Return the minimum number of moves needed to remove all numbers from the array.
 *
 * Example 1:
 * Input: arr = [1,2]
 * Output: 2
 *
 * Example 2:
 * Input: arr = [1,3,4,1,5]
 * Output: 3
 * Explanation: Remove [4] then remove [1,3,1] then remove [5].
 *
 * Constraints:
 * 1 <= arr.length <= 100
 * 1 <= arr[i] <= 20
 *
 */
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minimumMoves(vector<int>& arr) {
        int n = arr.size();
        if (n == 0) return 0;
        
        // dp[i][j] 表示删除子数组 arr[i..j] 所需的最少操作次数
        vector<vector<int>> dp(n, vector<int>(n, 0));
        
        // 长度为1的子数组，单个元素本身就是回文，需要1次操作
        for (int i = 0; i < n; i++) {
            dp[i][i] = 1;
        }
        
        // 枚举子数组长度，从2到n
        for (int len = 2; len <= n; len++) {
            for (int i = 0; i + len - 1 < n; i++) {
                int j = i + len - 1;
                dp[i][j] = INT_MAX;
                
                // 如果两端字符相等，可以考虑将两端与中间部分一起删除
                if (arr[i] == arr[j]) {
                    if (i + 1 > j - 1) {
                        // 中间没有元素，即长度为2且两端相等，整个子数组是回文
                        dp[i][j] = 1;
                    } else {
                        // 中间有元素，先删除中间部分，然后两端可合并为一次操作
                        dp[i][j] = dp[i + 1][j - 1];
                    }
                }
                
                // 枚举分割点，将子数组分成两部分分别删除
                for (int k = i; k < j; k++) {
                    dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j]);
                }
            }
        }
        
        return dp[0][n - 1];
    }
};