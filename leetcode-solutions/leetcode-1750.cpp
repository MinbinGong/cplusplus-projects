/**
 * 1750. Minimum Length of String After Deleting Similar Ends
 * 
 * Given a string s consisting only of characters 'a', 'b', and 'c'. You are asked
 * to apply the following algorithm on the string any number of times:
 * 
 * Pick a non-empty prefix from the string s where all the characters in the prefix
 * are equal.
 * Pick a non-empty suffix from the string s where all the characters in this suffix
 * are equal.
 * The prefix and the suffix should not intersect at any index.
 * The characters from the prefix and suffix must be the same.
 * Delete both the prefix and the suffix.
 * Return the minimum length of s after performing the above operation any number of
 * times (possibly zero times).
 * 
 * Example 1:
 * 
 * Input: s = "ca"
 * Output: 2
 * Explanation: You can't remove any characters, so the string stays as is.
 * 
 * Example 2:
 * 
 * Input: s = "cabaabac"
 * Output: 0
 * Explanation: An optimal sequence of operations is:
 * - Pick prefix = "c" and suffix = "c" and delete them, s = "abaaba".
 * - Pick prefix = "a" and suffix = "a" and delete them, s = "baab".
 * - Pick prefix = "b" and suffix = "b" and delete them, s = "aa".
 * - Pick prefix = "a" and suffix = "a" and delete them, s = "".
 * 
 * Constraints:
 * 
 * 1 <= s.length <= 105
 * s only consists of characters 'a', 'b', and 'c'.
 * 
 */
#include <string>
using namespace std;

class Solution {
public:
    int minimumLength(string s) {
        int l = 0, r = s.size() - 1;
        while (l < r && s[l] == s[r]) {
            char c = s[l];
            while (l <= r && s[l] == c) ++l;
            while (l <= r && s[r] == c) --r;
        }
        return r - l + 1;
    }
};