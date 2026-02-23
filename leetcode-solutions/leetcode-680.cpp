/*
 * Valid Palindrome II
 *
 * Given a non-empty string s, you may delete at most one character. Judge whether you can make it a palindrome.
 * 
 * Example 1:
 *
 * Input: "aba"
 * Output: True
 * 
 * Example 2:
 *
 * Input: "abca"
 * Output: True
 * Explanation: You could delete the character 'c'.
 * 
 * Note:
 *
 * The string will only contain lowercase characters a-z. The maximum length of the string is 50000.
 * 
 */
#include <string>
using namespace std;

class Solution {
public:
    bool validPalindrome(string s) {
        int left = 0, right = s.length() - 1;
        while (left < right) {
            if (s[left] != s[right]) {
                // 尝试删除左边字符或右边字符，看剩余部分是否为回文
                return isPalindrome(s, left + 1, right) || isPalindrome(s, left, right - 1);
            }
            ++left;
            --right;
        }
        return true;
    }

private:
    bool isPalindrome(const string& s, int l, int r) {
        while (l < r) {
            if (s[l] != s[r]) return false;
            ++l;
            --r;
        }
        return true;
    }
};