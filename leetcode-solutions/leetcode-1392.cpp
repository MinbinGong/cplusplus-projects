/**
 * 1392. Longest Happy Prefix
 * 
 * A string is called a happy prefix if is a non-empty prefix which is also a suffix (excluding itself).
 * 
 * Given a string s. Return the longest happy prefix of s .
 * 
 * Return an empty string if no such prefix exists.
 * 
 * Example 1:
 * Input: s = "level"
 * Output: "l"
 * Explanation: s contains 4 prefix excluding itself ("l", "le", "lev", "leve"), and suffix ("l", "el", "vel", "evel"). The largest prefix which is also suffix is given by "l".
 * 
 * Example 2:
 * Input: s = "ababab"
 * Output: "abab"
 * Explanation: "abab" is the largest prefix which is also suffix. They can overlap in the original string.
 * 
 * Example 3:
 * Input: s = "leetcodeleet"
 * Output: "leet"
 * 
 * Example 4:
 * Input: s = "a"
 * Output: ""
 * Explanation: s has only one prefix and suffix ("a", "a"). Hence, the longest happy prefix is "".
 * 
 * Note:
 * 1 <= s.length <= 10^5
 * s contains only lowercase English letters.
 * 
 */
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    string longestPrefix(string s) {
        int n = s.length();
        vector<int> pi(n, 0);  // prefix function (KMP)
        
        // Build the prefix function
        for (int i = 1; i < n; ++i) {
            int j = pi[i - 1];
            while (j > 0 && s[i] != s[j])
                j = pi[j - 1];
            if (s[i] == s[j])
                ++j;
            pi[i] = j;
        }
        
        int len = pi[n - 1];   // length of longest proper prefix that is also suffix
        return s.substr(0, len);
    }
};