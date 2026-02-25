/*
 * 1027. Longest Arithmetic Sequence
 *
 * Given an array A of integers, return the length of the longest arithmetic subsequence in A.
 *
 * Recall that a subsequence of A is a list A[i_1], A[i_2], ..., A[i_k] with 0 <= i_1 < i_2 < ... < i_k <= A.length - 1, and that a sequence B is arithmetic if B[i+1] - B[i] are all the same value (for 0 <= i < B.length - 1).
 *
 * Example 1:
 *
 * Input: [3,6,9,12]
 * Output: 4
 * Explanation: 
 * The whole array is an arithmetic sequence with steps of length = 3.
 * 
 * Example 2:
 *
 * Input: [9,4,7,2,10]
 * Output: 3
 * Explanation: 
 * The longest arithmetic subsequence is [4,7,10].
 * 
 * Example 3:
 *
 * Input: [20,1,15,3,10,5,8]
 * Output: 4
 * Explanation: 
 * The longest arithmetic subsequence is [20,15,10,5].
 * 
 * Note:
 * 
 * 2 <= A.length <= 2000
 * 0 <= A[i] <= 10000
 * 
 */
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    int longestArithSeqLength(vector<int>& A) {
        int n = A.size();
        if (n < 2) return n;  // not needed due to constraints but safe

        // dp[i][diff] = length of longest arithmetic subsequence ending at i with difference diff
        vector<unordered_map<int, int>> dp(n);
        int maxLen = 2; // minimum possible length

        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                int diff = A[i] - A[j];
                // length ending at j with same diff, default to 1 (just A[j] itself)
                int len = 1; // actually subsequence of length 1 ending at j (starting point)
                auto it = dp[j].find(diff);
                if (it != dp[j].end()) {
                    len = it->second;
                }
                dp[i][diff] = len + 1;
                maxLen = max(maxLen, dp[i][diff]);
            }
        }
        return maxLen;
    }
};