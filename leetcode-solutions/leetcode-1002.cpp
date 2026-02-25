/*
 * 1002. Find Common Characters
 *
 * Given an array A of strings made only from lowercase letters, return a list of all characters that show up in all strings within the list (including duplicates).  For example, if a character occurs 3 times in all strings but not 4 times, you need to include that character three times in the final answer.
 *
 * You may return the answer in any order.
 *
 * Example 1:
 *
 * Input: ["bella","label","roller"]
 * Output: ["e","l","l"]
 * 
 * Example 2:
 *
 * Input: ["cool","lock","cook"]
 * Output: ["c","o"]
 * 
 * Note:
 *
 * 1 <= A.length <= 100
 * 1 <= A[i].length <= 100
 * A[i][j] is a lowercase letter
 * 
 */
#include <vector>
#include <string>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    vector<string> commonChars(vector<string>& words) {
        // common frequency for each character, initialized to large number
        vector<int> common(26, INT_MAX);

        for (const string& w : words) {
            vector<int> freq(26, 0);
            for (char c : w) {
                ++freq[c - 'a'];
            }
            // update common to be the min of current and new frequencies
            for (int i = 0; i < 26; ++i) {
                common[i] = min(common[i], freq[i]);
            }
        }

        vector<string> result;
        for (int i = 0; i < 26; ++i) {
            for (int j = 0; j < common[i]; ++j) {
                result.push_back(string(1, 'a' + i));
            }
        }
        return result;
    }
};