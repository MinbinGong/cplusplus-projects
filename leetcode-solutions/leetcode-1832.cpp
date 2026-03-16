/**
 * 1832. Check if the Sentence Is Pangram
 * https://leetcode.com/problems/check-if-the-sentence-is-pangram/
 * 
 * A pangram is a sentence where every letter of the English alphabet appears at least once.
 * 
 * Given a string sentence containing only lowercase English letters, return true if sentence is a pangram, or false otherwise.
 * 
 * Example 1:
 * Input: sentence = "thequickbrownfoxjumpsoverthelazydog"
 * Output: true
 * Explanation: sentence contains at least one of every letter of the English alphabet.
 * 
 * Example 2:
 * Input: sentence = "leetcode"
 * Output: false
 * 
 * Constraints:
 * 1 <= sentence.length <= 1000
 * sentence consists of lowercase English letters.
 */
#include <vector>
using namespace std;

class Solution {
public:
    bool checkIfPangram(string sentence) {
        vector<bool> seen(26, false);
        int count = 0; // number of distinct letters seen
        
        for (char c : sentence) {
            int idx = c - 'a';
            if (!seen[idx]) {
                seen[idx] = true;
                count++;
            }
            if (count == 26) return true; // early exit
        }
        
        return count == 26;
    }
};