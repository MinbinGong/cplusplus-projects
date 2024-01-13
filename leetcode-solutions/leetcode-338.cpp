/*
Counting Bits

题目描述
给定一个非负整数 n，求从 0 到 n 的所有数字的二进制表达中，分别有多少个 1。


 */

#include <vector>
using namespace std;

vector<int> countBits(int num) {
    if (num == 0) return {0};
    vector<int> dp(num + 1, 0);
    dp[0] = 0;
    dp[1] = 1;
    for (int i = 2; i <= num; i++) {
        if (i & 1)
            dp[i] = dp[i >> 1] + 1;  // i&1 is bitwise AND which is used to check whether last bit is 1 or not.
        else
            dp[i] = dp[i >> 1];
    }
    return dp;
}

vector<int> countBits1(int num) {
    vector<int> dp(num + 1, 0);
    for (int i = 1; i <= num; ++i) {
        dp[i] = i & 1 ? dp[i - 1] + 1 : dp[i >> 1];
    }
    return dp;
}