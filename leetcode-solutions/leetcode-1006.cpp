/*
 * 1006. Clumsy Factorial
 *
 * Normally, the factorial of a positive integer n is the product of all positive integers less than or equal to n.  For example, factorial(10) = 10 * 9 * 8 * 7 * 6 * 5 * 4 * 3 * 2 * 1.
 *
 * We instead make a clumsy factorial: using the integers in decreasing order, we swap out the multiply operations for a fixed rotation of operations: multiply (*), divide (/), add (+) and subtract (-) in this order.
 *
 * For example, clumsy(10) = 10 * 9 / 8 + 7 - 6 * 5 / 4 + 3 - 2 * 1.  However, these operations are still applied using the usual order of operations of arithmetic: we do all multiplication and division steps before any addition or subtraction steps, and multiplication and division steps are processed left to right.
 *
 * Example 1:
 *
 * Input: 4
 * Output: 7
 * Explanation: 7 = 4 * 3 / 2 + 1
 * 
 * Example 2:
 *
 * Input: 10
 * Output: 12
 * Explanation: 12 = 10 * 9 / 8 + 7 - 6 * 5 / 4 + 3 - 2 * 1
 * 
 * Note:
 *
 * 1 <= N <= 10000
 * -2^31 <= answer <= 2^31 - 1  (The answer is guaranteed to fit within a 32-bit integer.)
 * 
 */
#include <vector>

class Solution {
public:
    int clumsy(int N) {
        std::vector<int> st;
        st.push_back(N);                     // start with the first number

        for (int i = N - 1; i >= 1; --i) {
            int step = N - i;                 // how many numbers have been processed
            int op = (step - 1) % 4;          // 0:*, 1:/, 2:+, 3:-

            if (op == 0) {                     // multiplication
                int top = st.back();
                st.pop_back();
                st.push_back(top * i);
            } else if (op == 1) {               // division (truncates toward zero)
                int top = st.back();
                st.pop_back();
                st.push_back(top / i);
            } else if (op == 2) {               // addition
                st.push_back(i);
            } else {                             // subtraction
                st.push_back(-i);
            }
        }

        int sum = 0;
        for (int x : st) sum += x;
        return sum;
    }
};