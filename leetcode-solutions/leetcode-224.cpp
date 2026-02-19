/*
 * Basic Calculator
 * 
 * Given a string s representing a valid expression, implement a basic calculator to evaluate it, and return the result of the evaluation.
 * 
 * Note: You are not allowed to use any built-in function which evaluates strings as mathematical expressions, such as eval().
 * 
 * Constraints:
 * 1. 1 <= s.length <= 3 * 105
 * 2. s consists of digits, '+', '-', '(', ')', and ' '.
 * 3. s represents a valid expression.
 * 4. '+' is not used as a unary operation (i.e., "+1" and "+(2 + 3)" is invalid).
 * 5. '-' could be used as a unary operation (i.e., "-1" and "-(2 + 3)" is valid).
 * 6. There will be no two consecutive operators in the input.
 * 7. Every number and running calculation will fit in a signed 32-bit integer.
 */
#include <string>
#include <stack>
using namespace std;

class Solution {
public:
    int calculate(string s) {
        int result = 0;
        int sign = 1;      // 1 for '+', -1 for '-'
        int num = 0;
        stack<int> st;     // stack to store (result_before_paren, sign_before_paren)
        
        for (char c : s) {
            if (isdigit(c)) {
                num = num * 10 + (c - '0');
            } else if (c == '+' || c == '-') {
                // Apply the previous number to result
                result += sign * num;
                num = 0;
                // Update sign for the next number
                sign = (c == '+') ? 1 : -1;
            } else if (c == '(') {
                // Push current result and sign onto stack
                st.push(result);
                st.push(sign);
                // Reset for new sub-expression
                result = 0;
                sign = 1;
            } else if (c == ')') {
                // Finish the inner expression
                result += sign * num;
                num = 0;
                // Pop the sign and outer result
                int outerSign = st.top(); st.pop();
                int outerResult = st.top(); st.pop();
                // Combine: outerResult + outerSign * (inner result)
                result = outerResult + outerSign * result;
            }
            // spaces are ignored
        }
        
        // Add any remaining number
        result += sign * num;
        return result;
    }
};