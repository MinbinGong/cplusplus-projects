/*
Count Binary Substrings

题目描述
给定一个 0-1 字符串，求有多少非空子字符串的 0 和 1 数量相同。

题解
从左往右遍历数组，记录和当前位置数字相同且连续的长度，以及其之前连续的不同数字的
长度。举例来说，对于 00110 的最后一位，我们记录的相同数字长度是 1，因为只有一个连续 0；
我们记录的不同数字长度是 2，因为在 0 之前有两个连续的 1。若不同数字的连续长度大于等于
当前数字的连续长度，则说明存在一个且只存在一个以当前数字结尾的满足条件的子字符串。
 */
#include <string>
using namespace std;

int countBinarySubstrings(string s) {
    int pre = 0, cur = 1, count = 0;
    for (int i = 1; i < s.length(); ++i) {
        if (s[i] == s[i - 1]) {
            ++cur;
        } else {
            pre = cur;
            cur = 1;
        }

        if (pre >= cur) {
            ++count;
        }
    }
    return count;
}