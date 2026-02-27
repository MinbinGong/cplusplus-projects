/**
 * 1067. Digit Count in Range
 * 
 * Given an integer d between 0 and 9, and two positive integers low and high as lower and upper bounds, respectively. Return the number of times that d occurs as a digit in all integers between low and high, including the bounds low and high.
 * 
 * 
 * Example 1:
 * Input: d = 1, low = 1, high = 13
 * Output: 6
 * Explanation: 
 * The digit d=1 occurs 6 times in 1,10,11,12,13. Note that the digit d=1 occurs twice in the number 11.
 * 
 * Example 2:
 * Input: d = 3, low = 100, high = 250
 * Output: 35
 * Explanation: 
 * The digit d=3 occurs 35 times in 103,113,123,130,131,...,238,239,243.
 * 
 * Note:
 * 0 <= d <= 9
 * 1 <= low <= high <= 2×10^8
 * 
 */
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    int digitsCount(int d, int low, int high) {
        // 计算 [0, high] 中 d 的出现次数减去 [0, low-1] 的出现次数
        return count(high, d) - count(low - 1, d);
    }

private:
    // 返回 [0, n] 中数字 d 出现的次数
    int count(int n, int d) {
        if (n < 0) return 0;
        string s = to_string(n);
        int len = s.size();
        // 记忆化数组：memo[pos][cnt][tight][leading]
        // pos 当前处理到的位数，cnt 已出现的次数，tight 是否受上限约束，leading 是否有前导零
        vector<vector<vector<vector<int>>>> memo(len,
            vector<vector<vector<int>>>(len + 1,
                vector<vector<int>>(2, vector<int>(2, -1))));

        function<int(int, int, bool, bool)> dfs = [&](int pos, int cnt, bool tight, bool leading) -> int {
            if (pos == len) return cnt;                     // 遍历完所有位，返回累计次数
            if (memo[pos][cnt][tight][leading] != -1) 
                return memo[pos][cnt][tight][leading];

            int up = tight ? s[pos] - '0' : 9;               // 当前位可选的最大数字
            int res = 0;
            for (int dig = 0; dig <= up; ++dig) {
                bool newTight = tight && (dig == up);
                bool newLeading = leading && (dig == 0);
                int newCnt = cnt;
                if (d == 0) {
                    // 数字0不能算前导零
                    if (!newLeading && dig == 0) newCnt++;
                } else {
                    if (dig == d) newCnt++;
                }
                res += dfs(pos + 1, newCnt, newTight, newLeading);
            }
            return memo[pos][cnt][tight][leading] = res;
        };

        return dfs(0, 0, true, true);
    }
};
