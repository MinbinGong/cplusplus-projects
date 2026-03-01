/**
 * 1297. Maximum Number of Occurrences of a Substring
 * 
 * Given a string s, return the maximum number of ocurrences of any substring under the following rules:
 * The number of unique characters in the substring must be less than or equal to maxLetters.
 * The substring size must be between minSize and maxSize inclusive.
 * 
 * Example 1:
 * Input: s = "aababcaab", maxLetters = 2, minSize = 3, maxSize = 4
 * Output: 2
 * Explanation: Substring "aab" has 2 ocurrences in the original string.
 * It satisfies the conditions, 2 unique letters and size 3 (between minSize and maxSize).
 * 
 * Example 2:
 * Input: s = "aaaa", maxLetters = 1, minSize = 3, maxSize = 3
 * Output: 2
 * Explanation: Substring "aaa" occur 2 times in the string. It can overlap.
 * 
 * Example 3:
 * Input: s = "aabcabcab", maxLetters = 2, minSize = 2, maxSize = 3
 * Output: 3
 * 
 * Example 4:
 * Input: s = "abcde", maxLetters = 2, minSize = 3, maxSize = 3
 * Output: 0
 * 
 * Note:
 * 1 <= s.length <= 10^5
 * 1 <= maxLetters <= 26
 * 1 <= minSize <= maxSize <= min(26, s.length)
 * s only contains lowercase English letters.
 * 
 */
#include <string>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class Solution {
public:
    int maxFreq(string s, int maxLetters, int minSize, int maxSize) {
        unordered_map<string, int> count;   // 统计子串出现次数
        int ans = 0;
        int n = s.length();

        for (int i = 0; i <= n - minSize; ++i) {
            string sub = s.substr(i, minSize);   // 取出长度为 minSize 的子串

            // 统计子串中不同字母的个数
            unordered_set<char> letters(sub.begin(), sub.end());
            if (letters.size() <= maxLetters) {
                ans = max(ans, ++count[sub]);
            }
        }

        return ans;
    }
};