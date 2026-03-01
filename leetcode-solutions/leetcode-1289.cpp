/**
 * 1289. Minimum Falling Path Sum II
 * 
 * Given a square grid of integers arr, a falling path with non-zero shifts is a choice of exactly one element from each row of arr,
 * such that no two elements chosen in adjacent rows are in the same column.
 * 
 * Return the minimum sum of a falling path with non-zero shifts.
 * 
 * Example 1:
 * Input: arr = [[1,2,3],[4,5,6],[7,8,9]]
 * Output: 13
 * Explanation: 
 * The possible falling paths are:
 * [1,5,9], [1,5,7], [2,4,8], [2,4,9], [3,4,8], [3,4,9]
 * The falling path with the smallest sum is [1,5,7], so the answer is 13.
 * 
 * Note:
 * 1 <= arr.length == arr[i].length <= 200
 * -99 <= arr[i][j] <= 99
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution1 {
public:
    int minFallingPathSum(vector<vector<int>>& grid) {
        int n = grid.size();
        // 处理特殊情况：只有一行
        if (n == 1) return grid[0][0];
        
        // dp数组，初始化为第一行
        vector<vector<int>> dp(n, vector<int>(n, INT_MAX));
        dp[0] = grid[0];
        
        // 动态规划
        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                // 寻找上一行的最小值（列不能等于j）
                int minPrev = INT_MAX;
                for (int k = 0; k < n; ++k) {
                    if (k != j) {
                        minPrev = min(minPrev, dp[i-1][k]);
                    }
                }
                dp[i][j] = grid[i][j] + minPrev;
            }
        }
        
        // 返回最后一行的最小值
        return *min_element(dp[n-1].begin(), dp[n-1].end());
    }
};

class Solution2 {
public:
    int minFallingPathSum(vector<vector<int>>& grid) {
        int n = grid.size();
        // 处理特殊情况：只有一行
        if (n == 1) return grid[0][0];
        
        // dp数组表示上一行的结果
        vector<int> dp = grid[0];
        
        for (int i = 1; i < n; ++i) {
            // 找到上一行的最小值、次小值及其列索引
            int min1 = INT_MAX, min2 = INT_MAX;
            int idx1 = -1;
            
            for (int j = 0; j < n; ++j) {
                if (dp[j] < min1) {
                    min2 = min1;
                    min1 = dp[j];
                    idx1 = j;
                } else if (dp[j] < min2) {
                    min2 = dp[j];
                }
            }
            
            // 计算当前行
            vector<int> new_dp(n);
            for (int j = 0; j < n; ++j) {
                if (j == idx1) {
                    new_dp[j] = grid[i][j] + min2;  // 与最小值冲突，用次小值
                } else {
                    new_dp[j] = grid[i][j] + min1;  // 无冲突，用最小值
                }
            }
            dp = move(new_dp);
        }
        
        return *min_element(dp.begin(), dp.end());
    }
};

class Solution3 {
public:
    int minFallingPathSum(vector<vector<int>>& grid) {
        int n = grid.size();
        // 处理特殊情况：只有一行
        if (n == 1) return grid[0][0];
        
        // 初始化上一行的最小值和次小值
        int first_min_sum = 0, second_min_sum = 0;
        int first_min_pos = -1;
        
        for (int i = 0; i < n; ++i) {
            // 当前行的最小值和次小值（初始化为最大值）
            int cur_first_min = INT_MAX, cur_second_min = INT_MAX;
            int cur_first_pos = -1;
            
            for (int j = 0; j < n; ++j) {
                // 计算当前位置的值：grid[i][j] + 上一行的合适最小值
                int cur_sum = (j == first_min_pos ? second_min_sum : first_min_sum) + grid[i][j];
                
                // 更新当前行的最小值和次小值
                if (cur_sum < cur_first_min) {
                    cur_second_min = cur_first_min;
                    cur_first_min = cur_sum;
                    cur_first_pos = j;
                } else if (cur_sum < cur_second_min) {
                    cur_second_min = cur_sum;
                }
            }
            
            // 更新上一行的信息
            first_min_sum = cur_first_min;
            second_min_sum = cur_second_min;
            first_min_pos = cur_first_pos;
        }
        
        return first_min_sum;
    }
};