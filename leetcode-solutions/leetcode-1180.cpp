/*
 * 1180. Count Substrings with Only One Distinct Letter
 * 
 * Given a string S, return the number of substrings that have only one distinct letter.
 * 
 * Example 1:
 * Input: S = "aaaba"
 * Output: 8
 * Explantion: The substrings with one distinct letter are "aaa", "aa", "a", "b".
 * "aaa" occurs 1 time.
 * "aa" occurs 2 times.
 * "a" occurs 4 times.
 * "b" occurs 1 time.
 * So the answer is 1 + 2 + 4 + 1 = 8.
 * 
 * Example 2:
 * Input: S = "aaaaaaaaaa"
 * Output: 55
 * 
 * Note:
 * 1 <= S.length <= 1000
 * S[i] consists of only lowercase English letters.
 */
#include <string>
using namespace std;

class Solution {
public:
    int countLetters(string s) {
        int n = s.size();
        int ans = 0;
        int i = 0;
        while (i < n) {
            int j = i;
            while (j < n && s[j] == s[i]) ++j;
            int len = j - i;
            ans += len * (len + 1) / 2;  // number of substrings with only this char
            i = j;
        }
        return ans;
    }
};