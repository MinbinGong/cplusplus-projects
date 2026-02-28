/**
 * 1271. Hexspeak
 * 
 * A decimal number can be converted to its Hexspeak representation by first converting it to an uppercase hexadecimal string, then replacing all occurrences of the digit '0' with the letter 'O', and the digit '1' with the letter 'I'. Such a representation is valid if and only if it consists only of the letters in the set {'A', 'B', 'C', 'D', 'E', 'F', 'I', 'O'}.
 * 
 * Given a string num representing a decimal integer N, return the Hexspeak representation of N if it is valid, otherwise return "ERROR".
 * 
 * Example 1:
 * Input: num = "257"
 * Output: "IOI"
 * Explanation: 257 is 101 in hexadecimal.
 * 
 * Example 2:
 * Input: num = "3"
 * Output: "ERROR"
 * 
 * Note:
 * 1 <= N <= 10^12
 * N does not contain leading zeros.
 * All answers must be in uppercase letters.
 * 
 */
#include <string>
#include <sstream>
#include <cctype>

class Solution {
public:
    std::string toHexspeak(std::string num) {
        // Convert decimal string to integer
        long long n = std::stoll(num);
        
        // Convert to uppercase hexadecimal string
        std::stringstream ss;
        ss << std::hex << std::uppercase << n;
        std::string hex = ss.str();
        
        // Replace digits and validate
        std::string result;
        for (char c : hex) {
            if (c >= '2' && c <= '9') {
                return "ERROR";
            }
            if (c == '0') {
                result += 'O';
            } else if (c == '1') {
                result += 'I';
            } else { // A-F
                result += c;
            }
        }
        return result;
    }
};