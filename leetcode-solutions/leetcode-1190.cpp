/*
 * 1190. Reverse Substrings Between Each Pair of Parentheses
 *
 * You are given a string s that consists of lower case English letters and brackets.
 * 
 * Reverse the strings in each pair of matching parentheses, starting from the innermost one.
 * 
 * Your result should not contain any brackets.
 * 
 * Example 1:
 * Input: s = "(abcd)"
 * Output: "dcba"
 * 
 * Example 2:
 * Input: s = "(u(love)i)"
 * Output: "iloveu"
 * 
 * Example 3:
 * Input: s = "(ed(et(oc))el)"
 * Output: "leetcode"
 * 
 * Example 4:
 * Input: s = "a(bcdefghijkl(mno)p)q"
 * Output: "apmnolkjihgfedcbq"
 * 
 * Note:
 * 0 <= s.length <= 2000
 * s only contains lower case English characters and parentheses.
 * It's guaranteed that all parentheses are balanced.
 * 
 */
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    string reverseParentheses(string s) {
        vector<char> st; // 用 vector 模拟栈
        for (char c : s) {
            if (c == ')') {
                string temp;
                // 弹出直到遇到 '('
                while (st.back() != '(') {
                    temp.push_back(st.back());
                    st.pop_back();
                }
                st.pop_back(); // 弹出 '('
                // 将反转后的字符串重新压入栈
                for (char ch : temp) {
                    st.push_back(ch);
                }
            } else {
                st.push_back(c);
            }
        }
        return string(st.begin(), st.end());
    }
};