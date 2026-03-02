/**
 * 1371. Find the Longest Substring Containing Vowels in Even Counts
 *
 * Given the string s, return the size of the longest substring containing each vowel an even number of times. That is, 'a', 'e', 'i', 'o', and 'u' must appear an even number of times.
 * 
 * Example 1:
 * Input: s = "eleetminicoworoep"
 * Output: 13
 * Explanation: The longest substring is "leetminicowor" which contains two each of the vowels: e, i and o and zero of the vowels: a and u.
 * 
 * Example 2:
 * Input: s = "leetcodeisgreat"
 * Output: 5
 * Explanation: The longest substring is "leetc" which contains two e's.
 * 
 * Example 3:
 * Input: s = "bcbcbc"
 * Output: 6
 * Explanation: In this case, s is the longest substring.
 * 
 * Note:
 * 1 <= s.length <= 5 x 10^5
 * s contains only lowercase English letters.
 * 
 */
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Solution {
public:
    int findTheLongestSubstring(string s) {
        // 状态压缩：用5位二进制表示a,e,i,o,u的奇偶性（1表示奇数，0表示偶数）
        vector<int> firstOccur(1 << 5, -2); // -2 表示未出现
        firstOccur[0] = -1; // 初始状态（全偶）出现在位置 -1
        int state = 0;
        int ans = 0;
        for (int i = 0; i < s.size(); ++i) {
            // 根据当前字符翻转对应位
            char c = s[i];
            switch (c) {
                case 'a': state ^= 1 << 0; break;
                case 'e': state ^= 1 << 1; break;
                case 'i': state ^= 1 << 2; break;
                case 'o': state ^= 1 << 3; break;
                case 'u': state ^= 1 << 4; break;
                default: break;
            }
            if (firstOccur[state] == -2) {
                // 第一次遇到该状态，记录位置
                firstOccur[state] = i;
            } else {
                // 之前遇到过，中间这段子串的元音均为偶数
                ans = max(ans, i - firstOccur[state]);
            }
        }
        return ans;
    }
};