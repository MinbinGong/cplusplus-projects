/*
 * Shortest Completing Word
 *
 * Find the minimum length word from a given dictionary words, which has all the letters from the string licensePlate.
 * 
 * 
 * Example 1:
 * 
 * Input: licensePlate = "1s3 PSt", words = ["step", "steps", "stripe", "stepple"]
 * Output: "steps"
 * Explanation: The smallest length word that contains the letters "S", "P", "S", and "T".
 * Note that the answer is not "step", because the letter "s" must occur in the word twice.
 * Also note that we ignored case for the purposes of comparing whether a letter exists in the word.
 * 
 * Example 2:
 * 
 * Input: licensePlate = "1s3 456", words = ["looks", "pest", "stew", "show"]
 * Output: "pest"
 * Explanation: There are 3 smallest length words that contains the letters "s".
 * We return the one that occurred first.
 * 
 * Note:
 * 1. licensePlate will be a string with length in range [1, 7].
 * 2. licensePlate will contain digits, spaces, or letters (uppercase or lowercase).
 * 3. words will have a length in the range [10, 1000].
 * 4. Every words[i] will consist of lowercase letters, and have length in range [1, 15].
 * 
 */
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    string shortestCompletingWord(string licensePlate, vector<string>& words) {
        // Step 1: count letters in license plate (case-insensitive, ignore digits)
        int required[26] = {0};
        for (char ch : licensePlate) {
            if (isalpha(ch)) {
                required[tolower(ch) - 'a']++;
            }
        }

        string result;
        int minLen = INT_MAX;

        // Step 2: check each word
        for (const string& word : words) {
            int wordCount[26] = {0};
            for (char ch : word) {
                wordCount[tolower(ch) - 'a']++;
            }

            // Check if word satisfies all required counts
            bool ok = true;
            for (int i = 0; i < 26; ++i) {
                if (wordCount[i] < required[i]) {
                    ok = false;
                    break;
                }
            }

            if (ok) {
                if (word.length() < minLen) {
                    minLen = word.length();
                    result = word;
                }
            }
        }

        return result;
    }
};