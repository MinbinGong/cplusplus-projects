/**
 * 1759. Count Number of Homogenous Substrings
 * 
 * Given a string s, return the number of homogenous substrings of s.
 * Since the answer may be too large, return it modulo 10^9 + 7.
 * 
 * A string is homogenous if all the characters of the string are the same.
 * 
 * A substring is a contiguous sequence of characters within a string.
 * 
 * Example 1:
 * 
 * Input: s = "abbcccaa"
 * Output: 13
 * Explanation: The homogenous substrings are listed as below:
 * "a"   appears 3 times.
 * "aa"  appears 1 time.
 * "b"   appears 2 times.
 * "bb"  appears 1 time.
 * "c"   appears 3 times.
 * "cc"  appears 2 times.
 * "ccc" appears 1 time.
 * 3 + 1 + 2 + 1 + 3 + 2 + 1 = 13.
 * 
 * Example 2:
 * 
 * Input: s = "xy"
 * Output: 2
 * Explanation: The homogenous substrings are "x" and "y".
 * 
 * Example 3:
 * 
 * Input: s = "zzzzz"
 * Output: 15
 * 
 * Constraints:
 * 
 * 1 <= s.length <= 10^5
 * s consists of lowercase letters.
 * 
 */

#include <string>
using namespace std;

class Solution {
public:
    int countHomogenous(string s) {
        const int MOD = 1e9 + 7;
        long long ans = 0;
        int n = s.size();
        for (int i = 0; i < n; ) {
            int j = i;
            while (j < n && s[j] == s[i]) ++j;
            long long len = j - i;
            ans = (ans + len * (len + 1) / 2) % MOD;
            i = j;
        }
        return ans;
    }
};