/*
 * Ternary Expression Parser
 *
 * Given a string expression representing arbitrarily nested ternary expressions, evaluate the expression, and return the result of it.
 * 
 * You can always assume that the given expression is valid and only contains digits, '?', ':', 'T', and 'F' where 'T' is true and 'F' is false. All the numbers in the expression are one-digit numbers (i.e., in the range [0, 9]).
 * 
 * The conditional expressions group right-to-left (as usual in most languages), and the result of the expression will always evaluate to either a digit, 'T' or 'F'.
 * 
 * Constraints:
 * 5 <= expression.length <= 104
 * expression consists of digits, '?', ':', 'T' and 'F'.
 * It is guaranteed that expression is a valid ternary expression and that each number is a one-digit number.
 * 
 */
#include <string>
using namespace std;

class Solution {
public:
    string parseTernary(string expression) {
        int i = 0;
        // parse the expression and convert the result to a string
        return string(1, parse(expression, i));
    }

private:
    char parse(const string& s, int& i) {
        char c = s[i];
        // check if this is a ternary expression (next character is '?')
        if (i + 1 < s.size() && s[i + 1] == '?') {
            i += 2;                      // skip '?' and move to the start of true part
            char trueVal = parse(s, i);   // recursively parse the true expression
            i++;                          // skip the ':'
            char falseVal = parse(s, i);  // recursively parse the false expression
            return (c == 'T') ? trueVal : falseVal;
        } else {
            // single character (base case)
            i++;
            return c;
        }
    }
};