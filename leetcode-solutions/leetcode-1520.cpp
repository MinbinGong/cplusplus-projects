/*
 * 1520. Maximum Number of Non-Overlapping Substrings
 *
 * Given a string s of lowercase letters, you need to find the maximum number of non-empty substrings of s that meet the following conditions:
 *
 * The substrings do not overlap, that is for any two substrings s[i..j] and s[k..l], either j < k or i > l is true.
 * A substring that contains a certain character c must also contain all occurrences of c.
 * Find the maximum number of substrings that meet the above conditions. If there are multiple solutions with the same number of substrings, return the one with minimum total length. It can be shown that there exists a unique solution of minimum total length.
 *
 * Notice that you can return the substrings in any order.
 *
 * Example 1:
 * Input: s = "adefaddaccc"
 * Output: ["e","f","ccc"]
 * Explanation: The following are all the possible substrings that meet the conditions:
 * [
 *   "adefaddaccc"
 *   "adefadda",
 *   "ef",
 *   "ccc"
 * ]
 * 
 * Example 2:
 * Input: s = "abbaccd"
 * Output: ["d","bb","cc"]
 * Explanation: The following are all the possible substrings that meet the conditions:
 * [
 *   "abbaccd"
 *   "bb",
 *   "cc"
 * ]
 * 
 * Constraints:
 * 1 <= s.length <= 10^5
 * s contains only lowercase English letters.
 * 
 */
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<string> maxNumOfSubstrings(string s) {
        int n = s.size();
        // first and last occurrence for each character
        vector<int> first(26, n);
        vector<int> last(26, -1);

        for (int i = 0; i < n; ++i) {
            int c = s[i] - 'a';
            first[c] = min(first[c], i);
            last[c] = max(last[c], i);
        }

        // collect all valid intervals [l, r]
        vector<pair<int, int>> intervals;

        for (int i = 0; i < n; ++i) {
            int c = s[i] - 'a';
            if (i != first[c]) continue;   // only start at first occurrence

            int r = last[c];
            bool valid = true;
            for (int j = i; j <= r; ++j) {
                int cur = s[j] - 'a';
                if (first[cur] < i) {       // character appears before i → impossible
                    valid = false;
                    break;
                }
                r = max(r, last[cur]);       // expand right bound if needed
            }
            if (valid) {
                intervals.emplace_back(i, r);
            }
        }

        // greedy selection: sort by right endpoint, pick non‑overlapping
        sort(intervals.begin(), intervals.end(),
             [](const pair<int, int>& a, const pair<int, int>& b) {
                 return a.second < b.second;
             });

        vector<string> ans;
        int lastEnd = -1;
        for (auto [l, r] : intervals) {
            if (l > lastEnd) {
                ans.push_back(s.substr(l, r - l + 1));
                lastEnd = r;
            }
        }
        return ans;
    }
};