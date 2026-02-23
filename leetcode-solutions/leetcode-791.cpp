/*
 * 791. Custom Sort String
 *
 * S and T are strings composed of lowercase letters. In S, no letter occurs more than once.
 * 
 * S was sorted in some custom order previously. We want to permute the characters of T so that they match the order that S was sorted. More specifically, if x occurs before y in S, then x should occur before y in the returned string.
 * 
 * Return any permutation of T (as a string) that satisfies this property.
 * 
 * Example :
 * Input: 
 * S = "cba"
 * T = "abcd"
 * Output: "cbad"
 * Explanation: 
 * "a", "b", "c" appear in S, so the order of "a", "b", "c" should be "c", "b", and "a". 
 * Since "d" does not appear in S, it can be at any position in T. "dcba", "cdba", "cbda" are also valid outputs.
 * 
 * Note:
 * 1. S has length at most 26, and no character is repeated in S.
 * 2. T has length at most 200.
 * 3. S and T consist of lowercase letters only.
 * 
 */
#include <string>
using namespace std;

class Solution {
public:
    string customSortString(string S, string T) {
        int count[26] = {0};
        // Count frequency of each character in T
        for (char c : T) {
            count[c - 'a']++;
        }

        string result;
        // Append characters in the order specified by S
        for (char c : S) {
            if (count[c - 'a'] > 0) {
                result.append(count[c - 'a'], c);
                count[c - 'a'] = 0;   // mark as used
            }
        }

        // Append remaining characters (not in S) in any order
        for (int i = 0; i < 26; ++i) {
            if (count[i] > 0) {
                result.append(count[i], 'a' + i);
            }
        }

        return result;
    }
};