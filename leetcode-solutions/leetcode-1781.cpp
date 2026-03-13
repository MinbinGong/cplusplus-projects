/**
 * 1781. Sum of Beauty of All Substrings
 * 
 * The beauty of a string is the difference in frequencies between the most frequent and least frequent characters.
 * 
 * For example, the beauty of "abaacc" is 3 - 1 = 2.
 * Given a string s, return the sum of beauty of all of its substrings.
 * 
 * Example 1:
 * 
 * Input: s = "aabcb"
 * Output: 5
 * Explanation: The substrings with non-zero beauty are ["aab","aabc","aabcb","abcb","bcb"], each with beauty equal to 1.
 * 
 * Example 2:
 * 
 * Input: s = "aabcbaa"
 * Output: 17
 * 
 * Constraints:
 * 
 * 1 <= s.length <= 500
 * s consists of only lowercase English letters.
 * 
 */
#include <vector>
#include <climits>
#include <string>
using namespace std;

class Solution {
public:
    int beautySum(string s) {
        int n = s.size();
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            int cnt[26] = {0};
            for (int j = i; j < n; ++j) {
                cnt[s[j] - 'a']++;
                int maxFreq = 0, minFreq = INT_MAX;
                for (int k = 0; k < 26; ++k) {
                    if (cnt[k] > 0) {
                        maxFreq = max(maxFreq, cnt[k]);
                        minFreq = min(minFreq, cnt[k]);
                    }
                }
                ans += maxFreq - minFreq;
            }
        }
        return ans;
    }
};