/*
 * 1624. Largest Substring Between Two Equal Characters
 * 
 * Given a string s, return the length of the longest substring between two equal characters, excluding the two characters. If there is no such substring return -1.
 * 
 * A substring is a contiguous sequence of characters within a string.
 * 
 * Example 1:
 * Input: s = "aa"
 * Output: 0
 * Explanation: The optimal substring here is an empty substring between the two 'a's.
 * 
 * Example 2:
 * Input: s = "abca"
 * Output: 2
 * Explanation: The optimal substring here is "bc".
 * 
 * Example 3:
 * Input: s = "cbzxy"
 * Output: -1
 * Explanation: There are no characters that appear twice in s.
 * 
 * Constraints:
 * 1 <= s.length <= 300
 * s contains only lowercase English letters.
 * 
 */
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxLengthBetweenEqualCharacters(string s) {
        unordered_map<char, int> firstIndex;
        int maxLen = -1;
        for (int i = 0; i < s.size(); ++i) {
            char c = s[i];
            if (firstIndex.find(c) != firstIndex.end()) {
                // gap between first occurrence and current i is i - firstIndex[c] - 1
                maxLen = max(maxLen, i - firstIndex[c] - 1);
            } else {
                firstIndex[c] = i;
            }
        }
        return maxLen;
    }
};