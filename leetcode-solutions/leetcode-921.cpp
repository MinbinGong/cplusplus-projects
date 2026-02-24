/*
 * Minimum Add to Make Parentheses Valid
 *
 * A parentheses string is valid if and only if:
 *
 * It is the empty string,
 * It can be written as AB (A concatenated with B), where A and B are valid strings, or
 * It can be written as (A), where A is a valid string.
 * Given a parentheses string s, return the minimum number of parentheses we must add to make the resulting string valid.
 *
 * Example 1:
 * Input: s = "())"
 * Output: 1
 *
 * Example 2:
 * Input: s = "((("
 * Output: 3
 *
 * Note:
 * 1 <= s.length <= 1000
 * s[i] is either '(' or ')'.
 *
 */
class Solution {
public:
    int minAddToMakeValid(string s) {
        int ans = 0, bal = 0;
        for (char c : s) {
            if (c == '(') {
                bal++;
            } else {
                if (bal > 0) bal--;
                else ans++;
            }
        }
        return ans + bal;
    }
};