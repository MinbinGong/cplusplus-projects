/**
 * 1446. Consecutive Characters
 * 
 * Given a string s, the power of the string is the maximum length of a non-empty substring that contains only one unique character.
 * 
 * Return the power of the string.
 * 
 * Example 1:
 * 
 * Input: s = "leetcode"
 * Output: 2
 * Explanation: The substring "ee" is of length 2 with the character 'e' only.
 * 
 * Example 2:
 * 
 * Input: s = "abbcccddddeeeeedcba"
 * Output: 5
 * Explanation: The substring "eeeee" is of length 5 with the character 'e' only.
 * 
 * Example 3:
 * 
 * Input: s = "triplepillooooow"
 * Output: 5
 * Explanation: The substring "ooooo" is of length 5 with the character 'o' only.
 * 
 * Example 4:
 * 
 * Input: s = "hooraaaaaaaaaaay"
 * Output: 11
 * Explanation: The substring "aaaaaaaaaa" is of length 11 with the character 'a' only.
 * 
 * Example 5:
 * 
 * Input: s = "tourist"
 * Output: 1
 * Explanation: The substring "t" is of length 1 with the character 't' only.
 * 
 * Note:
 * 1 <= s.length <= 500
 * s contains only lowercase English letters.
 * 
 */
#include <string>
using namespace std;

class Solution {
public:
    int maxPower(string s) {
        int maxLen = 1;   // 至少有一个字符
        int curLen = 1;   // 当前连续相同字符的长度
        for (int i = 1; i < s.length(); ++i) {
            if (s[i] == s[i - 1]) {
                ++curLen;
                maxLen = max(maxLen, curLen);
            } else {
                curLen = 1;
            }
        }
        return maxLen;
    }
};
