/*
 * Strange Printer
 *
 * There is a strange printer with the following two special requirements:
 *
 * The printer can only print a sequence of the same character each time.
 * At each turn, the printer can print new characters starting from and ending at any places, and will cover the original existing characters.
 *
 * Given a string consists of lower English letters only, your job is to count the minimum number of turns the printer needed in order to print it.
 *
 * Example 1:
 *
 * Input: "aaabbb"
 * Output: 2
 * Explanation: Print "aaa" first and then print "bbb".
 *
 * Example 2:
 *
 * Input: "aba"
 * Output: 2
 * Explanation: Print "aaa" first and then print "b" from the second place of the string, which will cover the existing character 'a'.
 *
 * Hint: Length of the given string will not exceed 100.
 * 
 * Note:
 *
 * The number of nodes in the given tree is between [1, 10^4].
 * Each node's value is between [-10^5, 10^5].
 * 
 */
#include <string>
#include <vector>
using namespace std;

class Solution1 {
public:
    int strangePrinter(string s) {
        int n = s.size();
        if (n == 0) return 0;
        
        // 预处理：去除相邻重复字符（优化）
        string t;
        for (char c : s) {
            if (t.empty() || c != t.back()) {
                t.push_back(c);
            }
        }
        s = t;
        n = s.size();
        
        vector<vector<int>> dp(n, vector<int>(n, 0));
        
        // 初始化：单个字符需要1次打印
        for (int i = 0; i < n; ++i) {
            dp[i][i] = 1;
        }
        
        // 区间DP：按长度从小到大枚举
        for (int len = 2; len <= n; ++len) {
            for (int i = 0; i + len - 1 < n; ++i) {
                int j = i + len - 1;
                
                // 情况1：最坏情况，最后一个字符单独打印
                dp[i][j] = dp[i][j-1] + 1;
                
                // 情况2：如果两端字符相同，最后一个可以伴随第一个一起打印
                if (s[i] == s[j]) {
                    dp[i][j] = min(dp[i][j], dp[i][j-1]);
                }
                
                // 情况3：枚举分割点，寻找合并机会
                for (int k = i; k < j; ++k) {
                    if (s[k] == s[j]) {
                        dp[i][j] = min(dp[i][j], dp[i][k] + dp[k+1][j-1]);
                    }
                }
            }
        }
        
        return dp[0][n-1];
    }
};

class Solution2 {
private:
    vector<vector<int>> memo;
    
    int dfs(const string& s, int i, int j) {
        if (i > j) return 0;
        if (i == j) return 1;
        if (memo[i][j] != 0) return memo[i][j];
        
        // 最坏情况
        int res = dfs(s, i, j-1) + 1;
        
        // 寻找合并机会
        for (int k = i; k < j; ++k) {
            if (s[k] == s[j]) {
                res = min(res, dfs(s, i, k) + dfs(s, k+1, j-1));
            }
        }
        
        return memo[i][j] = res;
    }
    
public:
    int strangePrinter(string s) {
        // 预处理去除相邻重复
        string t;
        for (char c : s) {
            if (t.empty() || c != t.back()) {
                t.push_back(c);
            }
        }
        
        int n = t.size();
        memo.assign(n, vector<int>(n, 0));
        return dfs(t, 0, n-1);
    }
};