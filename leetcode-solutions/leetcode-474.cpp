/*
Ones and Zeros

题目描述
给定 m 个数字 0 和 n 个数字 1，以及一些由 0-1 构成的字符串，求利用这些数字最多可以构
成多少个给定的字符串，字符串只可以构成一次。

题解
这是一个多维费用的 0-1 背包问题，有两个背包大小，0 的数量和 1 的数量。我们在这里直
接展示三维空间压缩到二维后的写法。
 */
#include <string>
#include <utility>
#include <vector>
using namespace std;

pair<int, int> count(const string &s) {
    int count0 = s.length(), count1 = 0;
    for (const char &c : s) {
        if (c == '1') {
            ++count1;
            --count0;
        }
    }
    return make_pair(count0, count1);
}

int findMaxForm(vector<string> &strs, int m, int n) {
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    for (const string &str : strs) {
        auto [count0, count1] = count(str);
        for (int i = m; i >= count0; --i) {
            for (int j = n; j >= count1; --j) {
                dp[i][j] = max(dp[i][j], 1 + dp[i - count0][j - count1]);
            }
        }
    }
    return dp[m][n];
}