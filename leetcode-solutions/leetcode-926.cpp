/*
 * Flip String to Monotone Increasing
 *
 * A string of '0's and '1's is monotone increasing if it consists of some number of '0's (possibly 0), followed by some number of '1's (also possibly 0.)
 *
 * We are given a string S of '0's and '1's, and we may flip any '0' to a '1' or a '1' to a '0'.
 *
 * Return the minimum number of flips to make S monotone increasing.
 *
 * Example 1:
 * Input: "00110"
 * Output: 1
 * Explanation: We flip the last digit to get 00111.
 *
 * Example 2:
 * Input: "010110"
 * Output: 2
 * Explanation: We flip to get 011111, or alternatively 000111.
 *
 * Example 3:
 * Input: "00011000"
 * Output: 2
 * Explanation: We flip to get 00000000.
 * 
 * Note:
 * 1 <= S.length <= 20000
 * S only consists of '0' and '1' characters.
 * 
 */
#include <string>
#include <climits>
using namespace std;

class Solution {
public:
    int minFlipsMonoIncr(string s) {
        int n = s.size();
        int total_ones = 0;
        for (char c : s) if (c == '1') total_ones++;
        int ans = INT_MAX;
        int ones_so_far = 0; // number of '1's in the first i characters
        for (int i = 0; i <= n; ++i) {
            // Let first i characters become 0, the rest become 1.
            // Flips needed = ones in left + zeros in right
            int flips = ones_so_far + (n - i - (total_ones - ones_so_far));
            ans = min(ans, flips);
            if (i < n && s[i] == '1') ++ones_so_far;
        }
        return ans;
    }
};