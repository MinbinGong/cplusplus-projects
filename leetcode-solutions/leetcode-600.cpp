/*
 * Non-negative Integers without Consecutive Ones
 * 
 * Given a positive integer n, return the number of the integers in the range [0, n] whose binary representations do not contain consecutive ones.
 * 
 * Example 1:
 * Input: n = 5
 * Output: 5
 * Explanation:
 * Here are the non-negative integers <= 5 with their corresponding binary representations:
 * 0 : 0
 * 1 : 1
 * 2 : 10
 * 3 : 11
 * 4 : 100
 * 5 : 101
 * Among them, only integer 3 disobeys the rule (two consecutive ones) and the other 5 satisfy the rule. 
 * 
 * Example 2:
 * Input: n = 1
 * Output: 2
 * 
 * Example 3:
 * Input: n = 2
 * Output: 3
 * 
 * Constraints:
 * 1 <= n <= 109
 * 
 */
#include <vector>
#include <functional>
using namespace std;

class Solution1 {
public:
    int findIntegers(int n) {
        // 将 n 转为二进制数组，a[1] 是最低位
        vector<int> a;
        while (n) {
            a.push_back(n & 1);
            n >>= 1;
        }
        int len = a.size();
        
        // dp[pos][pre] 表示在不受限情况下，位置 pos 且上一位为 pre 时的合法个数
        vector<vector<int>> dp(len, vector<int>(2, -1));
        
        // pos: 当前处理到的位数（从高位到低位，索引从 len-1 到 0）
        // pre: 上一位选的值（0 或 1）
        // limit: 当前是否受到 n 的限制
        function<int(int, int, bool)> dfs = [&](int pos, int pre, bool limit) -> int {
            if (pos < 0) return 1; // 成功构造一个合法数
            
            if (!limit && dp[pos][pre] != -1) return dp[pos][pre];
            
            int up = limit ? a[pos] : 1; // 当前位可取的最大值
            int ans = 0;
            
            for (int i = 0; i <= up; ++i) {
                if (pre == 1 && i == 1) continue; // 连续 1，剪枝
                ans += dfs(pos - 1, i, limit && (i == up));
            }
            
            if (!limit) dp[pos][pre] = ans;
            return ans;
        };
        
        return dfs(len - 1, 0, true);
    }
};

class Solution2 {
public:
    int findIntegers(int n) {
        // 预计算斐波那契数组，长度到 32 足够（n ≤ 1e9 < 2^30）
        vector<int> fib(32, 0);
        fib[0] = 1;
        fib[1] = 2;
        for (int i = 2; i < 32; ++i) {
            fib[i] = fib[i-1] + fib[i-2];
        }
        
        int ans = 0;
        int prevBit = 0; // 记录上一位
        
        // 从高位向低位遍历（30 到 0 是因为 2^30 > 1e9）
        for (int i = 30; i >= 0; --i) {
            if (n & (1 << i)) { // 当前位是 1
                ans += fib[i];   // 累加当前位取 0 时的合法数
                if (prevBit) {    // 出现连续 1，直接返回
                    return ans;
                }
                prevBit = 1;
            } else {
                prevBit = 0;
            }
        }
        // 加上 n 自身（若它合法）
        return ans + 1;
    }
};