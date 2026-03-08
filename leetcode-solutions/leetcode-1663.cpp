/*
 * 1663. Smallest String With A Given Numeric Value
 *
 * The numeric value of a lowercase character is defined as its position (1-indexed) in the alphabet, so the numeric value of a is 1, the numeric value of b is 2, the numeric value of c is 3, and so on.
 * The numeric value of a string consisting of lowercase characters is defined as the sum of its characters' numeric values. For example, the numeric value of the string "abe" is equal to 1 (for a) + 2 (for b) + 5 (for e) = 8.
 * 
 * You are given two integers n and k. Return the lexicographically smallest string with length equal to n and numeric value equal to k.
 * 
 * Example 1:
 * Input: n = 3, k = 27
 * Output: "aay"
 * Explanation: The numeric value of the string is 1 + 1 + 25 = 27, and it is the smallest string with such a value.
 * 
 * Example 2:
 * Input: n = 5, k = 73
 * Output: "aaszz"
 * Explanation: The numeric value of the string is 1 + 1 + 1 + 25 + 26 = 73, and it is the smallest string with such a value.
 * 
 * Constraints:
 * 1 <= n <= 105
 * n <= k <= 26 * n
 * 
 */
#include <string>
using namespace std;

class Solution {
public:
    string getSmallestString(int n, int k) {
        string ans(n, 'a');      // start with all 'a's (each contributes 1)
        k -= n;                   // remaining sum to distribute

        // Traverse from the last character to the first
        for (int i = n - 1; i >= 0 && k > 0; --i) {
            int add = min(25, k); // maximum we can add to this position (a=1 -> z=26)
            ans[i] += add;         // increase character value
            k -= add;              // reduce remaining sum
        }
        return ans;
    }
};