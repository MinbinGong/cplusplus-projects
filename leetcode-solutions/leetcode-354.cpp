/*
 * Russian Doll Envelopes
 * 
 * You are given a 2D array of integers envelopes where envelopes[i] = [wi, hi] represents the width and the height of an envelope.
 * 
 * One envelope can fit into another if and only if both the width and height of one envelope are greater than the other envelope's width and height.
 * 
 * Return the maximum number of envelopes you can Russian doll (i.e., put one inside the other).
 * 
 * Note: You cannot rotate an envelope.
 * 
 * Example 1:
 * Input: envelopes = [[5,4],[6,4],[6,7],[2,3]]
 * Output: 3
 * Explanation: The maximum number of envelopes you can Russian doll is 3 ([2,3] => [5,4] => [6,7]).
 * 
 * Example 2:
 * Input: envelopes = [[1,1],[1,1],[1,1]]
 * Output: 1
 * 
 * Constraints:
 * 1 <= envelopes.length <= 105
 * envelopes[i].length == 2
 * 1 <= wi, hi <= 105
 * 
 */
// #include <algorithm>
// #include <utility>
// #include <vector>
// using namespace std;

// int help(vector<pair<int, int>> &envelopes) {
//   sort(envelopes.begin(), envelopes.end(),
//        [](auto &p1, auto &p2) { return p1.first < p2.first || (p1.first == p2.first && p1.second > p2.second); });
//
//   vector<int> col;
//   for (auto &pair : envelopes) {
//     auto it = lower_bound(col.begin(), col.end(), pair.second);
//     if (it == col.end())
//       col.push_back(pair.second);
//     else if (*it > pair.second)
//       *it = pair.second;
//   }
//   return col.size();
// }
//
// int maxEnvelopes(vector<vector<int>> &envelopes) {
//   vector<pair<int, int>> src{};
//   for (size_t i = 0; i < envelopes.size(); ++i) src.emplace_back(std::make_pair(envelopes[i][0], envelopes[i][1]));
//
//   return help(src);
// }

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        if (envelopes.empty()) return 0;
        // Sort by width ascending, and if same width, height descending
        sort(envelopes.begin(), envelopes.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[0] < b[0] || (a[0] == b[0] && a[1] > b[1]);
        });
        
        // Now find LIS on height
        vector<int> tails;
        for (const auto& env : envelopes) {
            int h = env[1];
            auto it = lower_bound(tails.begin(), tails.end(), h);
            if (it == tails.end()) {
                tails.push_back(h);
            } else {
                *it = h;
            }
        }
        return tails.size();
    }
};