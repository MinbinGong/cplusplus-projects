/*
 * 273. Integer to English Words
 * 
 * Convert a non-negative integer num to its English words representation.
 * 
 * Example 1:
 * Input: num = 123
 * Output: "One Hundred Twenty Three"
 * 
 * Example 2:
 * Input: num = 12345
 * Output: "Twelve Thousand Three Hundred Forty Five"
 * 
 * Example 3:
 * Input: num = 1234567
 * Output: "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty Seven"
 * 
 * Constraints:
 * 1. 0 <= num <= 2^31 - 1
 */
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    string numberToWords(int num) {
        if (num == 0) return "Zero";
        
        // Arrays for words
        vector<string> ones = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten",
                               "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen",
                               "Eighteen", "Nineteen"};
        vector<string> tens = {"", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
        vector<string> thousands = {"", "Thousand", "Million", "Billion"};
        
        string result;
        int unit = 0; // 0 = no scale, 1 = thousand, 2 = million, 3 = billion
        
        while (num > 0) {
            int chunk = num % 1000; // last three digits
            if (chunk != 0) {
                string chunkStr = threeDigitToWords(chunk, ones, tens);
                if (!result.empty()) {
                    result = chunkStr + " " + thousands[unit] + " " + result;
                } else {
                    result = chunkStr + (unit > 0 ? " " + thousands[unit] : "");
                }
            }
            num /= 1000;
            unit++;
        }
        return result;
    }

private:
    string threeDigitToWords(int num, const vector<string>& ones, const vector<string>& tens) {
        // num is between 1 and 999
        string res;
        int hundred = num / 100;
        int rest = num % 100;
        
        if (hundred > 0) {
            res += ones[hundred] + " Hundred";
            if (rest > 0) res += " ";
        }
        
        if (rest > 0) {
            if (rest < 20) {
                res += ones[rest];
            } else {
                res += tens[rest / 10];
                if (rest % 10 > 0) {
                    res += " " + ones[rest % 10];
                }
            }
        }
        return res;
    }
};