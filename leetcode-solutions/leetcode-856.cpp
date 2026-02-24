/*
 * 856. Score of Parentheses
 * 
 * Given a balanced parentheses string S, compute the score of the string based on the following rule:
 * 
 * () has score 1
 * AB has score A + B, where A and B are balanced parentheses strings.
 * (A) has score 2 * A, where A is a balanced parentheses string.
 * 
 * Example 1:
 * Input: "()"
 * Output: 1
 * 
 * Example 2:
 * Input: "(())"
 * Output: 2
 * 
 * Example 3:
 * Input: "()()"
 * Output: 2
 * 
 * Example 4:
 * Input: "(()(()))"
 * Output: 6
 * 
 * Note:
 * S is a balanced parentheses string, containing only ( and ).
 * 2 <= S.length <= 50
 * 
 */
#include <string>
#include <stack>
using namespace std;

class Solution {
public:
    int scoreOfParentheses(string S) {
        stack<int> st;
        st.push(0); // 初始总分
        for (char c : S) {
            if (c == '(') {
                st.push(0); // 新一层开始，分数为0
            } else {
                int top = st.top(); st.pop();
                int prev = st.top(); st.pop();
                // 如果 top == 0，表示"()"，加1；否则加2*top
                st.push(prev + max(2 * top, 1));
            }
        }
        return st.top();
    }
};