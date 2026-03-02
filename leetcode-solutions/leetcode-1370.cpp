/**
 * 1370. Increasing Decreasing String
 *
 * Given a string s. You should re-order the string using the following algorithm:
 *
 * Pick the smallest character from s and append it to the result.
 * Pick the smallest character from s which is greater than the last appended character to the result and append it.
 * Repeat step 2 until you cannot pick more characters.
 * Pick the largest character from s and append it to the result.
 * Pick the largest character from s which is smaller than the last appended character to the result and append it.
 * Repeat step 5 until you cannot pick more characters.
 * Repeat the steps from 1 to 6 until you pick all characters from s.
 * In each step, If the smallest or the largest character appears more than once you can choose any occurrence and append it to the result.
 *
 * Return the result string after sorting s with this algorithm.
 *
 * Example 1:
 * Input: s = "aaaabbbbcccc"
 * Output: "abccbaabccba"
 * Explanation: First append "a", then append "b", then append "c" three times, then append "b" two times, then append "a" three times.
 * 
 * Example 2:
 * Input: s = "rat"
 * Output: "art"
 * Explanation: The word "rat" becomes "art" after re-ordering it with the mentioned algorithm.
 * 
 * Example 3:
 * Input: s = "leetcode"
 * Output: "cdelotee"
 * Explanation: First append "c", then append "d", then append "e" three times, then append "l" two times, then append "o" three times.
 * 
 * Note:
 * s contains only lower-case English letters.
 * 1 <= s.length <= 500
 * 
 */
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Solution {
public:
    string sortString(string s) {
        vector<int> cnt(26, 0);
        for (char c : s) cnt[c - 'a']++;
        string ans;
        int n = s.length();
        while (ans.length() < n) {
            // 升序取一遍
            for (int i = 0; i < 26; ++i) {
                if (cnt[i] > 0) {
                    ans.push_back('a' + i);
                    cnt[i]--;
                }
            }
            // 降序取一遍
            for (int i = 25; i >= 0; --i) {
                if (cnt[i] > 0) {
                    ans.push_back('a' + i);
                    cnt[i]--;
                }
            }
        }
        return ans;
    }
};