/*
 * 758. Bold Words in String
 *
 * Given a set of keywords words and a string S, make all appearances of all keywords in S bold. Any letters between <b> and </b> tags become bold.
 * 
 * The returned string should use the least number of tags possible, and of course the tags should form a valid combination.
 * 
 * For example, given that words = ["ab", "bc"] and S = "aabcd", we should return "a<b>abc</b>d". Note that returning "a<b>a<b>b</b>c</b>d" would use more tags, so it is incorrect.
 * 
 * Note:
 * 1. words has length in range [0, 50].
 * 2. words[i] has length in range [1, 10].
 * 3. S has length in range [0, 500].
 * 4. All characters in words[i] and S are lowercase letters.
 * 
 */
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    string boldWords(vector<string>& words, string S) {
        int n = S.size();
        vector<bool> bold(n, false);

        // Mark all positions that should be bold
        for (const string& w : words) {
            size_t pos = 0;
            while ((pos = S.find(w, pos)) != string::npos) {
                for (size_t i = pos; i < pos + w.size(); ++i) {
                    bold[i] = true;
                }
                pos += 1; // move forward to find overlapping occurrences
            }
        }

        // Build the result string with <b> and </b> tags
        string res;
        for (int i = 0; i < n; ++i) {
            if (bold[i] && (i == 0 || !bold[i - 1])) {
                res += "<b>";
            }
            res += S[i];
            if (bold[i] && (i == n - 1 || !bold[i + 1])) {
                res += "</b>";
            }
        }
        return res;
    }
};