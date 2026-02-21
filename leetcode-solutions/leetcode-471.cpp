/*
 * Encode and Decode Strings
 *
 * Design an algorithm to encode a list of strings to a string. The encoded string is then sent over the network and is decoded back to the original list of strings.
 *
 * Constraints:
 * 1 <= strs.length <= 200
 * 0 <= strs[i].length <= 200
 * strs[i] contains any possible characters out of 256 valid ASCII characters.
 * 
 */
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    string encode(string s) {
        int n = s.size();
        // dp[i][j] 表示子串 s[i...j] 的最短编码
        vector<vector<string>> dp(n, vector<string>(n, ""));

        // 区间DP，从小到大枚举区间长度
        for (int len = 1; len <= n; ++len) {
            for (int i = 0; i + len - 1 < n; ++i) {
                int j = i + len - 1;
                string substr = s.substr(i, len);
                dp[i][j] = substr; // 初始化为原串

                // 1. 尝试将当前子串压缩成重复模式 k[encoded]
                // 只有当长度大于4时才可能压缩得更短（例如 "5[a]" 比 "aaaaa" 短）
                if (len > 4) {
                    // 技巧：在 substr+substr 中查找 substr 的第二次出现位置
                    // 这个位置就是循环节的长度
                    int repeatPos = (substr + substr).find(substr, 1);
                    if (repeatPos < substr.size()) {
                        int cycleLen = repeatPos;                 // 循环节长度
                        int repeatCnt = len / cycleLen;           // 重复次数
                        // 注意：循环节内部的编码要用已经计算好的 dp[i][i+cycleLen-1]
                        string encoded = to_string(repeatCnt) + "[" + dp[i][i + cycleLen - 1] + "]";
                        if (encoded.size() < dp[i][j].size()) {
                            dp[i][j] = encoded;
                        }
                    }
                }

                // 2. 尝试将当前子串分割成左右两部分拼接
                for (int k = i; k < j; ++k) {
                    string combined = dp[i][k] + dp[k + 1][j];
                    if (combined.size() < dp[i][j].size()) {
                        dp[i][j] = combined;
                    }
                }
            }
        }
        return dp[0][n - 1];
    }
};