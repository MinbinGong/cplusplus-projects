/**
 * 884. Uncommon Words from Two Sentences
 *
 * We are given two sentences A and B. (A sentence is a string of space separated words. Each word consists only of lowercase letters.)
 * A word is uncommon if it appears exactly once in one of the sentences, and does not appear in the other sentence.
 * Return a list of all uncommon words.
 * You may return the list in any order.
 *
 * Example 1:
 * Input: A = "this apple is sweet", B = "this apple is sour"
 * Output: ["sweet","sour"]
 *
 * Example 2:
 * Input: A = "apple apple", B = "banana"
 * Output: ["banana"]
 *
 * Note:
 * 0 <= A.length <= 200
 * 0 <= B.length <= 200
 * A and B both contain only spaces and lowercase letters.
 * 
 */
#include <vector>
#include <string>
#include <unordered_map>
#include <sstream>
using namespace std;

class Solution {
public:
    vector<string> uncommonFromSentences(string s1, string s2) {
        unordered_map<string, int> freq;
        istringstream iss(s1 + " " + s2);
        string word;
        while (iss >> word) {
            freq[word]++;
        }
        vector<string> res;
        for (auto& p : freq) {
            if (p.second == 1) {
                res.push_back(p.first);
            }
        }
        return res;
    }
};