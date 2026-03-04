/*
 * 1573. Number of Ways to Split a String
 * 
 * Given a binary string s, you can split s into 3 non-empty strings s1, s2, and s3 where s1 + s2 + s3 = s.
 * 
 * Return the number of ways s can be split such that the number of ones is the same in s1, s2, and s3. Since the answer may be too large, return it modulo 10^9 + 7.
 * 
 * Example 1:
 * Input: s = "10101"
 * Output: 4
 * Explanation: There are four ways to split s in 3 parts where each part contain the same number of letters '1'.
 * "1|010|1"
 * "1|01|01"
 * "10|10|1"
 * "10|1|01"
 * 
 * Example 2:
 * Input: s = "1001"
 * Output: 0
 * 
 * Example 3:
 * Input: s = "0000"
 * Output: 3
 * Explanation: There are three ways to split s in 3 parts.
 * "0|0|00"
 * "0|00|0"
 * "00|0|0"
 * 
 * Constraints:
 * 3 <= s.length <= 10^5
 * s[i] is either '0' or '1'.
 * 
 */
#include <string>
using namespace std;

class Solution {
public:
    int numWays(string s) {
        const int MOD = 1e9 + 7;
        int n = s.size();
        int total = 0;
        for (char c : s) {
            if (c == '1') total++;
        }
        // 如果不能均分，直接返回0
        if (total % 3 != 0) return 0;
        
        // 全零字符串的情况
        if (total == 0) {
            // 在 n-1 个间隔中选择两个位置分割
            long long ways = (long long)(n - 1) * (n - 2) / 2 % MOD;
            return ways;
        }
        
        int k = total / 3;          // 每段应有的1的个数
        int cnt1 = 0, cnt2 = 0;     // 第一段和第二段结束位置的可能个数
        int pref = 0;                // 当前前缀中1的个数
        
        for (char c : s) {
            if (c == '1') pref++;
            if (pref == k) cnt1++;           // 可能的第一段结束位置
            else if (pref == 2 * k) cnt2++;   // 可能的第二段结束位置
        }
        
        long long ans = (long long)cnt1 * cnt2 % MOD;
        return ans;
    }
};