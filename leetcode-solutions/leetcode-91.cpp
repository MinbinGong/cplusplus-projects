/*
    Decode ways
    题目描述
        已知字母 A-Z 可以表示成数字 1-26。给定一个数字串，求有多少种不同的字符串等价于这个数字串。

    题解
        这是一道很经典的动态规划题，难度不大但是十分考验耐心。这是因为只有 1-26 可以表示字母，
    因此对于一些特殊情况，比如数字 0 或者当相邻两数字大于 26 时，需要有不同的状态转移方程，
 */
#include <string>
#include <vector>
using namespace std;

int numDecodings(string s) {
    if (s.empty()) {
        return 0;
    }

    int prev = s[0] - '0';
    if (prev == 0) {
        return 0;
    }

    int n = s.length();
    if (n == 1) {
        return 1;
    }

    vector<int> dp(n + 1, 1);
    for (int i = 2; i <= n; ++i) {
        int cur = s[i] - '0';
        if ((prev == 0 || prev > 2) && cur == 0) {
            return 0;
        }
        if ((prev < 2 && prev > 0) || prev == 2 && cur < 7) {
            if (cur) {
                dp[i] = dp[i - 2] + dp[i - 1];
            } else {
                dp[i] = dp[i - 2];
            }

        } else {
            dp[i] = dp[i - 1];
        }
        prev = cur;
    }
    return dp[n];
}