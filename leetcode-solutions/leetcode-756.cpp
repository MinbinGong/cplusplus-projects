/*
 * 756. Pyramid Transition Matrix
 *
 * We are stacking blocks to form a pyramid. Each block has a color which is a one letter string, like `'Z'`.
 * 
 * For every block of color `C` we place not in the bottom row, we are placing it on top of a left block of color `A` and right block of color `B`. We are allowed to place the block there only if `(A, B, C)` is an allowed triple.
 * 
 * We start with a bottom row of bottom, represented as a single string. We also start with a list of allowed triples allowed. Each allowed triple is represented as a string of length 3.
 * 
 * Return true if we can build the pyramid all the way to the top, otherwise false.
 * 
 * Example 1:
 * 
 * Input: bottom = "XYZ", allowed = ["XYD", "YZE", "DEA", "FFF"]
 * Output: true
 * Explanation:
 * We can stack the pyramid like this:
 *     A
 *    / \
 *   D   E
 *  / \ / \
 * Z   Y   X
 * 
 * We have to start with the bottom row: we have to place a block of color X on top of both blocks of color Y. And then, we place a block of color Y on top of both blocks of color Z. And finally, we place a block of color D on top of both blocks of color E.
 * 
 * Example 2:
 * 
 * Input: bottom = "XXYX", allowed = ["XXX", "XXY", "XYX", "XYY", "YXZ"]
 * Output: false
 * Explanation:
 * We can't stack the pyramid to the top.
 * Note that there could be allowed triples (A, B, C) and (A, B, D) with C != D.
 * 
 * Note:
 * 1. bottom will be a string with length in range [2, 8].
 * 2. allowed will have length in range [0, 200].
 * 3. Letters in all strings will be chosen from the set {'A', 'B', 'C', 'D', 'E', 'F', 'Z'}.
 * 
 */
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Solution {
public:
    bool pyramidTransition(string bottom, vector<string>& allowed) {
        // Map each bottom pair to the list of possible top blocks
        unordered_map<string, vector<char>> mp;
        for (const string& s : allowed) {
            string key = s.substr(1, 2);   // left and right block in the lower row
            mp[key].push_back(s[0]);        // top block above them
        }
        unordered_set<string> memo;          // rows that are already known to be impossible
        return dfs(bottom, mp, memo);
    }

private:
    bool dfs(const string& row,
             unordered_map<string, vector<char>>& mp,
             unordered_set<string>& memo) {
        if (row.size() == 1) return true;          // reached the top
        if (memo.count(row)) return false;          // already proved impossible

        // Try to build the next row by considering each adjacent pair
        if (buildNext(row, 0, "", mp, memo))
            return true;

        memo.insert(row);   // all attempts failed → this row cannot lead to a pyramid
        return false;
    }

    bool buildNext(const string& row, int idx, string next,
                   unordered_map<string, vector<char>>& mp,
                   unordered_set<string>& memo) {
        if (idx == row.size() - 1) {                 // finished constructing the next row
            return dfs(next, mp, memo);
        }

        string key = row.substr(idx, 2);              // the current pair (left, right)
        if (!mp.count(key)) return false;             // no possible top block → dead end

        for (char c : mp[key]) {
            if (buildNext(row, idx + 1, next + c, mp, memo))
                return true;
        }
        return false;
    }
};