/*
 * 541. Reverse String II
 * 
 * Given a string s and an integer k, reverse the first k characters for every 2k characters counting from the start of the string.
 * 
 * If there are fewer than k characters left, reverse all of them. If there are less than 2k but greater than or equal to k characters, then reverse the first k characters and left the other as original.
 * 
 * Example 1:
 * Input: s = "abcdefg", k = 2
 * Output: "bacdfeg"
 * 
 * Example 2:
 * Input: s = "abcd", k = 2
 * Output: "bacd"
 * 
 * Constraints:
 * 1. 1 <= s.length <= 104
 * 2. s consists of only lowercase English letters.
 * 3. 1 <= k <= 104
 * 
 */
#include <string>
#include <algorithm>
using namespace std;

class Solution1 {
public:
    string reverseStr(string s, int k) {
        int n = s.length();
        for (int i = 0; i < n; i += 2 * k) {
            // Reverse from i to i+k-1, but ensure we don't go out of bounds
            int left = i;
            int right = min(i + k - 1, n - 1);
            reverse(s.begin() + left, s.begin() + right + 1);
        }
        return s;
    }
};

class Solution2 {
public:
    string reverseStr(string s, int k) {
        int n = s.size();
        for (int i = 0; i < n; i += 2 * k) {
            int l = i;
            int r = min(i + k - 1, n - 1);
            while (l < r) {
                swap(s[l++], s[r--]);
            }
        }
        return s;
    }
};