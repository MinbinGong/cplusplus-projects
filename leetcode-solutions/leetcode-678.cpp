/*
 * Valid Parenthesis String
 *
 * Given a string containing only three types of characters: '(', ')' and '*', write a function to check whether this string is valid. We define the validity of a string by these rules:
 *
 * Any left parenthesis '(' must have a corresponding right parenthesis ')'.
 * Any right parenthesis ')' must have a corresponding left parenthesis '('.
 * Left parenthesis '(' must go before the corresponding right parenthesis ')'.
 * '*' could be treated as a single right parenthesis ')' or a single left parenthesis '(' or an empty string.
 * An empty string is also valid.
 * 
 * Example 1:
 *
 * Input: "()"
 * Output: True
 * 
 * Example 2:
 *
 * Input: "(*)"
 * Output: True
 * 
 * Example 3:
 *
 * Input: "(*))"
 * Output: True
 * 
 * Note:
 *
 * The string size will be in the range [1, 100].
 * 
 */
#include <string>
using namespace std;

class Solution {
public:
    bool checkValidString(string s) {
        // low 和 high 分别表示左括号数量的最小可能值和最大可能值
        int low = 0, high = 0;
        for (char c : s) {
            if (c == '(') {
                ++low;
                ++high;
            } else if (c == ')') {
                --low;
                --high;
            } else { // c == '*'
                --low;      // '*' 当作右括号
                ++high;     // '*' 当作左括号
                // '*' 当作空字符串时不改变计数，已在 low 和 high 的范围内自然覆盖
            }
            // 如果 high 小于 0，说明即使把所有 '*' 都当作 '(' 也不够匹配当前的 ')'
            if (high < 0) return false;
            // low 不能小于 0，因为负值无意义，我们只关心非负的最小可能
            low = max(low, 0);
        }
        // 最后，最小可能的左括号数必须为 0 才能完全匹配
        return low == 0;
    }
};