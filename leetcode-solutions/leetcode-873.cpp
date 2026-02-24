/**
 * 873. Length of Longest Fibonacci Subsequence
 * 
 * Example 1:
 * Input: [1,2,3,4,5,6,7,8]
 * Output: 5
 * Explanation:
 * The longest subsequence that is fibonacci-like: [1,2,3,5,8].
 * 
 * Example 2:
 * Input: [1,3,7,11,12,14,18]
 * Output: 3
 * Explanation:
 * The longest subsequence that is fibonacci-like:
 * [1,11,12], [3,11,14] or [7,11,18].
 * 
 * Note:
 * 3 <= A.length <= 1000
 * 1 <= A[0] < A[1] < ... < A[A.length - 1] <= 10^9
 * (The time limit has been reduced by 50% for submissions in Java, C, and C++.)
 * 
 */
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int lenLongestFibSubseq(vector<int>& arr) {
        int n = arr.size();
        // map value to its index for O(1) lookup
        unordered_map<int, int> index;
        for (int i = 0; i < n; ++i) {
            index[arr[i]] = i;
        }
        // dp[i][j] = length of Fibonacci-like sequence ending with arr[i], arr[j]
        vector<vector<int>> dp(n, vector<int>(n, 2)); // minimum length 2 for any pair
        int maxLen = 0;

        for (int j = 0; j < n; ++j) {
            for (int i = 0; i < j; ++i) {
                int target = arr[i] + arr[j];
                // check if target exists after j
                auto it = index.find(target);
                if (it != index.end() && it->second > j) {
                    int k = it->second;
                    dp[j][k] = dp[i][j] + 1;
                    maxLen = max(maxLen, dp[j][k]);
                }
            }
        }
        return maxLen >= 3 ? maxLen : 0;
    }
};