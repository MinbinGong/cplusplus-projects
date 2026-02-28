/*
 * 1181. Before and After Puzzle
 * 
 * Given a list of phrases, generate a list of Before and After puzzles.
 * 
 * A phrase is a string that consists of lowercase English letters and spaces only. No space appears in the start or the end of a phrase. There are no consecutive spaces in a phrase.
 * 
 * Before and After puzzles are phrases that are formed by merging two phrases where the last word of the first phrase is the same as the first word of the second phrase.
 * 
 * Return the Before and After puzzles that can be formed by every two phrases phrases[i] and phrases[j] where i != j. Note that the order of matching two phrases matters, we want to consider both orders.
 * 
 * You should return a list of distinct strings sorted lexicographically.
 * 
 * Example 1:
 * Input: phrases = ["writing code","code rocks"]
 * Output: ["writing code rocks"]
 * 
 * Example 2:
 * Input: phrases = ["mission statement",
 *                   "a quick bite to eat",
 *                   "a chip off the old block",
 *                   "chocolate bar",
 *                   "mission impossible"]
 * Output: ["a chip off the old block mission impossible",
 *          "a quick bite to eat chocolate bar",
 *          "chocolate bar mission impossible",
 *          "mission impossible",
 *          "mission statement a quick bite to eat",
 *          "mission statement a chip off the old block"]
 * 
 * Example 3:
 * Input: phrases = ["a","b","a"]
 * Output: ["a","a"]
 * 
 * Note:
 * 1 <= phrases.length <= 100
 * 1 <= phrases[i].length <= 100
 */
#include <vector>
#include <string>
#include <set>

using namespace std;

class Solution {
public:
    vector<string> beforeAndAfterPuzzles(vector<string>& phrases) {
        int n = phrases.size();
        vector<string> firsts(n), lasts(n);
        
        // Extract first and last word for each phrase
        for (int i = 0; i < n; ++i) {
            size_t firstSpace = phrases[i].find(' ');
            if (firstSpace == string::npos) {
                firsts[i] = phrases[i];
                lasts[i] = phrases[i];
            } else {
                firsts[i] = phrases[i].substr(0, firstSpace);
                size_t lastSpace = phrases[i].rfind(' ');
                lasts[i] = phrases[i].substr(lastSpace + 1);
            }
        }
        
        set<string> resultSet;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == j) continue;
                if (lasts[i] == firsts[j]) {
                    // Combine: phrase i + rest of phrase j after its first word
                    string rest = phrases[j].substr(firsts[j].size()); // includes leading space if any
                    resultSet.insert(phrases[i] + rest);
                }
            }
        }
        
        return vector<string>(resultSet.begin(), resultSet.end());
    }
};