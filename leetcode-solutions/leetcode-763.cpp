/*
 * 763. Partition Labels
 *
 * A string S of lowercase letters is given. We want to partition this string into as many parts as possible so that each letter appears in at most one part, and return a list of integers representing the size of these parts.
 * 
 * Example 1:
 * Input: S = "ababcbacadefegdehijhklij"
 * Output: [9,7,8]
 * Explanation:
 * The partition is "ababcbaca", "defegde", "hijhklij".
 * 
 * Note:
 * 1. S will have length in range [1, 500].
 * 2. S will consist of lowercase letters ('a' to 'z') only.
 * 
 */
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    vector<int> partitionLabels(string s) {
        vector<int> last(26, 0);
        // Record the last occurrence of each character
        for (int i = 0; i < s.size(); ++i) {
            last[s[i] - 'a'] = i;
        }

        vector<int> result;
        int start = 0, end = 0;
        for (int i = 0; i < s.size(); ++i) {
            end = max(end, last[s[i] - 'a']);
            if (i == end) {
                result.push_back(end - start + 1);
                start = i + 1;
            }
        }
        return result;
    }
};