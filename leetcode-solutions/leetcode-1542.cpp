/**
 * 1542. Find Longest Awesome Substring
 * 
 * Given a string s. An awesome substring is a non-empty substring of s such that we can make any number of swaps in order to make it palindrome.
 * 
 * Return the length of the maximum length awesome substring of s.
 * 
 * 
 * Example 1:
 * Input: s = "3242415"
 * Output: 5
 * Explanation: "24241" is the longest awesome substring, we can form the palindrome "24142" with some swaps.
 * 
 * Example 2:
 * Input: s = "12345678"
 * Output: 1
 * 
 * Example 3:
 * Input: s = "213123"
 * Output: 6
 * Explanation: "213123" is the longest awesome substring, we can form the palindrome "231132" with some swaps.
 * 
 * Example 4:
 * Input: s = "00"
 * Output: 2
 * 
 * Constraints:
 * 1 <= s.length <= 10^5
 * s consists only of digits.
 * 
 */
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    int longestAwesome(string s) {
        // mask of parity for digits 0-9 (10 bits)
        vector<int> firstOccur(1024, -1);
        firstOccur[0] = 0;          // empty prefix before first character
        int mask = 0;
        int ans = 0;
        int n = s.size();

        for (int i = 0; i < n; ++i) {
            int d = s[i] - '0';
            mask ^= (1 << d);       // flip parity of current digit

            // case 1: same mask -> all frequencies even
            if (firstOccur[mask] != -1) {
                ans = max(ans, i + 1 - firstOccur[mask]);
            } else {
                firstOccur[mask] = i + 1;
            }

            // case 2: masks that differ by exactly one bit
            for (int b = 0; b < 10; ++b) {
                int target = mask ^ (1 << b);
                if (firstOccur[target] != -1) {
                    ans = max(ans, i + 1 - firstOccur[target]);
                }
            }
        }
        return ans;
    }
};
