/**
 * 830. Positions of Large Groups
 *
 * In a string S of lowercase letters, these letters form consecutive groups of the same character.
 *
 * For example, a string like S = "abbxxxxzyy" has the groups "a", "bb", "xxxx", "z" and "yy".
 *
 * Call a group large if it has 3 or more characters.  We would like the starting and ending positions of every large group.
 *
 * The final answer should be in lexicographic order.
 *
 * Example:
 * Input: "abbxxxxzzy"
 * Output: [[3,6]]
 * Explanation: "xxxx" is the single large group with starting  3 and ending positions 6.
 *
 * Input: "abc"
 * Output: []
 * Explanation: We have "a","b" and "c" but no large group.
 *
 * Input: "abcdddeeeeaabbbcd"
 * Output: [[3,5],[6,9],[12,14]]
 * Explanation: We have "ddd", "eee" and "bbb" for the 3 large groups with starting and ending positions 3, 5, 6 respectively.
 *
 * Note:  1 <= S.length <= 1000
 *
 */
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    vector<vector<int>> largeGroupPositions(string s) {
        vector<vector<int>> res;
        int n = s.size();
        int i = 0;
        while (i < n) {
            int j = i;
            while (j < n && s[j] == s[i]) ++j;
            if (j - i >= 3) {
                res.push_back({i, j - 1});
            }
            i = j;
        }
        return res;
    }
};