/*
 * Longest Word in Dictionary through Deleting
 *
 * Given a string s and a string array dictionary, return the longest string in the dictionary that can be formed by deleting some of the given string characters. If there is more than one possible result, return the longest word with the smallest lexicographical order. If there is no possible result, return the empty string.
 * 
 * Constraints:
 * 1 <= s.length <= 1000
 * 1 <= dictionary.length <= 1000
 * 1 <= dictionary[i].length <= 1000
 * s and dictionary[i] consist of lowercase English letters.
 * 
 */
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    string findLongestWord(string s, vector<string>& dictionary) {
        string best = "";
        for (const string& word : dictionary) {
            if (isSubsequence(word, s)) {
                if (word.length() > best.length() || 
                    (word.length() == best.length() && word < best)) {
                    best = word;
                }
            }
        }
        return best;
    }
    
private:
    bool isSubsequence(const string& word, const string& s) {
        int i = 0, j = 0;
        while (i < word.size() && j < s.size()) {
            if (word[i] == s[j]) i++;
            j++;
        }
        return i == word.size();
    }
};