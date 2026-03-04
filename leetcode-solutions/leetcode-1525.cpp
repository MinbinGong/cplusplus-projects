/*
 * 1525. Number of Good Ways to Split a String
 *
 * You are given a string s, a split is called good if you can split s into 2 non-empty strings p and q where its concatenation is equal to s and the number of distinct letters in p and q are the same.
 *
 * Return the number of good splits you can make in s.
 *
 * Example 1:
 * Input: s = "aacaba"
 * Output: 2
 * Explanation: There are 5 ways to split "aacaba" and 2 of them are good.
 * ("a", "acaba") Left string and right string contains 1 and 3 different letters respectively.
 * ("aa", "caba") Left string and right string contains 1 and 3 different letters respectively.
 * ("aac", "aba") Left string and right string contains 2 and 2 different letters respectively (good split).
 * ("aaca", "ba") Left string and right string contains 2 and 2 different letters respectively (good split).
 * ("aacab", "a") Left string and right string contains 3 and 1 different letters respectively.
 * 
 * Example 2:
 * Input: s = "abcd"
 * Output: 1
 * Explanation: Split the string as follows ("ab", "cd").
 * 
 * Constraints:
 * s contains only lowercase English letters.
 * 1 <= s.length <= 10^5
 * 
 */
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int numSplits(string s) {
        int n = s.length();
        vector<int> left(26, 0), right(26, 0);
        int leftDistinct = 0, rightDistinct = 0;

        // Initialize right with all characters
        for (char c : s) {
            if (right[c - 'a']++ == 0) rightDistinct++;
        }

        int ans = 0;
        for (int i = 0; i < n - 1; ++i) {
            char c = s[i];
            // Move c from right to left
            if (left[c - 'a']++ == 0) leftDistinct++;
            if (--right[c - 'a'] == 0) rightDistinct--;

            if (leftDistinct == rightDistinct) ans++;
        }
        return ans;
    }
};