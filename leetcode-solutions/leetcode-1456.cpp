/**
 * 1456. Maximum Number of Vowels in a Substring of Given Length
 * 
 * Given a string s and an integer k.
 * 
 * Return the maximum number of vowel letters in any substring of s with length k.
 * 
 * Vowel letters in English are (a, e, i, o, u).
 * 
 * Example 1:
 * 
 * Input: s = "abciiidef", k = 3
 * Output: 3
 * Explanation: The substring "iii" contains 3 vowel letters.
 * 
 * Example 2:
 * 
 * Input: s = "aeiou", k = 2
 * Output: 2
 * Explanation: Any substring of length 2 contains 2 vowels.
 * 
 * Example 3:
 * 
 * Input: s = "leetcode", k = 3
 * Output: 2
 * Explanation: "lee", "eet" and "ode" contain 2 vowels.
 * 
 * Example 4:
 * 
 * Input: s = "rhythms", k = 4
 * Output: 0
 * Explanation: We can see that s doesn't have any vowel letters.
 * 
 * Example 5:
 * 
 * Input: s = "tryhard", k = 4
 * Output: 1
 * 
 * Note:
 * 1 <= s.length <= 10^5
 * s consists of lowercase English letters.
 * 1 <= k <= s.length
 */
#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
    int maxVowels(string s, int k) {
        int n = s.size();
        int maxVowels = 0, currentVowels = 0;

        // Helper function to check if a character is a vowel
        auto isVowel = [](char c) -> bool {
            return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
        };

        // Count vowels in the first window of length k
        for (int i = 0; i < k; ++i) {
            if (isVowel(s[i])) currentVowels++;
        }
        maxVowels = currentVowels;

        // Slide the window over the rest of the string
        for (int i = k; i < n; ++i) {
            // Remove the leftmost character of the previous window
            if (isVowel(s[i - k])) currentVowels--;
            // Add the new character at the right
            if (isVowel(s[i])) currentVowels++;
            maxVowels = max(maxVowels, currentVowels);
        }

        return maxVowels;
    }
};
