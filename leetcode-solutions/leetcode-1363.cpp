/**
 * 1363. Largest Multiple of Three
 *
 * Given an array of digits digits, return the largest multiple of three that can be formed by concatenating some of the given digits in any order. If there is no answer return an empty string.
 *
 * Since the answer may not fit in an integer data type, return the answer as a string. Note that the returning answer must not contain unnecessary leading zeros.
 * 
 * Example 1:
 * Input: digits = [8,1,9]
 * Output: "981"
 * 
 * Example 2:
 * Input: digits = [8,6,7,1,0]
 * Output: "8760"
 * 
 * Example 3:
 * Input: digits = [1]
 * Output: ""
 * 
 * Note:
 * 1 <= digits.length <= 10^4
 * 0 <= digits[i] <= 9
 * 
 */
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Solution1 {
public:
    string largestMultipleOfThree(vector<int>& digits) {
        vector<int> cnt(10, 0); // 统计0-9每个数字出现的次数
        int sum = 0;
        for (int d : digits) {
            cnt[d]++;
            sum += d;
        }

        int remainder = sum % 3;

        // 需要删除的数字类型及数量
        if (remainder == 1) {
            // 尝试删除1个余1的（1,4,7）
            if (!removeOne(cnt, 1, 4, 7)) {
                // 如果失败，尝试删除2个余2的（2,5,8）
                removeTwo(cnt, 2, 5, 8);
            }
        } else if (remainder == 2) {
            // 尝试删除1个余2的（2,5,8）
            if (!removeOne(cnt, 2, 5, 8)) {
                // 如果失败，尝试删除2个余1的（1,4,7）
                removeTwo(cnt, 1, 4, 7);
            }
        }

        // 构建结果字符串
        string res;
        for (int i = 9; i >= 0; --i) {
            res += string(cnt[i], '0' + i);
        }

        // 处理前导零和空串的情况
        if (res.empty() || res[0] == '0') return res.empty() ? "" : "0";
        return res;
    }

private:
    // 尝试删除一个特定余数的数字，返回是否成功
    bool removeOne(vector<int>& cnt, int a, int b, int c) {
        if (cnt[a] > 0) { cnt[a]--; return true; }
        if (cnt[b] > 0) { cnt[b]--; return true; }
        if (cnt[c] > 0) { cnt[c]--; return true; }
        return false;
    }

    // 尝试删除两个特定余数的数字
    void removeTwo(vector<int>& cnt, int a, int b, int c) {
        for (int i = 0; i < 2; ++i) {
            if (cnt[a] > 0) { cnt[a]--; continue; }
            if (cnt[b] > 0) { cnt[b]--; continue; }
            if (cnt[c] > 0) { cnt[c]--; continue; }
        }
    }
};

class Solution2 {
public:
    string largestMultipleOfThree(vector<int>& digits) {
        sort(digits.begin(), digits.end()); // 升序排序
        int n = digits.size();
        // dp[i][j] 考虑前i个数，余数为j的最大个数，初始化为负无穷
        vector<vector<int>> dp(n + 1, vector<int>(3, INT_MIN));
        dp[0][0] = 0;

        for (int i = 1; i <= n; ++i) {
            int d = digits[i-1];
            int mod = d % 3;
            for (int j = 0; j < 3; ++j) {
                dp[i][j] = max(dp[i-1][j], dp[i-1][(j - mod + 3) % 3] + 1);
            }
        }

        if (dp[n][0] <= 0) return ""; // 无解

        // 回溯找出选的数字
        string res;
        for (int i = n, j = 0; i > 0; --i) {
            int d = digits[i-1];
            int mod = d % 3;
            // 检查是否选了当前数字（即从哪个状态转移而来）
            if (dp[i][j] == dp[i-1][(j - mod + 3) % 3] + 1) {
                res += (d + '0');
                j = (j - mod + 3) % 3;
            }
        }

        // 处理前导零
        if (res.empty()) return "";
        int idx = 0;
        while (idx < res.size() - 1 && res[idx] == '0') ++idx;
        return res.substr(idx);
    }
};