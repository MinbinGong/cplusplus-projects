/*
 * Detect Capital
 *
 * We define the usage of capitals in a word to be right when one of the following cases holds:
 * 
 * All letters in this word are capitals, like "USA".
 * All letters in this word are not capitals, like "leetcode".
 * Only the first letter in this word is capital, like "Google".
 * Given a string word, return true if the usage of capitals in it is right.
 * 
 * Constraints:
 * 1 <= word.length <= 100
 * word consists of lowercase and uppercase English letters.
 * 
 */
#include <string>
using namespace std;

class Solution {
public:
    bool detectCapitalUse(string word) {
        int capitals = 0;
        for (char c : word) {
            if (isupper(c)) capitals++;
        }
        
        if (capitals == word.length()) return true;          // all uppercase
        if (capitals == 0) return true;                      // all lowercase
        if (capitals == 1 && isupper(word[0])) return true;  // only first capital
        
        return false;
    }
};