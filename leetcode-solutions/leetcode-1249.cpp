/*
 * 1249. Minimum Remove to Make Valid Parentheses
 *
 * Given a string s of '(' , ')' and lowercase English characters. 
 *
 * Your task is to remove the minimum number of parentheses ( '(' or ')', in any positions ) so that the resulting parentheses string is valid and return any valid string.
 *
 * Formally, a parentheses string is valid if and only if:
 *
 * It is the empty string, contains only lowercase characters, or
 * It can be written as AB (A concatenated with B), where A and B are valid strings, or
 * It can be written as (A), where A is a valid string.
 *
 * Example 1:
 * Input: s = "lee(t(c)o)de)"
 * Output: "lee(t(c)o)de"
 * Explanation: "lee(t(co)de)" , "lee(t(c)ode)" would also be accepted.
 *
 * Example 2:
 * Input: s = "a)b(c)d"
 * Output: "ab(c)d"
 *
 * Example 3:
 * Input: s = "))(("
 * Output: ""
 * Explanation: An empty string is also valid.
 *
 * Constraints:
 * 1 <= s.length <= 10^5
 * s[i] is one of  '(' , ')' and lowercase English letters.
 *
 */
#include <string>
#include <stack>
#include <vector>

class Solution {
public:
    std::string minRemoveToMakeValid(std::string s) {
        int n = s.length();
        std::vector<bool> remove(n, false);
        std::stack<int> st; // stores indices of '('

        for (int i = 0; i < n; ++i) {
            if (s[i] == '(') {
                st.push(i);
            } else if (s[i] == ')') {
                if (st.empty()) {
                    remove[i] = true; // unmatched ')'
                } else {
                    st.pop(); // match this ')' with a '('
                }
            }
        }

        // Mark unmatched '(' for removal
        while (!st.empty()) {
            remove[st.top()] = true;
            st.pop();
        }

        // Build result
        std::string result;
        for (int i = 0; i < n; ++i) {
            if (!remove[i]) {
                result.push_back(s[i]);
            }
        }
        return result;
    }
};