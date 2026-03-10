/*
 * 1702. Maximum Binary String After Change
 * 
 * You are given a binary string binary consisting of only 0's or 1's. You can apply each of the following operations any number of times:
 * 
 * Operation 1: If the number contains the substring "00", you can replace it with "10".
 * For example, "00010" -> "10010"
 * Operation 2: If the number contains the substring "10", you can replace it with "01".
 * For example, "00010" -> "00001"
 * Return the maximum binary string you can obtain after any number of operations. Binary string x is greater than binary string y if x's decimal representation is greater than y's decimal representation.
 * 
 * Example 1:
 * Input: binary = "000110"
 * Output: "111011"
 * Explanation: A valid transformation sequence can be:
 * "000110" -> "000101" 
 * "000101" -> "100101" 
 * "100101" -> "110101" 
 * "110101" -> "110011" 
 * "110011" -> "111011"
 * 
 * Example 2:
 * Input: binary = "01"
 * Output: "01"
 * Explanation: "01" cannot be transformed any further.
 * 
 * Constraints:
 * 1 <= binary.length <= 10^5
 * binary consists of only '0' and '1'.
 * 
 */
#include <string>
using namespace std;

class Solution {
public:
    string maximumBinaryString(string binary) {
        int n = binary.length();
        
        // Find the position of the first '0'
        int firstZero = -1;
        for (int i = 0; i < n; i++) {
            if (binary[i] == '0') {
                firstZero = i;
                break;
            }
        }
        
        // If no zero found or only one zero, string is already maximum
        if (firstZero == -1) {
            return binary;
        }
        
        // Count total number of zeros in the string
        int zeroCount = 0;
        for (char c : binary) {
            if (c == '0') zeroCount++;
        }
        
        // If only one zero, string is already maximum
        if (zeroCount == 1) {
            return binary;
        }
        
        // Construct the result: all '1's except for one '0' at position (firstZero + zeroCount - 1)
        string result(n, '1');
        result[firstZero + zeroCount - 1] = '0';
        
        return result;
    }
};