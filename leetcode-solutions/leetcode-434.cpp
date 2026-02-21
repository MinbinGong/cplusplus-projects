/*
 * Number of Segments in a String
 *
 * Given a string s, return the number of segments in the string.
 * 
 * A segment is defined to be a contiguous sequence of non-space characters.
 * 
 * Constraints:
 * 0 <= s.length <= 300
 * s consists of lowercase and uppercase English letters, digits, or one of the following characters "!@#$%^&*()_+-=',.:".
 * The only space character in s is ' '.
 */
#include <string>
using namespace std;

class Solution {
public:
    int countSegments(string s) {
        int count = 0;
        int n = s.size();
        for (int i = 0; i < n; ++i) {
            // 当前字符非空格，并且前一个字符是空格或是字符串开头
            if (s[i] != ' ' && (i == 0 || s[i - 1] == ' ')) {
                count++;
            }
        }
        return count;
    }
};