/**
 * 1839. Longest Substring Of All Vowels in Order
 * https://leetcode.com/problems/longest-substring-of-all-vowels-in-order/
 * 
 * A string is considered beautiful if it satisfies the following conditions:
 * 
 * Each of the 5 English vowels ('a', 'e', 'i', 'o', 'u') must appear at least once in it.
 * The letters must be sorted in alphabetical order (i.e. all 'a's before 'e's, all 'e's before 'i's, etc.).
 * For example, strings "aeiou" and "aaaaaaeiiiioou" are considered beautiful, but "uaeio", "aeoiu", and "aaaeeeooo" are not beautiful.
 * 
 * Given a string word consisting of English vowels, return the length of the longest beautiful substring of word. If no such substring exists, return 0.
 * 
 * A substring is a contiguous sequence of characters in a string.
 * 
 * Example 1:
 * Input: word = "aeiaaioaaaaeiiiiouuuooaauuaeiu"
 * Output: 13
 * Explanation: The longest beautiful substring in word is "aaaaeiiiiouuu" of length 13.
 * 
 * Example 2:
 * Input: word = "aeeeiiiioooauuuaeiou"
 * Output: 5
 * Explanation: The longest beautiful substring in word is "aeiou" of length 5.
 * 
 * Example 3:
 * Input: word = "a"
 * Output: 0
 * Explanation: There is no beautiful substring, so return 0.
 * 
 * Constraints:
 * 1 <= word.length <= 5 * 105
 * word consists of characters 'a', 'e', 'i', 'o', and 'u'.
 * 
 */
#include <string>
using namespace std;

class Solution {
public:
    int longestBeautifulSubstring(string word) {
        int n = word.size();
        int max_len = 0;
        int i = 0;
        
        while (i < n) {
            if (word[i] != 'a') {
                ++i;
                continue;
            }
            
            int j = i;
            int last = 0;          // index of last vowel seen (0 = 'a')
            
            while (j < n) {
                char c = word[j];
                // Not a vowel -> break
                if (c != 'a' && c != 'e' && c != 'i' && c != 'o' && c != 'u')
                    break;
                
                int idx;
                if (c == 'a') idx = 0;
                else if (c == 'e') idx = 1;
                else if (c == 'i') idx = 2;
                else if (c == 'o') idx = 3;
                else idx = 4;
                
                if (idx < last) break;          // out of order
                if (idx > last + 1) break;      // skipped a vowel
                
                if (idx > last) last = idx;
                ++j;
                
                if (last == 4) {
                    max_len = max(max_len, j - i);
                }
            }
            
            // Move i to the next possible start
            if (j < n && word[j] != 'a' && word[j] != 'e' && word[j] != 'i' && word[j] != 'o' && word[j] != 'u') {
                i = j + 1;          // skip non‑vowel
            } else {
                i = j;               // start from the invalid vowel or end
            }
        }
        
        return max_len;
    }
};