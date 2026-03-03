/**
 * 1451. Rearrange Words in a Sentence
 * 
 * Given a sentence text (A sentence is a string of space-separated words) in the following format:
 * 
 * First letter is in upper case.
 * Each word in text are separated by a single space.
 * Your task is to rearrange the words in text such that all words are rearranged in an increasing order of their lengths. If two words have the same length, arrange them in their original order.
 * 
 * Return the new text following the format shown above.
 * 
 * Example 1:
 * 
 * Input: text = "Leetcode is cool"
 * Output: "Is cool leetcode"
 * Explanation: There are 3 words, "Leetcode" of length 8, "is" of length 2 and "cool" of length 4.
 * Output is ordered by length and the new first word starts with capital letter.
 * 
 * Example 2:
 * 
 * Input: text = "Keep calm and code on"
 * Output: "On and keep calm code"
 * Explanation: Output is ordered as follows:
 * "On" 2 letters.
 * "and" 3 letters.
 * "keep" 4 letters in case of tie order by position in original text.
 * "calm" 4 letters.
 * "code" 4 letters.
 * 
 * Example 3:
 * 
 * Input: text = "To be or not to be"
 * Output: "To be or to be not"
 * 
 * Note:
 * text begins with a capital letter and then contains lowercase letters and single space between words.
 * 1 <= text.length <= 10^5
 * 
 */
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

class Solution {
public:
    string arrangeWords(string text) {
        // Split the text into words
        vector<string> words;
        istringstream iss(text);
        string word;
        while (iss >> word) {
            words.push_back(word);
        }

        // Stable sort by word length (preserves original order for equal lengths)
        stable_sort(words.begin(), words.end(),
                    [](const string& a, const string& b) {
                        return a.size() < b.size();
                    });

        // Adjust cases according to the rule
        if (!words.empty()) {
            // First word: first letter uppercase, rest lowercase (as per original)
            words[0][0] = toupper(words[0][0]);
            for (size_t i = 1; i < words.size(); ++i) {
                words[i][0] = tolower(words[i][0]);
            }
        }

        // Rebuild the sentence
        string result;
        for (size_t i = 0; i < words.size(); ++i) {
            if (i > 0) result += " ";
            result += words[i];
        }
        return result;
    }
};