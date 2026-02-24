/**
 * 859. Buddy Strings
 * 
 * Example 1:
 * Input: A = "ab", B = "ba"
 * Output: true
 * 
 * Example 2:
 * Input: A = "ab", B = "ab"
 * Output: false
 * 
 * Example 3:
 * Input: A = "aa", B = "aa"
 * Output: true
 * 
 * Example 4:
 * Input: A = "aaaaaaabc", B = "aaaaaaacb"
 * Output: true
 * 
 * Example 5:
 * Input: A = "", B = "aa"
 * Output: false
 * 
 * Note:
 * 0 <= A.length <= 20000
 * 0 <= B.length <= 20000
 * A and B consist only of lowercase letters.
 * 
 */
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    bool buddyStrings(string s, string goal) {
        if (s.length() != goal.length()) return false;

        // Case 1: strings are equal
        if (s == goal) {
            vector<int> count(26, 0);
            for (char c : s) {
                if (++count[c - 'a'] > 1) return true; // duplicate exists
            }
            return false; // all characters distinct
        }

        // Case 2: strings differ
        vector<int> diff;
        for (int i = 0; i < s.length(); ++i) {
            if (s[i] != goal[i]) diff.push_back(i);
        }
        // Must have exactly two differences and they should be swappable
        return diff.size() == 2 &&
               s[diff[0]] == goal[diff[1]] &&
               s[diff[1]] == goal[diff[0]];
    }
};