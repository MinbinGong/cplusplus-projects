/*
 * 1165. Single-Row Keyboard
 *
 * There is a special keyboard with all keys in a single row.
 *
 * Given a string keyboard of length 26 indicating the layout of the keyboard (indexed from 0 to 25), initially your finger is at index 0. To type a character, you have to move your finger to the index of the desired character. The time taken to move your finger from index i to index j is |i - j|.
 *
 * You want to type a string word. Write a function to calculate how much time it takes to type it with one finger.
 *
 * Example 1:
 * Input: keyboard = "abcdefghijklmnopqrstuvwxyz", word = "cba"
 * Output: 4
 * Explanation: The index moves from 0 to 2 to write 'c' then to 1 to write 'b' then to 0 again to write 'a'.
 * Total time = 2 + 1 + 1 = 4.
 *
 * Example 2:
 * Input: keyboard = "pqrstuvwxyzabcdefghijklmno", word = "leetcode"
 * Output: 73
 *
 * Note:
 * 1 <= keyboard.length <= 26
 * keyboard contains each English lowercase letter exactly once in some order.
 * 1 <= word.length <= 10^4
 * word contains only English lowercase letters.
 *
 */
#include <string>
#include <vector>
#include <cstdlib>   // for abs

class Solution {
public:
    int calculateTime(std::string keyboard, std::string word) {
        // Record the position of each character
        int pos[26];
        for (int i = 0; i < 26; ++i) {
            pos[keyboard[i] - 'a'] = i;
        }
        
        int total = 0;
        int prev = 0; // finger starts at index 0
        
        for (char c : word) {
            int cur = pos[c - 'a'];
            total += std::abs(cur - prev);
            prev = cur;
        }
        
        return total;
    }
};