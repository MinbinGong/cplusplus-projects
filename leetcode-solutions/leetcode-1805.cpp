/*
 * 1805. Number of Different Integers in a String
 *
 * You are given a string word that consists of digits and lowercase English letters.
 * 
 * You need to find the number of different integers that appear in the string word.
 * 
 * Integers are positive numbers that do not have any leading zeros.
 * 
 * Example 1:
 * 
 * Input: word = "a123bc34d8ef34"
 * Output: 3
 * Explanation: The three different integers are "123", "34", and "8". Notice that "34" is only counted once.
 * 
 * Example 2:
 * 
 * Input: word = "leet1234code234"
 * Output: 2
 * Explanation: "1234" and "234" are the only different integers.
 * 
 * Example 3:
 * 
 * Input: word = "a1b01c001"
 * Output: 1
 * Explanation: "1", "01", and "001" are the only different integers. Notice that "001" is only counted once.
 * 
 * Constraints:
 * 
 * 1 <= word.length <= 1000
 * word consists of digits and lowercase English letters.
 * 
 */
#include <string>
#include <unordered_set>

class Solution {
public:
    int numDifferentIntegers(std::string word) {
        std::unordered_set<std::string> seen;
        int n = word.size();
        int i = 0;
        
        while (i < n) {
            if (isdigit(word[i])) {
                int j = i;
                // Find the end of the current digit sequence
                while (j < n && isdigit(word[j])) {
                    ++j;
                }
                // Extract the raw digit substring
                std::string num = word.substr(i, j - i);
                
                // Remove leading zeros
                int k = 0;
                while (k < num.size() && num[k] == '0') {
                    ++k;
                }
                if (k == num.size()) {
                    num = "0";          // The number is all zeros
                } else {
                    num = num.substr(k); // Keep the significant digits
                }
                
                seen.insert(num);
                i = j; // Move past the digits
            } else {
                ++i; // Skip non‑digit characters
            }
        }
        
        return seen.size();
    }
};
