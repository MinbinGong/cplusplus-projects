/*
 * Generalized Abbreviation
 * 
 * Write a function to generate the generalized abbreviations of a word.
 * 
 * Example 1:
 * Input: word = "word"
 * Output: ["word","1ord","w1rd","wo1d","wor1","2rd","w2d","wo2","1o1d","1or1","w1r1","1o2","2r1","3d","w3","4"]
 * 
 * Example 2:
 * Input: word = "a"
 * Output: ["a","1"]
 * 
 */
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    vector<string> generateAbbreviations(string word) {
        vector<string> result;
        string current;
        backtrack(word, 0, current, 0, result);
        return result;
    }

private:
    void backtrack(const string& word, int pos, string& current, int count, vector<string>& result) {
        if (pos == word.size()) {
            if (count > 0) {
                current += to_string(count);
            }
            result.push_back(current);
            // revert the change if any
            if (count > 0) {
                current.erase(current.size() - to_string(count).size());
            }
            return;
        }

        // Option 1: abbreviate current character (increase count)
        backtrack(word, pos + 1, current, count + 1, result);

        // Option 2: keep current character (flush count first)
        // Save current length to revert later
        int len = current.size();
        if (count > 0) {
            current += to_string(count);
        }
        current += word[pos];
        backtrack(word, pos + 1, current, 0, result);
        // Restore
        current.erase(len);
    }
};