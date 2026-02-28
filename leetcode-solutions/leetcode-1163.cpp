/*
 * 1163. Last Substring in Lexicographical Order
 *
 * Given a string s, return the last substring of s in lexicographical order.
 *
 * Example 1:
 * Input: "abab"
 * Output: "bab"
 * Explanation: The substrings are ["a", "ab", "aba", "abab", "b", "ba", "bab"]. The lexicographically maximum substring is "bab".
 *
 * Example 2:
 * Input: "leetcode"
 * Output: "tcode"
 *
 * Note:
 * 1 <= s.length <= 4 * 10^5
 * s contains only lowercase English letters.
 *
 */
#include <string>
using namespace std;

class Solution {
public:
    string lastSubstring(string s) {
        int n = s.size();
        int i = 0;          // current best start
        int j = 1;          // candidate start
        int k = 0;          // matching length

        while (j + k < n) {
            // extend the match
            if (s[i + k] == s[j + k]) {
                ++k;
                continue;
            }

            // mismatch at position i+k and j+k
            if (s[i + k] < s[j + k]) {
                // suffixes starting at i ... i+k are not better than j
                i = max(i + k + 1, j);
                j = i + 1;
            } else { // s[i + k] > s[j + k]
                // suffixes starting at j ... j+k are not better than i
                j = j + k + 1;
            }
            k = 0; // reset matching length
        }

        return s.substr(i);
    }
};