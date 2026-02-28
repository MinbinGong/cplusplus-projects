/**
 * 1220. Count Vowels Permutation
 *
 * Given an integer n, your task is to count how many strings of length n can be formed under the following rules:
 *
 * Each character is a lower case vowel ('a', 'e', 'i', 'o', 'u')
 * Each vowel 'a' may only be followed by an 'e'.
 * Each vowel 'e' may only be followed by an 'a' or an 'i'.
 * Each vowel 'i' may not be followed by another 'i'.
 * Each vowel 'o' may only be followed by an 'i' or a 'u'.
 * Each vowel 'u' may only be followed by an 'a'.
 * Since the answer may be too large, return it modulo 10^9 + 7.
 *
 *
 *
 * Example 1:
 *
 * Input: n = 1
 * Output: 5
 * Explanation: All possible strings are: "a", "e", "i" , "o" and "u".
 *
 * Example 2:
 *
 * Input: n = 2
 * Output: 10
 * Explanation: All possible strings are: "ae", "ea", "ei", "ia", "ie", "io", "iu", "oi", "ou" and "ua".
 *
 * Example 3:
 *
 * Input: n = 5
 * Output: 68
 *
 *
 * Constraints:
 *
 * 1 <= n <= 2 * 10^4
 *
 */
#include <vector>

class Solution1 {
public:
    int countVowelPermutation(int n) {
        const int MOD = 1e9 + 7;
        // 元音映射：0-a, 1-e, 2-i, 3-o, 4-u
        // dp[i][j] 表示长度为i的字符串以第j个元音结尾的个数
        std::vector<std::vector<long long>> dp(n + 1, std::vector<long long>(5, 0));
        
        // 初始化：长度为1的字符串
        for (int j = 0; j < 5; ++j) {
            dp[1][j] = 1;
        }
        
        // 动态规划
        for (int i = 2; i <= n; ++i) {
            // a 前面只能是 e, i, u
            dp[i][0] = (dp[i-1][1] + dp[i-1][2] + dp[i-1][4]) % MOD;
            // e 前面只能是 a, i
            dp[i][1] = (dp[i-1][0] + dp[i-1][2]) % MOD;
            // i 前面只能是 e, o
            dp[i][2] = (dp[i-1][1] + dp[i-1][3]) % MOD;
            // o 前面只能是 i
            dp[i][3] = dp[i-1][2] % MOD;
            // u 前面只能是 i, o
            dp[i][4] = (dp[i-1][2] + dp[i-1][3]) % MOD;
        }
        
        // 计算总和
        long long result = 0;
        for (int j = 0; j < 5; ++j) {
            result = (result + dp[n][j]) % MOD;
        }
        
        return result;
    }
};

// 优化版：使用滚动数组
class Solution2 {
public:
    int countVowelPermutation(int n) {
        const int MOD = 1e9 + 7;
        std::vector<long long> dp(5, 1);  // 长度为1的情况
        std::vector<long long> ndp(5, 0);
        
        for (int i = 2; i <= n; ++i) {
            ndp[0] = (dp[1] + dp[2] + dp[4]) % MOD;
            ndp[1] = (dp[0] + dp[2]) % MOD;
            ndp[2] = (dp[1] + dp[3]) % MOD;
            ndp[3] = dp[2] % MOD;
            ndp[4] = (dp[2] + dp[3]) % MOD;
            dp = ndp;
        }
        
        long long result = 0;
        for (int j = 0; j < 5; ++j) {
            result = (result + dp[j]) % MOD;
        }
        return result;
    }
};
