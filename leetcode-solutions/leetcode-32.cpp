/*
 * Given a string containing just the characters '(' and ')', return the length
 * of the longest valid (well-formed) parentheses substring
 */
#include <string>
#include <stack>
#include <algorithm>

int longest_valid_parentheses(std::string s) {
    std::stack<int> stk;
    stk.push(-1);
    int ans = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '(') {
            stk.push(i);
        } else {
            if (stk.size() == 1) {
                stk.top = i;
            } else {
                stk.pop();
                ans = max(ans, i - stk.top());
            }
        }
    }

    return ans;
}

