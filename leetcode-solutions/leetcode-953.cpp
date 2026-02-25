/*
 * 953. Verifying an Alien Dictionary
 *
 * In an alien language, surprisingly, they also use English lowercase letters,
 * but possibly in a different order. The order of the alphabet is some permutation of lowercase letters.
 *
 * Given a sequence of words written in the alien language, and the order of the alphabet,
 * return true if and only if the given words are sorted lexicographically in this alien language.
 *
 * Example 1:
 *
 * Input: words = ["hello","leetcode"], order = "hlabcdefgijkmnopqrstuvwxyz"
 * Output: true
 * Explanation: As 'h' comes before 'l' in this language, then the sequence is sorted.
 *
 * Example 2:
 *
 * Input: words = ["word","world","row"], order = "worldabcefghijkmnpqstuvxyz"
 * Output: false
 * Explanation: As 'd' comes after 'l' in this language, then words[0] > words[1], hence the sequence is unsorted.
 *
 * Example 3:
 *
 * Input: words = ["apple","app"], order = "abcdefghijklmnopqrstuvwxyz"
 * Output: false
 * Explanation: The first three characters "app" match, and the second string is shorter (in size.)
 * According to lexicographical rules "apple" > "app", because 'l' > '∅',
 * where '∅' is defined as the blank character which is less than any other character (More info).
 *
 * Note:
 *
 * 1 <= words.length <= 100
 * 1 <= words[i].length <= 20
 * order.length == 26
 * All characters in words[i] and order are English lowercase letters.
 */
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    bool isAlienSorted(vector<string>& words, string order) {
        // Create a mapping from character to its index in the alien alphabet
        int rank[26];
        for (int i = 0; i < 26; ++i) {
            rank[order[i] - 'a'] = i;
        }

        // Compare each adjacent pair
        for (int i = 0; i < words.size() - 1; ++i) {
            const string &w1 = words[i];
            const string &w2 = words[i + 1];

            int len = min(w1.length(), w2.length());
            bool foundDiff = false;

            for (int j = 0; j < len; ++j) {
                char c1 = w1[j], c2 = w2[j];
                if (c1 != c2) {
                    if (rank[c1 - 'a'] > rank[c2 - 'a']) {
                        return false; // wrong order
                    }
                    foundDiff = true;
                    break;
                }
            }

            // If no difference found in the common prefix, check lengths
            if (!foundDiff && w1.length() > w2.length()) {
                return false; // first word is longer and a prefix => not sorted
            }
        }

        return true;
    }
};