/*
 * Numbers At Most N Given Digit Set
 *
 * We have a sorted set of digits D, a non-empty subset of {'1','2','3','4','5','6','7','8','9'}.
 * (Note that '0' is not included.)
 *
 * Now, we write numbers using these digits, using each digit as many times as we want.
 * For example, if D = {'1','3','5'}, we may write numbers such as '13', '551', '1351315'.
 *
 * Return the number of positive integers that can be written (using the digits of D) that are less than or equal to N.
 *
 * Example 1:
 * Input: D = {"1","3","5","7"}, N = 100
 * Output: 20
 * Explanation: 
 * The 20 numbers that can be written are:
 * 1, 3, 5, 7, 11, 13, 15, 17, 31, 33, 35, 37, 51, 53, 55, 57, 71, 73, 75, 77.
 * 
 * Example 2:
 * Input: D = {"1","4","9"}, N = 1000000000
 * Output: 29523
 * Explanation: 
 * We can write 3 one digit numbers, 9 two digit numbers, 27 three digit numbers,
 * 81 four digit numbers, 243 five digit numbers, 729 six digit numbers,
 * 2187 seven digit numbers, 6561 eight digit numbers, and 19683 nine digit numbers.
 * In total, this is 29523 integers that can be written using the digits of D.
 * 
 * Note:
 * D is a subset of digits '1'-'9' in sorted order.
 * 1 <= N <= 10^9
 */
#include <vector>
#include <cmath>
#include <functional>
#include <string>
using namespace std;

class Solution1 {
public:
    int atMostNGivenDigitSet(vector<string>& digits, int n) {
        string s = to_string(n);          // 将 n 转为字符串，方便逐位处理
        int len = s.size();                // n 的位数
        int m = digits.size();              // 可用数字的个数
        int ans = 0;

        // 1. 统计所有位数小于 len 的数字
        // 例如 n 是 3 位数，那么所有 1 位数和 2 位数都一定小于 n
        for (int i = 1; i < len; i++) {
            ans += pow(m, i);
        }

        // 2. 统计位数等于 len 的数字（需要逐位与 n 比较）
        for (int i = 0; i < len; i++) {
            bool hasSame = false;           // 标记当前位是否找到了与 s[i] 相等的数字
            for (string& d : digits) {
                if (d[0] < s[i]) {
                    // 如果 digits 中的数字小于 n 的当前位
                    // 那么剩余位置可以任意填所有 m 个数字
                    ans += pow(m, len - i - 1);
                } else if (d[0] == s[i]) {
                    // 如果相等，则当前位固定为这个数字，继续检查下一位
                    hasSame = true;
                } else {
                    // digits 有序，遇到大于的就可以直接跳出循环
                    break;
                }
            }
            // 如果当前位没有找到与 s[i] 相等的数字，说明后续所有构造都会超过 n，直接返回
            if (!hasSame) {
                return ans;
            }
        }
        // 3. 如果循环顺利结束，说明 n 本身可以被构造出来，因此需要加上 n 本身
        return ans + 1;
    }
};

class Solution2 {
public:
    int atMostNGivenDigitSet(vector<string>& digits, int n) {
        string s = to_string(n);
        int m = s.size();
        vector<int> nums;
        for (auto& d : digits) {
            nums.push_back(stoi(d));
        }

        // dp 数组: dp[i][isLimit][isNum]
        // i: 当前处理到第几位 (从0开始)
        // isLimit: 当前是否受到 n 的约束 (即前缀是否与 n 相等)
        // isNum: 当前是否已经开始构造数字 (用于处理前导零)
        vector<vector<vector<int>>> memo(m, vector<vector<int>>(2, vector<int>(2, -1)));

        // 深度优先搜索函数
        function<int(int, bool, bool)> dfs = [&](int i, bool isLimit, bool isNum) -> int {
            if (i == m) {
                // 如果已经构造完所有位，并且确实构造了数字（isNum 为 true），则返回 1 表示一种有效构造
                return isNum ? 1 : 0;
            }
            if (memo[i][isLimit][isNum] != -1) {
                return memo[i][isLimit][isNum];
            }

            int res = 0;
            // 如果之前还没有构造数字，可以跳过当前位 (继续不选)
            if (!isNum) {
                res += dfs(i + 1, false, false);
            }

            // 确定当前位可以选择的数字的上限
            int up = isLimit ? (s[i] - '0') : 9;
            // 从第一个数字开始尝试填入
            for (int d : nums) {
                if (d > up) break; // 超过了上限，后面的更大，直接跳出
                // 当前位可以填入 d
                // 新的 isLimit 取决于之前的 isLimit 和当前是否正好等于上限
                // 新的 isNum 自然为 true
                res += dfs(i + 1, isLimit && (d == up), true);
            }

            memo[i][isLimit][isNum] = res;
            return res;
        };

        return dfs(0, true, false);
    }
};