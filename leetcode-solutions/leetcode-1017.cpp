/*
 * 1017. Convert to Base -2
 *
 * Given a number N, return a string consisting of "0"s and "1"s that represents its value in base -2 (negative two).
 * 
 * The returned string must have no leading zeroes, unless the string is "0".
 * 
 * Example 1:
 *
 * Input: 2
 * Output: "110"
 * Explantion: (-2) ^ 2 + (-2) ^ 1 = 2
 * 
 * Example 2:
 *
 * Input: 3
 * Output: "111"
 * Explantion: (-2) ^ 2 + (-2) ^ 1 + (-2) ^ 0 = 3
 * 
 * Example 3:
 *
 * Input: 4
 * Output: "100"
 * Explantion: (-2) ^ 2 = 4
 * 
 * Note:
 *
 * 0 <= N <= 10^9
 * 
 */
#include <string>
#include <algorithm>

class Solution {
public:
    std::string baseNeg2(int n) {
        if (n == 0) return "0";
        std::string result;
        while (n != 0) {
            int remainder = n % -2;
            n /= -2;
            if (remainder < 0) {
                remainder += 2;
                n += 1;         // because we increased remainder, adjust quotient
            }
            result.push_back('0' + remainder);
        }
        std::reverse(result.begin(), result.end());
        return result;
    }
};