/*
 * One Edit Distance
 * 
 * Given two strings s and t, return true if they are both one edit distance apart, otherwise return false.
 * 
 * A string s is said to be one distance apart from a string t if you can:
 * 1. Insert exactly one character into s to get t.
 * 2. Delete exactly one character from s to get t.
 * 3. Replace exactly one character of s with a different character to get t.
 * 
 * Constraints:
 * 1. 0 <= s.length, t.length <= 104
 * 2. s and t consist of lowercase letters, uppercase letters, digits, and special characters.
 * 3. s and t are the same length.
 */
#include <string>
using namespace std;

bool isOneEditDistance(string s, string t) {
    int m = s.size(), n = t.size();
    if (m > n) return isOneEditDistance(t, s);
    if (n - m > 1) return false;
    
    for (int i = 0; i < m; ++i) {
        if (s[i] != t[i]) {
            if (m == n) {
                // Replace: check remaining strings from i+1
                return s.compare(i + 1, m - i - 1, t, i + 1, n - i - 1) == 0;
            } else {
                // Insert into s: skip one char in t
                return s.compare(i, m - i, t, i + 1, n - i - 1) == 0;
            }
        }
    }
    return m + 1 == n;
}