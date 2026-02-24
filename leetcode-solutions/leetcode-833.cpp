/**
 * 833. Find And Replace in String
 * 
 * To some string S, we will perform some replacement operations that replace groups of letters with new ones (not necessarily the same size).
 * 
 * Each replacement operation has 3 parameters: a starting index i, a source word x and a target word y.  The rule is that if x starts at position i in the original string S, then we will replace that occurrence of x with y.  If not, we do nothing.
 * 
 * For example, if we have S = "abcd" and we have some replacement operation i = 2, x = "cd", y = "ffff", then because "cd" starts at position 2 in the original string S, we will replace it with "ffff".
 * 
 * Using another example on S = "abcd", if we have both the replacement operation i = 0, x = "ab", y = "eee", as well as another replacement operation i = 2, x = "ec", y = "ffff", this second operation does nothing because in the original string S[2] = 'c', which doesn't match x[0] = 'e'.
 * 
 * Example:
 * Input: S = "abcd", indexes = [0,2], sources = ["a","cd"], targets = ["eee","ffff"]
 * Output: "eeebffff"
 * Explanation: "a" starts at index 0 in S, so it's replaced by "eee".
 * "cd" starts at index 2 in S, so it's replaced by "ffff".
 * 
 * Input: S = "abcd", indexes = [0,2], sources = ["ab","ec"], targets = ["eee","ffff"]
 * Output: "eeecd"
 * Explanation: "ab" starts at index 0 in S, so it's replaced by "eee".
 * "ec" doesn't starts at index 2 in the original S, so we do nothing.
 * 
 * Note:
 * 1 <= S.length <= 1000
 * 0 <= indexes.length <= 100
 * 0 <= indexes[i] < S.length
 * All characters in given inputs are lowercase letters.
 * 
 */
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    string findReplaceString(string s, vector<int>& indices, vector<string>& sources, vector<string>& targets) {
        int n = s.size();
        unordered_map<int, pair<string, string>> mp;
        for (int i = 0; i < indices.size(); ++i) {
            mp[indices[i]] = {sources[i], targets[i]};
        }
        string result;
        for (int i = 0; i < n; ) {
            if (mp.count(i)) {
                auto& [src, tgt] = mp[i];
                if (s.substr(i, src.size()) == src) {
                    result += tgt;
                    i += src.size();
                } else {
                    result += s[i];
                    ++i;
                }
            } else {
                result += s[i];
                ++i;
            }
        }
        return result;
    }
};