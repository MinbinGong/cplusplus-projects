/**
 * 1541. Minimum Insertions to Balance a Parentheses String
 * 
 * Given a parentheses string s containing only the characters '(' and ')'. A parentheses string is balanced if:
 * 
 * Any left parenthesis '(' must have a corresponding two consecutive right parenthesis '))'.
 * Left parenthesis '(' must go before the corresponding two consecutive right parenthesis '))'.
 * In other words, we treat '(' as openning parenthesis and '))' as closing parenthesis.
 * 
 * For example, "())", "())(())))" and "(())())))" are balanced, ")()", "()))" and "(()))" are not balanced.
 * 
 * You can insert the characters '(' and ')' at any position of the string to balance it if needed.
 * 
 * Return the minimum number of insertions needed to make s balanced.
 * 
 * 
 * Example 1:
 * Input: s = "(()))"
 * Output: 1
 * Explanation: The balanced string is "(()))".
 * 
 * Example 2:
 * Input: s = "())"
 * Output: 0
 * Explanation: The string is already balanced.
 * 
 * Example 3:
 * Input: s = "))())("
 * Output: 3
 * Explanation: Add '(' to match the first '))', Add '))' to match the last '('.
 * 
 * Constraints:
 * 1 <= s.length <= 10^5
 * s consists of '(' and ')' only.
 * 
 */
#include <string>
using namespace std;

class Solution {
public:
    int minInsertions(string s) {
        int need = 0;       // how many ')' are still required to close currently open '('
        int insert = 0;     // insertions already made

        for (char c : s) {
            if (c == '(') {
                need += 2;          // each '(' needs two ')'
            } else { // c == ')'
                if (need > 0) {
                    need--;          // one ')' is used to satisfy a pending need
                } else {
                    // extra ')' appears without any matching '(' – insert a '(' first
                    insert++;
                    // inserted '(' needs two ')', but this ')' consumes one → net +1 need
                    need += 1;
                }
            }
        }

        // after the loop, any remaining need must be satisfied by inserting ')'
        return insert + need;
    }
};