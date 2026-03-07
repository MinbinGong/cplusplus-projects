/**
 * 1616. Check If Two String Arrays are Equivalent
 * 
 * Given two string arrays word1 and word2, return true if the two arrays represent the same string, and false otherwise.
 * 
 * A string is represented by an array if the array elements concatenated in order forms the string.
 * 
 * Example 1:
 * Input: word1 = ["ab", "c"], word2 = ["a", "bc"]
 * Output: true
 * Explanation:
 * word1 represents string "ab" + "c" -> "abc"
 * word2 represents string "a" + "bc" -> "abc"
 * The strings are the same, so return true.
 * 
 * Example 2:
 * Input: word1 = ["a", "cb"], word2 = ["ab", "c"]
 * Output: false
 * 
 * Example 3:
 * Input: word1  = ["abc", "d", "defg"], word2 = ["abcddefg"]
 * Output: true
 * 
 * Constraints:
 * 1 <= word1.length, word2.length <= 103
 * 1 <= word1[i].length, word2[i].length <= 103
 * 1 <= sum(word1[i].length), sum(word2[i].length) <= 103
 * word1[i] and word2[i] consist of lowercase letters.
 * 
 */
#include <string>
using namespace std;

class Solution {
public:
    bool checkPalindromeFormation(string a, string b) {
        // Try both possibilities: prefix from a + suffix from b,
        // and prefix from b + suffix from a.
        return check(a, b) || check(b, a);
    }

private:
    // Returns true if there exists an index i such that
    // a[0..i-1] + b[i..n-1] is a palindrome.
    bool check(string& a, string& b) {
        int n = a.size();
        int l = 0, r = n - 1;

        // Match from the outside as long as characters from a (left) and b (right) are equal.
        while (l < r && a[l] == b[r]) {
            ++l;
            --r;
        }

        // After the matching, the middle part [l, r] must be a palindrome
        // entirely from either a or b.
        return isPalindrome(a, l, r) || isPalindrome(b, l, r);
    }

    // Checks if the substring s[l..r] is a palindrome.
    bool isPalindrome(string& s, int l, int r) {
        while (l < r) {
            if (s[l] != s[r]) return false;
            ++l;
            --r;
        }
        return true;
    }
};