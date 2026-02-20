/*
 * Additive Number
 *
 * Additive number is a string whose digits can form additive sequence.
 * 
 * A valid additive sequence should contain at least three numbers. Except for the first two numbers, each subsequent number in the sequence must be the sum of the preceding two.
 * 
 * Given a string containing only digits, return true if it is an additive number or false otherwise.
 * 
 * Note: Numbers in the additive sequence cannot have leading zeros, so sequence 1, 2, 03 or 1, 02, 3 is invalid.
 * 
 * Example 1:
 * Input: "112358"
 * Output: true
 * Explanation: The digits can form an additive sequence: 1, 1, 2, 3, 5, 8. 
 *              1 + 1 = 2, 1 + 2 = 3, 2 + 3 = 5, 3 + 5 = 8
 * 
 * Example 2:
 * Input: "199100199"
 * Output: true
 * Explanation: The additive sequence is: 1, 99, 100, 199. 
 *              1 + 99 = 100, 99 + 100 = 199
 * 
 * Example 3:
 * Input: "1023"
 * Output: false
 * Explanation: The additive sequence is: 1, 0, 2, 3. 
 *              1 + 0 = 1, 0 + 2 = 2, 2 + 3 = 5
 * 
 */
#include <string>
#include <algorithm>
using namespace std;

class Solution {
public:
    bool isAdditiveNumber(string num) {
        int n = num.size();
        if (n < 3) return false;

        // Try all possible lengths for the first two numbers
        for (int len1 = 1; len1 <= n - 2; ++len1) {
            // First number cannot have leading zero unless it is "0"
            if (len1 > 1 && num[0] == '0') break;

            string num1 = num.substr(0, len1);

            for (int len2 = 1; len2 <= n - len1 - 1; ++len2) {
                // Second number cannot have leading zero unless it is "0"
                if (len2 > 1 && num[len1] == '0') break;

                string num2 = num.substr(len1, len2);
                string rest = num.substr(len1 + len2);

                if (isValid(num1, num2, rest)) {
                    return true;
                }
            }
        }
        return false;
    }

private:
    // Check if the remaining string can be formed by the additive sequence
    bool isValid(const string& a, const string& b, const string& rest) {
        string A = a, B = b;
        string s = rest;
        int pos = 0;

        while (pos < s.size()) {
            string sum = addStrings(A, B);
            // The next part must exactly match the sum
            if (sum.size() > s.size() - pos) return false;
            if (s.compare(pos, sum.size(), sum) != 0) return false;

            pos += sum.size();
            A = B;
            B = sum;
        }
        // The loop ran at least once because rest is non‑empty
        return true;
    }

    // Addition of two non‑negative integers represented as strings
    string addStrings(const string& a, const string& b) {
        int i = a.size() - 1, j = b.size() - 1, carry = 0;
        string res;
        while (i >= 0 || j >= 0 || carry) {
            int sum = carry;
            if (i >= 0) sum += a[i--] - '0';
            if (j >= 0) sum += b[j--] - '0';
            res.push_back(sum % 10 + '0');
            carry = sum / 10;
        }
        reverse(res.begin(), res.end());
        return res;
    }
};