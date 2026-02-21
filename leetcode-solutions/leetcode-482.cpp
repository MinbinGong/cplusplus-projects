/*
 * License Key Formatting
 *
 * You are given a license key represented as a string s that consists of only alphanumeric characters and dashes. The string is separated into n + 1 groups by n dashes. You are also given an integer k.
 *
 * We want to reformat the string s such that each group contains exactly k characters, except for the first group, which could be shorter than k but still must contain at least one character. Furthermore, there must be a dash inserted between two groups, and you should convert all lowercase letters to uppercase.
 *
 * Return the reformatted license key.
 *
 * Constraints:
 * 1 <= s.length <= 105
 * s consists of English letters, digits, and dashes '-'.
 * 1 <= k <= 104
 * 
 */
#include <string>
using namespace std;

class Solution {
public:
    string licenseKeyFormatting(string s, int k) {
        string result;
        int count = 0;
        // Traverse from the end to the beginning
        for (int i = s.size() - 1; i >= 0; --i) {
            if (s[i] == '-') continue;               // ignore existing dashes
            if (count == k) {                         // need to insert a dash
                result.push_back('-');
                count = 0;
            }
            result.push_back(toupper(s[i]));          // add uppercase character
            ++count;
        }
        // Reverse because we built from the end
        reverse(result.begin(), result.end());
        return result;
    }
};