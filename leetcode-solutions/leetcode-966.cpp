/*
 * 966. Vowel Spellchecker
 *
 * Given a wordlist, we want to implement a spellchecker that converts a query word into a correct word.
 *
 * For a given query word, the spell checker handles two categories of spelling mistakes:
 *
 * Capitalization: If the query matches a word in the wordlist (case-insensitive), then the query word is returned with the same case as the case in the wordlist.
 * Example: wordlist = ["yellow"], query = "YellOw": correct = "yellow"
 * Example: wordlist = ["Yellow"], query = "yellow": correct = "Yellow"
 * Example: wordlist = ["yellow"], query = "yellow": correct = "yellow"
 * Vowel Errors: If after replacing the vowels ('a', 'e', 'i', 'o', 'u') of the query word with any vowel individually, it matches a word in the wordlist (case-insensitive), then the query word is returned with the same case as the match in the wordlist.
 * Example: wordlist = ["YellOw"], query = "yollow": correct = "YellOw"
 * Example: wordlist = ["YellOw"], query = "yeellow": correct = "" (no match)
 * Example: wordlist = ["YellOw"], query = "yllw": correct = "" (no match)
 * In addition, the spell checker operates under the following precedence rules:
 *
 * When the query exactly matches a word in the wordlist (case-sensitive), you should return the same word back.
 * When the query matches a word up to capitlization, you should return the first such match in the wordlist.
 * When the query matches a word up to vowel errors, you should return the first such match in the wordlist.
 * 
 * Example 1:
 *
 * Input: wordlist = ["KiTe","kite","hare","Hare"], queries = ["kite","Kite","KiTe","Hare","HARE","Hear","hear","keti","keet","keto"]
 * Output: ["kite","KiTe","KiTe","Hare","hare","","","KiTe","","KiTe"]
 * 
 * Example 2:
 *
 * Input: wordlist = ["yellow"], queries = ["YellOw"]
 * Output: ["yellow"]
 * 
 * Note:
 *
 * 1 <= wordlist.length <= 5000
 * 1 <= queries.length <= 5000
 * 1 <= wordlist[i].length <= 7
 * 1 <= queries[i].length <= 7
 * All strings in wordlist and queries consist only of english letters.
 * 
 */
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<string> spellchecker(vector<string>& wordlist, vector<string>& queries) {
        unordered_set<string> exact;
        unordered_map<string, string> lower;
        unordered_map<string, string> vowel;

        // Helper to replace vowels
        auto toVowelKey = [](const string& s) {
            string key;
            for (char c : s) {
                char lower = tolower(c);
                if (lower == 'a' || lower == 'e' || lower == 'i' || lower == 'o' || lower == 'u')
                    key += '#';
                else
                    key += lower;
            }
            return key;
        };

        for (const string& w : wordlist) {
            exact.insert(w);
            string low = w;
            transform(low.begin(), low.end(), low.begin(), ::tolower);
            if (lower.find(low) == lower.end()) {
                lower[low] = w;
            }
            string vow = toVowelKey(w);
            if (vowel.find(vow) == vowel.end()) {
                vowel[vow] = w;
            }
        }

        vector<string> ans;
        for (const string& q : queries) {
            if (exact.count(q)) {
                ans.push_back(q);
                continue;
            }
            string low = q;
            transform(low.begin(), low.end(), low.begin(), ::tolower);
            auto it = lower.find(low);
            if (it != lower.end()) {
                ans.push_back(it->second);
                continue;
            }
            string vow = toVowelKey(q);
            auto it2 = vowel.find(vow);
            if (it2 != vowel.end()) {
                ans.push_back(it2->second);
                continue;
            }
            ans.push_back("");
        }
        return ans;
    }
};