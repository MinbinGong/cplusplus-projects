/*
 * 792. Number of Matching Subsequences
 *
 * Given string S and a dictionary of words words, find the number of words[i] that is a subsequence of S.
 * 
 * Example :
 * Input: 
 * S = "abcde"
 * words = ["a", "bb", "acd", "ace"]
 * Output: 3
 * Explanation: There are three words in words that are a subsequence of S: "a", "acd", "ace".
 * 
 * Note:
 * 1. All words in words and S will only consists of lowercase letters.
 * 2. The length of S will be in the range of [1, 50000].
 * 3. The length of words will be in the range of [1, 5000].
 * 4. The length of words[i] will be in the range of [1, 50].
 * 
 */
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    int numMatchingSubseq(string s, vector<string>& words) {
        // waiting[ch] : list of (word_index, next_position_in_word) that are waiting for character ch
        vector<vector<pair<int, int>>> waiting(26);
        for (int i = 0; i < words.size(); ++i) {
            waiting[words[i][0] - 'a'].emplace_back(i, 0);
        }

        int ans = 0;
        for (char c : s) {
            // take all words waiting for the current character c
            auto vec = waiting[c - 'a'];
            waiting[c - 'a'].clear(); // clear the bucket for this character

            for (auto [idx, pos] : vec) {
                ++pos; // move to the next character in the word
                if (pos == words[idx].size()) {
                    // the whole word is matched
                    ++ans;
                } else {
                    // still need more characters – put it into the bucket for the next required character
                    waiting[words[idx][pos] - 'a'].emplace_back(idx, pos);
                }
            }
        }
        return ans;
    }
};