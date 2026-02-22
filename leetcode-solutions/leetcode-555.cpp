/*
 * Split Concatenated Strings
 *
 * Given a list of strings, you could concatenate these strings together into a loop, where for each string you could choose to reverse it or not. Among all the possible loops, you need to find the lexicographically biggest string after cutting the loop, which will make the looped string into a regular one.
 * 
 * Specifically, to find the lexicographically biggest string, you need to experience two phases:
 * 
 * Concatenate all the strings into a loop, where you can reverse some strings or not and connect them in the same order as given.
 * Cut and make one breakpoint in any place of the loop, which will make the looped string into a regular one starting from the character at the cutpoint.
 * 
 * And your job is to find the lexicographically biggest one among all the possible regular strings.
 * 
 * Note:
 * The input strings will only contain lowercase letters.
 * The total length of all the strings will not over 1,000.
 * 
 * Example:
 * Input: "abc", "xyz"
 * Output: "zyxcba"
 * 
 */
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Solution {
public:
    string splitLoopedString(vector<string>& strs) {
        int n = strs.size();
        // 1. 预处理：每个字符串取自己和反转后较大的那个
        for (string& s : strs) {
            string rev = s;
            reverse(rev.begin(), rev.end());
            if (rev > s) { // 如果反转后更大，则替换
                s = rev;
            }
        }

        string ans; // 初始为空，后续会更新

        // 2. 枚举每个字符串作为切割点所在的字符串
        for (int i = 0; i < n; ++i) {
            string s = strs[i];
            string rev_s = s;
            reverse(rev_s.begin(), rev_s.end());

            // 构造除当前字符串外，其他字符串的组合部分（注意顺序）
            string rest;
            for (int j = i + 1; j < n; ++j) {
                rest += strs[j];
            }
            for (int j = 0; j < i; ++j) {
                rest += strs[j];
            }

            // 3. 尝试当前字符串的两种形式：原序和反序
            for (const string& cur : {s, rev_s}) {
                // 4. 枚举切割位置
                for (int k = 0; k <= cur.size(); ++k) {
                    // 切割点右边部分 + 其他字符串 + 切割点左边部分
                    string candidate = cur.substr(k) + rest + cur.substr(0, k);
                    // 更新答案
                    if (candidate > ans) {
                        ans = candidate;
                    }
                }
            }
        }

        return ans;
    }
};