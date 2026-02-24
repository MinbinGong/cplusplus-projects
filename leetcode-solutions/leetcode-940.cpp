/*
 * Distinct Subsequences II
 *
 * Given a string S, count the number of distinct, non-empty subsequences of S .
 *
 * Since the result may be large, return the answer modulo 10^9 + 7.
 *
 * Example 1:
 * Input: "abc"
 * Output: 7
 * Explanation: The 7 distinct subsequences are "a", "b", "c", "ab", "ac", "bc", and "abc".
 * 
 * Example 2:
 * Input: "aba"
 * Output: 6
 * Explanation: The 6 distinct subsequences are "a", "b", "ab", "ba", "aa" and "aba".
 * 
 * Example 3:
 * Input: "aaa"
 * Output: 3
 * Explanation: The 3 distinct subsequences are "a", "aa" and "aaa".
 * 
 * Note:
 * S contains only lowercase letters.
 * 1 <= S.length <= 2000
 * 
 */
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    int distinctSubseqII(string s) {
        const int MOD = 1e9 + 7;
        vector<long long> endsWith(26, 0);
        long long total = 0; // 维护当前所有不同子序列的总数
        
        for (char c : s) {
            int idx = c - 'a';
            long long newEndings = (total + 1) % MOD; // 以当前字符结尾的新增子序列
            total = (total + newEndings - endsWith[idx] + MOD) % MOD; // 更新总数
            endsWith[idx] = (endsWith[idx] + newEndings) % MOD; // 更新该字符结尾的计数
        }
        
        return total; // total 即为最终答案
    }
};