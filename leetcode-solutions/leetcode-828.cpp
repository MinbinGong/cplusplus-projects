/**
 * 828. Count Unique Characters of All Substrings of a Given String
 *
 * Let's define a function countUniqueChars(s) that returns the number of unique characters on s.
 *
 * For example, calling countUniqueChars(s) if s = "LEETCODE" then "L", "T", "C", "O", "D" are the unique characters since
 * they appear only once in s, therefore countUniqueChars(s) = 5.
 *
 * Given a string s, return the sum of countUniqueChars(t) where t is a substring of s.
 *
 * Notice that some substrings can be repeated so in this case you have to count the repeated ones too.
 *
 * Example:
 * Input: s = "ABC"
 * Output: 10
 * Explanation: All possible substrings are: "A","B","C","AB","BC" and "ABC".
 * Evey substring is composed with only unique letters.
 * Sum of lengths of all substring is 1 + 1 + 1 + 2 + 2 + 3 = 10
 *
 * Note:
 * 1 <= s.length <= 10^5
 * s consists of uppercase English letters only.
 * 
 */
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Solution {
public:
    int uniqueLetterString(string s) {
        int n = s.size();
        vector<int> lastPos(26, -1);
        vector<int> prev(n, -1);
        // 记录每个字符上一次出现的位置
        for (int i = 0; i < n; ++i) {
            int c = s[i] - 'A';
            prev[i] = lastPos[c];
            lastPos[c] = i;
        }

        fill(lastPos.begin(), lastPos.end(), n);
        vector<int> next(n, n);
        // 记录每个字符下一次出现的位置
        for (int i = n - 1; i >= 0; --i) {
            int c = s[i] - 'A';
            next[i] = lastPos[c];
            lastPos[c] = i;
        }

        int ans = 0;
        for (int i = 0; i < n; ++i) {
            // 以 s[i] 为唯一字符的子串个数
            ans += (i - prev[i]) * (next[i] - i);
        }
        return ans;
    }
};
