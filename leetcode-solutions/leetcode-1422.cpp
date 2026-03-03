/**
 * 1422. Maximum Score After Splitting a String
 * 
 * Given a string s of zeros and ones, return the maximum score after splitting the string into two non-empty substrings (i.e. left substring and right substring).
 * 
 * The score after splitting a string is the number of zeros in the left substring plus the number of ones in the right substring.
 * 
 * Example 1:
 * 
 * Input: s = "011101"
 * Output: 5 
 * Explanation: 
 * All possible ways of splitting s into two non-empty substrings are:
 * left = "0" and right = "11101", score = 1 + 4 = 5 
 * left = "01" and right = "1101", score = 1 + 3 = 4 
 * left = "011" and right = "101", score = 1 + 2 = 3 
 * left = "0111" and right = "01", score = 1 + 1 = 2 
 * left = "01110" and right = "1", score = 2 + 1 = 3
 * 
 * Example 2:
 * 
 * Input: s = "00111"
 * Output: 5
 * Explanation: When left = "00" and right = "111", we get the maximum score = 2 + 3 = 5
 * 
 * Example 3:
 * 
 * Input: s = "1111"
 * Output: 3
 * 
 * Note:
 * 2 <= s.length <= 500
 * The string s consists of characters '0' and '1' only.
 * 
 */
#include <string>
using namespace std;

class Solution {
public:
    int maxScore(string s) {
        int n = s.length();
        int totalOnes = 0;
        // Count total number of '1's in the string
        for (char c : s) {
            if (c == '1') totalOnes++;
        }

        int zerosLeft = 0;    // count of '0's in left part
        int onesRight = totalOnes; // initially, left is empty, so all ones are on the right
        int best = 0;

        // i is the last index of the left part (0-based)
        // left part must be non-empty, right part must be non-empty
        // so i goes from 0 to n-2
        for (int i = 0; i < n - 1; i++) {
            // Update counts based on character at position i
            if (s[i] == '0') {
                zerosLeft++;
            } else {
                onesRight--; // this '1' moves from right to left
            }
            // Score at this split
            int score = zerosLeft + onesRight;
            best = max(best, score);
        }

        return best;
    }
};