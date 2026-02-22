/*
 * Solve the Equation
 *
 *  Solve a given equation and return the value of 'x' in the form of a string "x=#value".
 *  The equation contains only '+', '-' operation, the variable 'x' and its coefficient.
 *  You should return "No solution" if there is no solution for the equation, or "Infinite solutions" if there are infinite solutions for the equation.
 *
 *  If there is exactly one solution for the equation, we ensure that the value of 'x' is an integer.
 *
 */
#include <string>
using namespace std;

class Solution {
public:
    string solveEquation(string equation) {
        long long coeff[2] = {0, 0};    // coefficient of x on left(0) and right(1)
        long long constant[2] = {0, 0}; // constant term on left and right
        int side = 0;                    // 0 = left, 1 = right
        int i = 0, n = equation.size();

        while (i < n) {
            if (equation[i] == '=') {
                side = 1;
                i++;
                continue;
            }

            // determine sign of the current term
            int sign = 1;
            if (equation[i] == '+' || equation[i] == '-') {
                sign = (equation[i] == '+') ? 1 : -1;
                i++;
            }

            // parse the term: either a number followed optionally by 'x', or just 'x'
            if (i < n && equation[i] == 'x') {
                // term is just "x" (coefficient 1)
                coeff[side] += sign;
                i++;
            } else {
                // parse a number
                long long num = 0;
                while (i < n && isdigit(equation[i])) {
                    num = num * 10 + (equation[i] - '0');
                    i++;
                }
                // check if it's an x-term or a constant
                if (i < n && equation[i] == 'x') {
                    coeff[side] += sign * num;
                    i++;
                } else {
                    constant[side] += sign * num;
                }
            }
        }

        // bring all terms to one side: (left_coeff - right_coeff) * x = (right_const - left_const)
        long long a = coeff[0] - coeff[1];
        long long b = constant[1] - constant[0];

        if (a == 0) {
            if (b == 0) return "Infinite solutions";
            else return "No solution";
        } else {
            // unique solution (guaranteed integer)
            long long x = b / a;
            return "x=" + to_string(x);
        }
    }
};