/*
 * 1186. Maximum Subarray Sum with One Deletion
 * 
 * Given an array of integers, return the maximum sum for a non-empty subarray (contiguous elements) with at most one element deletion. In other words, you want to choose a subarray and optionally delete one element from it so that there is still at least one element left and the sum of the remaining elements is maximum possible.
 * 
 * Note that the subarray needs to be non-empty after deleting one element.
 * 
 * Example 1:
 * 
 * Input: arr = [1,-2,0,3]
 * Output: 4
 * Explanation: Because we can choose [1, -2, 0, 3] and drop -2, thus the subarray [1, 0, 3] becomes the maximum value.
 * Example 2:
 * 
 * Input: arr = [1,-2,-2,3]
 * Output: 3
 * Explanation: We just choose [3] and it's the maximum sum.
 * Example 3:
 * 
 * Input: arr = [-1,-1,-1,-1]
 * Output: -1
 * Explanation: The final subarray needs to be non-empty. You can't choose [-1] and delete -1 from it, then get an empty subarray to make the sum equals to 0.
 * 
 * Constraints:
 * 
 * 1 <= arr.length <= 10^5
 * -10^4 <= arr[i] <= 10^4
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    int maximumSum(vector<int>& arr) {
        int n = arr.size();
        // dp0: maximum sum of a subarray ending at current index with no deletion
        // dp1: maximum sum of a subarray ending at current index with at most one deletion
        int dp0 = arr[0];
        int dp1 = arr[0];
        int ans = arr[0];

        for (int i = 1; i < n; ++i) {
            // Extend without deletion or start new subarray
            int new_dp0 = max(arr[i], dp0 + arr[i]);
            // Two possibilities for one deletion:
            // 1. Extend previous subarray that already used a deletion
            // 2. Delete current element, taking the best subarray ending at i-1 without deletion
            int new_dp1 = max(dp1 + arr[i], dp0);

            ans = max(ans, max(new_dp0, new_dp1));
            dp0 = new_dp0;
            dp1 = new_dp1;
        }
        return ans;
    }
};