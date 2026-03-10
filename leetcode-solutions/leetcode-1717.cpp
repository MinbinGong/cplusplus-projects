/**
 * 1717. Maximum Score From Removing Substrings
 * 
 * You are given a string s and two integers x and y. You can perform two types of operations any number of times.
 * 
 * Remove substring "ab" and gain x points.
 * For example, when removing "ab" from "cabxbae" it becomes "cxbae".
 * Remove substring "ba" and gain y points.
 * For example, when removing "ba" from "cabxbae" it becomes "cabxe".
 * Return the maximum points you can gain after applying the above operations on s.
 * 
 * Example 1:
 * Input: s = "cdbcbbaaabab", x = 4, y = 5
 * Output: 19
 * Explanation:
 * - Remove the "ba" underlined in "cdbcbbaaabab". Now, s = "cdbcbbaaab" and 5 points are added to the score.
 * - Remove the "ab" underlined in "cdbcbbaaab". Now, s = "cdbcbaaab" and 4 points are added to the score.
 * - Remove the "ba" underlined in "cdbcbaaab". Now, s = "cdbcbaa" and 5 points are added to the score.
 * Total score = 5 + 4 + 5 = 14.
 * 
 * Example 2:
 * Input: s = "aabbaaxybbaabb", x = 5, y = 4
 * Output: 20
 * 
 * Constraints:
 * 1 <= s.length <= 105
 * 1 <= x, y <= 104
 * s consists of lowercase English letters.
 * 
 */
#include <string>
using namespace std;

class Solution {
public:
    int maximumGain(string s, int x, int y) {
        // helper lambda to remove a given pair and count removals
        auto removePairs = [](const string& str, char first, char second) {
            string stack;
            int count = 0;
            for (char c : str) {
                if (!stack.empty() && stack.back() == first && c == second) {
                    stack.pop_back();
                    ++count;
                } else {
                    stack.push_back(c);
                }
            }
            return make_pair(count, stack);
        };

        if (x >= y) {
            // remove "ab" first
            auto [cntAB, remainder] = removePairs(s, 'a', 'b');
            auto [cntBA, _] = removePairs(remainder, 'b', 'a');
            return cntAB * x + cntBA * y;
        } else {
            // remove "ba" first
            auto [cntBA, remainder] = removePairs(s, 'b', 'a');
            auto [cntAB, _] = removePairs(remainder, 'a', 'b');
            return cntAB * x + cntBA * y;
        }
    }
};