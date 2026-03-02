/*
 * 1358. Number of Substrings Containing All Three Characters
 *
 * Given a string s consisting only of characters a, b and c.
 * 
 * Return the number of substrings containing at least one occurrence of all these characters a, b and c.
 * 
 * Example 1:
 * Input: s = "abcabc"
 * Output: 10
 * Explanation: The substrings containing at least one occurrence of the characters a, b and c are "abc", "abca", "abcab", "abcabc", "bca", "bcab", "bcabc", "cab", "cabc" and "abc" (again). 
 * 
 * Example 2:
 * Input: s = "aaacb"
 * Output: 3
 * Explanation: The substrings containing at least one occurrence of the characters a, b and c are "aaacb", "aacb" and "acb". 
 * 
 * Example 3:
 * Input: s = "abc"
 * Output: 1
 * 
 * Note:
 * 3 <= s.length <= 5 x 10^4
 * s only consists of a, b or c characters.
 * 
 */
#include <string>
using namespace std;

class Solution {
public:
    int numberOfSubstrings(string s) {
        int n = s.size();
        int cnt[3] = {0};  // counts of 'a', 'b', 'c'
        int left = 0;
        int ans = 0;

        for (int right = 0; right < n; ++right) {
            cnt[s[right] - 'a']++;

            // shrink the window from the left while it still contains all three
            while (cnt[0] > 0 && cnt[1] > 0 && cnt[2] > 0) {
                cnt[s[left] - 'a']--;
                left++;
            }

            // after the while loop, the window [left, right] is invalid.
            // all substrings starting from 0 to left-1 and ending at right are valid.
            ans += left;
        }

        return ans;
    }
};
