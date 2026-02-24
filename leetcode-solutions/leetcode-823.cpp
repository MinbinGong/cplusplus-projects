/**
 * 823. Binary Trees With Factors
 *
 * Given an array of unique integers, arr, where each integer arr[i] is strictly greater than 1.
 *
 * We make a binary tree using these integers, and each number may be used for any number of times. Each non-leaf node's value should be equal to the product of the values of its children.
 *
 * Return the number of binary trees we can make. The answer may be too large so return the answer modulo 109 + 7.
 *
 * Example:
 * Input: arr = [2,4]
 * Output: 3
 * Explanation: We can make these trees: [2], [4], [4, 2, 2]
 *
 * Note:
 * 1 <= arr.length <= 1000
 * 2 <= arr[i] <= 109
 * All the values of arr are unique.
 */
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
public:
    int numFactoredBinaryTrees(vector<int>& arr) {
        const int MOD = 1e9 + 7;
        sort(arr.begin(), arr.end());
        int n = arr.size();
        unordered_map<int, int> index;
        for (int i = 0; i < n; ++i) {
            index[arr[i]] = i;
        }
        vector<long long> dp(n, 1); // each element as a single-node tree

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                if (arr[i] % arr[j] == 0) {
                    int right = arr[i] / arr[j];
                    auto it = index.find(right);
                    if (it != index.end()) {
                        dp[i] = (dp[i] + dp[j] * dp[it->second]) % MOD;
                    }
                }
            }
        }

        long long ans = 0;
        for (long long x : dp) ans = (ans + x) % MOD;
        return ans;
    }
};