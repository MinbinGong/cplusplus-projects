/*
 * 1653. Minimum Deletions to Make String Balanced
 *
 * You are given a string s consisting only of characters 'a' and 'b'.
 * 
 * You can delete any number of characters in s to make s balanced. s is balanced if there is no pair of indices (i,j) such that i < j and s[i] = 'b' and s[j]= 'a'.
 * 
 * Return the minimum number of deletions needed to make s balanced.
 * 
 * Example 1:
 * Input: s = "aababbab"
 * Output: 2
 * Explanation: You can either:
 * Delete the characters at 0-indexed positions 2 and 6 ("aababbab" -> "aaabbb"), or
 * Delete the characters at 0-indexed positions 3 and 6 ("aababbab" -> "aabbbb").
 * 
 * Example 2:
 * Input: s = "bbaaaaabb"
 * Output: 2
 * Explanation: The only solution is to delete the first two characters.
 * 
 * Constraints:
 * 1 <= s.length <= 105
 * s[i] is 'a' or 'b'.
 * 
 */
#include <string>
using namespace std;

class Solution {
public:
    int minimumDeletions(string s) {
        int count_b = 0;      // 当前遍历到的 'b' 的个数
        int deletions = 0;    // 当前需要的最少删除次数
        for (char c : s) {
            if (c == 'b') {
                count_b++;
            } else { // c == 'a'
                // 遇到 'a' 时，有两种选择：
                // 1. 删除这个 'a'，删除次数 +1
                // 2. 删除之前所有的 'b'，使这个 'a' 前面没有 'b'
                // 取两者中的较小值
                deletions = min(deletions + 1, count_b);
            }
        }
        return deletions;
    }
};