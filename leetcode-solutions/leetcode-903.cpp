/*
 * Valid Permutations for DI Sequence
 *
 * We are given S, a length n string of characters from the set {'D', 'I'}.
 * (These letters stand for "decreasing" and "increasing".)
 *
 * A valid permutation is a permutation P[0], P[1], ..., P[n] of integers {0, 1, ..., n},
 * such that for all i:
 *
 * If S[i] == 'D', then P[i] > P[i+1], and;
 * If S[i] == 'I', then P[i] < P[i+1].
 *
 * How many valid permutations are there?  Since the answer may be large, return your answer modulo 10^9 + 7.
 *
 * Example 1:
 * Input: "DID"
 * Output: 5
 * Explanation:
 * The 5 valid permutations of (0, 1, 2, 3) are:
 * (1, 0, 3, 2)
 * (2, 0, 3, 1)
 * (2, 1, 3, 0)
 * (3, 0, 2, 1)
 * (3, 1, 2, 0)
 *
 * Note:
 * 1 <= S.length <= 200
 * S consists only of characters from the set {'D', 'I'}.
 */
#include <vector>
#include <string>
using namespace std;

class Solution1 {
 public:
  int numPermsDISequence(string S) {
    int n = S.size();
    int MOD = 1e9 + 7;
    // dp[i][j] 含义如上
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
    dp[0][0] = 1;

    for (int i = 1; i <= n; ++i) {
      for (int j = 0; j <= i; ++j) {
        if (S[i - 1] == 'I') {
          // 上升：累加所有 k < j 的情况
          for (int k = 0; k < j; ++k) {
            dp[i][j] = (dp[i][j] + dp[i - 1][k]) % MOD;
          }
        } else {
          // 下降：累加所有 k >= j 的情况 (注意 k 的范围是 0 到 i-1)
          for (int k = j; k < i; ++k) {
            dp[i][j] = (dp[i][j] + dp[i - 1][k]) % MOD;
          }
        }
      }
    }

    int ans = 0;
    for (int j = 0; j <= n; ++j) {
      ans = (ans + dp[n][j]) % MOD;
    }
    return ans;
  }
};

class Solution2 {
public:
    int numPermsDISequence(string S) {
        int n = S.size();
        int MOD = 1e9 + 7;
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
        dp[0][0] = 1;

        for (int i = 1; i <= n; ++i) {
            // 计算上一层的后缀和和前缀和
            vector<int> prefix(i, 0), suffix(i, 0);
            // 前缀和：pre[k] = sum(dp[i-1][0]...dp[i-1][k])
            prefix[0] = dp[i-1][0];
            for (int k = 1; k < i; ++k) {
                prefix[k] = (prefix[k-1] + dp[i-1][k]) % MOD;
            }
            // 后缀和：suf[k] = sum(dp[i-1][k]...dp[i-1][i-1])
            suffix[i-1] = dp[i-1][i-1];
            for (int k = i-2; k >= 0; --k) {
                suffix[k] = (suffix[k+1] + dp[i-1][k]) % MOD;
            }

            for (int j = 0; j <= i; ++j) {
                if (S[i - 1] == 'I') {
                    // 上升：sum_{k=0}^{j-1} dp[i-1][k]
                    if (j > 0) {
                        dp[i][j] = prefix[j-1];
                    } else {
                        dp[i][j] = 0;
                    }
                } else {
                    // 下降：sum_{k=j}^{i-1} dp[i-1][k]
                    if (j <= i-1) {
                        dp[i][j] = suffix[j];
                    } else {
                        // 当 j == i 时，k 从 i 到 i-1 是空集，为0
                        dp[i][j] = 0;
                    }
                }
            }
        }

        int ans = 0;
        for (int j = 0; j <= n; ++j) {
            ans = (ans + dp[n][j]) % MOD;
        }
        return ans;
    }
};

class Solution3 {
public:
    int numPermsDISequence(string S) {
        int n = S.size();
        int MOD = 1e9 + 7;
        vector<int> dp(n + 1, 0);
        // 初始化 i=0 的情况
        dp[0] = 1; // 长度为1的序列，最后一个数字是0（相对最小）

        for (int i = 1; i <= n; ++i) {
            vector<int> ndp(i + 1, 0); // 当前层的长度为 i+1
            if (S[i - 1] == 'I') {
                // 上升：dp[i][j] = sum_{k < j} dp[i-1][k]
                int sum = 0;
                for (int j = 0; j <= i; ++j) {
                    ndp[j] = sum;
                    // 注意：这里的 sum 要加上 dp[i-1][j] 为下一个 j+1 做准备
                    // 但 dp[i-1] 的有效索引只到 i-1，当 j == i 时，dp[i-1][j] 不存在
                    if (j < i) {
                        sum = (sum + dp[j]) % MOD;
                    }
                }
            } else {
                // 下降：dp[i][j] = sum_{k >= j} dp[i-1][k]
                int sum = 0;
                for (int j = i; j >= 0; --j) {
                    ndp[j] = sum;
                    // 累加 dp[i-1][j-1] 为下一个 j-1 做准备
                    if (j > 0) {
                        sum = (sum + dp[j - 1]) % MOD;
                    }
                }
            }
            dp = move(ndp); // 滚动
        }

        int ans = 0;
        for (int j = 0; j <= n; ++j) {
            ans = (ans + dp[j]) % MOD;
        }
        return ans;
    }
};