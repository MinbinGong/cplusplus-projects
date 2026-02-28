/*
 * 1178. Number of Valid Words for Each Puzzle
 * 
 * With respect to a given puzzle string, a word is valid if both the following conditions are satisfied:
 * word contains the first letter of puzzle.
 * For each letter in word, that letter is in puzzle.
 * For example, if the puzzle is "abcdefg", then valid words are "faced", "cabbage", and "baggage"; while invalid words are "beefed" (doesn't include "a") and "based" (includes "s" which isn't in the puzzle).
 * Return an array answer, where answer[i] is the number of words in the given word list words that are valid with respect to the puzzle puzzles[i].
 * 
 * Example :
 * Input: words = ["aaaa","asas","able","ability","actt","actor","access"], puzzles = ["aboveyz","abrodyz","abslute","absoryz","actresz","gaswxyz"]
 * Output: [1,1,3,2,4,0]
 * Explantion:
 * 1) "aboveyz" contains the first letter 'a', and "aaaa" is a valid word.
 * 2) "abrodyz" contains the first letter 'a', and "aaaa" is a valid word.
 * 3) "abslute" contains the first letter 'a', and "aaaa" is a valid word.
 * 4) "absoryz" contains the first letter 'a', and "aaaa" is a valid word.
 * 5) "actresz" contains the first letter 'a', and "aaaa" is a valid word.
 * 6) "gaswxyz" doesn't contain the first letter 'a', and none of the words in the list is valid.
 * 
 * Note:
 * 1 <= words.length <= 10^5
 * 4 <= words[i].length <= 50
 * 1 <= puzzles.length <= 10^4
 * puzzles[i].length == 7
 * words[i][j], puzzles[i][j] are English lowercase letters.
 * Each puzzles[i] doesn't contain repeated characters.
 */
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<int> findNumOfValidWords(vector<string>& words, vector<string>& puzzles) {
        // frequency map for word masks
        unordered_map<int, int> freq;
        for (const string& w : words) {
            int mask = 0;
            for (char c : w) {
                mask |= 1 << (c - 'a');
            }
            freq[mask]++;
        }

        vector<int> result;
        for (const string& p : puzzles) {
            int first = 1 << (p[0] - 'a');          // mandatory first letter
            int puzzleMask = 0;
            for (char c : p) {
                puzzleMask |= 1 << (c - 'a');
            }
            int rest = puzzleMask ^ first;           // bits of the other 6 letters

            int count = 0;
            int sub = rest;
            do {
                int mask = sub | first;               // subset that includes first letter
                auto it = freq.find(mask);
                if (it != freq.end()) {
                    count += it->second;
                }
                if (sub == 0) break;
                sub = (sub - 1) & rest;               // next subset
            } while (true);

            result.push_back(count);
        }
        return result;
    }
};