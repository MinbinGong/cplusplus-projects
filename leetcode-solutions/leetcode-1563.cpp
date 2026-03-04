/**
 * 1563. Stone Game V
 * 
 * There are several stones arranged in a row, and each stone has an associated value which is an integer given in the array stoneValue.
 * 
 * In each round of the game, Alice divides the row into two non-empty rows (i.e. left row and right row), then Bob calculates the value of each row which is the sum of the values of all the stones in this row. Bob throws away the row which has the maximum value, and Alice's score increases by the value of the remaining row. If the value of the two rows are equal, Bob lets Alice decide which row will be thrown away. The next round starts with the remaining row.
 * 
 * The game ends when there is only one stone remaining. Alice's is initially zero.
 * 
 * Return the maximum score that Alice can obtain.
 * 
 * Example 1:
 * Input: stoneValue = [6,2,3,4,5,5]
 * Output: 18
 * Explanation:
 * Choose the triplet (6, 2, 3), Alice Pick the pile with 6 coins, you the pile with 2 coins and Bob the last one.
 * The score is 6 + 2 = 8.
 * Next round, choose the triplet (4, 5, 5), Alice Pick the pile with 4 coins, you the pile with 5 coins and Bob the last one.
 * The score is 4 + 5 = 9.
 * The game ends because only one stone is remaining.
 * 
 * Example 2:
 * Input: stoneValue = [7,7,7,7,7,7,7]
 * Output: 28
 * 
 * Example 3:
 * Input: stoneValue = [4]
 * Output: 0
 * 
 * Constraints:
 * 1 <= stoneValue.length <= 500
 * 1 <= stoneValue[i] <= 10^6
 * 
 */
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

class Solution1 {
public:
    int stoneGameV(vector<int>& stoneValue) {
        int n = stoneValue.size();
        vector<int> prefix(n + 1, 0);
        for (int i = 0; i < n; ++i)
            prefix[i + 1] = prefix[i] + stoneValue[i];

        vector<vector<int>> memo(n, vector<int>(n, 0));
        function<int(int, int)> dfs = [&](int i, int j) -> int {
            if (i == j) return 0;                 // 只剩一块石头
            if (memo[i][j] != 0) return memo[i][j];

            int total = prefix[j + 1] - prefix[i];
            int leftSum = 0;
            int ans = 0;
            for (int k = i; k < j; ++k) {
                leftSum += stoneValue[k];
                int rightSum = total - leftSum;

                if (leftSum < rightSum) {
                    // 保留左边，加左边和 + 递归左边
                    if (ans >= leftSum * 2) continue; // 剪枝优化
                    ans = max(ans, leftSum + dfs(i, k));
                } else if (leftSum > rightSum) {
                    // 保留右边，加右边和 + 递归右边
                    if (ans >= rightSum * 2) break;   // 剪枝优化
                    ans = max(ans, rightSum + dfs(k + 1, j));
                } else { // 相等，Alice 可以选择任意一边
                    ans = max(ans, leftSum + dfs(i, k));
                    ans = max(ans, rightSum + dfs(k + 1, j));
                }
            }
            return memo[i][j] = ans;
        };

        return dfs(0, n - 1);
    }
};

class Solution2 {
public:
    int stoneGameV(vector<int>& stoneValue) {
        int n = stoneValue.size();
        vector<int> prefix(n + 1, 0);
        for (int i = 0; i < n; ++i)
            prefix[i + 1] = prefix[i] + stoneValue[i];

        vector<vector<int>> dp(n, vector<int>(n, 0));

        for (int len = 2; len <= n; ++len) {               // 区间长度
            for (int i = 0; i + len - 1 < n; ++i) {
                int j = i + len - 1;
                for (int k = i; k < j; ++k) {               // 枚举分割点
                    int leftSum  = prefix[k + 1] - prefix[i];
                    int rightSum = prefix[j + 1] - prefix[k + 1];

                    if (leftSum < rightSum) {
                        dp[i][j] = max(dp[i][j], leftSum + dp[i][k]);
                    } else if (leftSum > rightSum) {
                        dp[i][j] = max(dp[i][j], rightSum + dp[k + 1][j]);
                    } else { // leftSum == rightSum
                        dp[i][j] = max(dp[i][j], leftSum + dp[i][k]);
                        dp[i][j] = max(dp[i][j], rightSum + dp[k + 1][j]);
                    }
                }
            }
        }
        return dp[0][n - 1];
    }
};

class Solution3 {
public:
    int stoneGameV(vector<int>& stoneValue) {
        int n = stoneValue.size();
        if (n == 1) return 0;

        vector<int> prefix(n + 1, 0);
        for (int i = 0; i < n; ++i)
            prefix[i + 1] = prefix[i] + stoneValue[i];

        vector<vector<int>> dp(n, vector<int>(n, 0));
        vector<vector<int>> dp2(n, vector<int>(n, 0)); // dp2[i][j] = max(dp[i][k] + sum[i..k]) for k in [i, j]
        vector<vector<int>> dp3(n, vector<int>(n, 0)); // dp3[i][j] = max(dp[k][j] + sum[k..j]) for k in [i, j]

        for (int i = 0; i < n; ++i) {
            dp2[i][i] = stoneValue[i];
            dp3[i][i] = stoneValue[i];
        }

        for (int len = 2; len <= n; ++len) {
            for (int i = 0; i + len - 1 < n; ++i) {
                int j = i + len - 1;
                int total = prefix[j + 1] - prefix[i];

                // 使用双指针找到最佳分割点
                int best = 0;
                int leftSum = 0;
                int mid = i;
                while (mid < j && (leftSum + stoneValue[mid]) * 2 <= total) {
                    leftSum += stoneValue[mid];
                    ++mid;
                }

                // 情况1：左半和 <= 右半和
                if (mid - 1 >= i) {
                    best = max(best, dp2[i][mid - 1]);
                }
                // 情况2：左半和 == 右半和（恰好相等时，需要额外判断）
                if (mid < j && (leftSum + stoneValue[mid]) * 2 == total) {
                    best = max(best, dp[i][mid] + total / 2);
                    best = max(best, dp[mid + 1][j] + total / 2);
                    ++mid;
                }
                // 情况3：左半和 > 右半和
                if (mid <= j) {
                    best = max(best, dp3[mid][j]);
                }

                dp[i][j] = best;

                // 更新辅助数组
                dp2[i][j] = max(dp2[i][j - 1], dp[i][j] + total);
                dp3[i][j] = max(dp3[i + 1][j], dp[i][j] + total);
            }
        }
        return dp[0][n - 1];
    }
};
