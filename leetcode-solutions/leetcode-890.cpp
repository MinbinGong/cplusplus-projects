/**
 * 890. Find and Replace Pattern
 *
 * You have a list of words and a pattern, and you want to know which words in words matches the pattern.
 * A word matches the pattern if there exists a permutation of letters p so that after replacing every letter x in the pattern with p(x), we get the desired word.
 * (Recall that a permutation of letters is a bijection from letters to letters: every letter maps to another letter, and no two letters map to the same letter.)
 * Return a list of the words in words that match the given pattern.
 * You may return the answer in any order.
 *
 * Example 1:
 * Input: words = ["abc","deq","mee","aqq","dkd","ccc"], pattern = "abb"
 * Output: ["mee","aqq"]
 * Explanation: "mee" matches the pattern because there is a permutation {a -> m, b -> e, ...}.
 * "ccc" does not match the pattern because {a -> c, b -> c, ...} is not a permutation,
 * since a and b map to the same letter.
 * 
 * Example 2:
 * Input: words = ["a","b","c"], pattern = "a"
 * Output: ["a","b","c"]
 * 
 * Note:
 * 1 <= words.length <= 50
 * 1 <= pattern.length = words[i].length <= 20
 * 
 */
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

class Solution {
public:
    vector<string> findAndReplacePattern(vector<string>& words, string pattern) {
        vector<string> res;
        for (string& w : words) {
            if (match(w, pattern)) res.push_back(w);
        }
        return res;
    }

private:
    bool match(string& word, string& pattern) {
        vector<int> w2p(26, -1), p2w(26, -1);
        for (int i = 0; i < word.size(); ++i) {
            int wc = word[i] - 'a';
            int pc = pattern[i] - 'a';
            if (w2p[wc] != p2w[pc]) return false;
            w2p[wc] = i;
            p2w[pc] = i;
        }
        return true;
    }
};