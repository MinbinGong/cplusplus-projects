/**
 * 1763. Longest Nice Substring
 * 
 * A string s is nice if, for every letter of the alphabet that s contains, it appears both in uppercase and lowercase.
 * 
 * For example, "abABB" is nice because 'A' and 'a' appear, and 'B' and 'b' appear. However, "abA" is not because 'b' appears, but 'B' does not.
 * 
 * Given a string s, return the longest substring of s that is nice. If there are multiple, return the substring of the earliest occurrence.
 * 
 * If there are none, return an empty string.
 * 
 * Example 1:
 * 
 * Input: s = "YazaAay"
 * Output: "aAa"
 * Explanation: "aAa" is a nice string because 'A/a' is the only letter of the alphabet in s, and both 'A' and 'a' appear.
 * "aAa" is the longest nice substring.
 * 
 * Example 2:
 * 
 * Input: s = "Bb"
 * Output: "Bb"
 * Explanation: "Bb" is a nice string because both 'B' and 'b' appear. The whole string is a substring.
 * 
 * Example 3:
 * 
 * Input: s = "c"
 * Output: ""
 * Explanation: There are no nice substrings.
 * 
 * Constraints:
 * 
 * 1 <= s.length <= 100
 * s consists of uppercase and lowercase English letters.
 * 
 */

#include <string>
#include <unordered_set>
using namespace std;

class Solution {
public:
    string longestNiceSubstring(string s) {
        if (s.size() < 2) return "";
        unordered_set<char> charSet(s.begin(), s.end());
        for (int i = 0; i < s.size(); ++i) {
            char c = s[i];
            // 如果当前字符同时存在大小写，则继续检查下一个
            if (charSet.count(toupper(c)) && charSet.count(tolower(c))) {
                continue;
            }
            // 当前字符破坏了 nice 条件，分割并递归
            string left = longestNiceSubstring(s.substr(0, i));
            string right = longestNiceSubstring(s.substr(i + 1));
            return left.size() >= right.size() ? left : right;
        }
        // 整个字符串是 nice 的
        return s;
    }
};