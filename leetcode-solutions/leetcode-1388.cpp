/**
 * 1388. Pizza With 3n Slices
 * 
 * There is a pizza with 3n slices of varying size, you and your friends will take slices of pizza as follows:
 * 
 * You will pick any pizza slice.
 * Your friend Alice will pick next slice in anti-clockwise direction of your pick.
 * Your friend Bob will pick next slice in clockwise direction of your pick.
 * Repeat until there are no more slices of pizzas.
 * Given an integer array slices that represent the sizes of the pizza slices in a clockwise direction, return the maximum possible sum of slice sizes that you can pick.
 * 
 * Example 1:
 * Input: slices = [1,2,3,4,5,6]
 * Output: 10
 * Explanation: Pick pizza slice of size 4, Alice and Bob will pick slices with size 3 and 5 respectively. Then Pick slices with size 6, finally Alice and Bob will pick slice of size 2 and 1 respectively. Total = 4 + 6 = 10.
 * 
 * Example 2:
 * Input: slices = [8,9,8,6,1,1]
 * Output: 16
 * Explanation: Pick pizza slice of size 8 in each turn. If you pick slice with size 9 your partners will pick slices of size 8.
 * 
 * Example 3:
 * Input: slices = [4,1,2,5,8,3,1,9,7]
 * Output: 21
 * 
 * Example 4:
 * Input: slices = [3,1,2]
 * Output: 3
 * 
 * Note:
 * 1 <= slices.length <= 500
 * slices.length % 3 == 0
 * 1 <= slices[i] <= 1000
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    int maxSizeSlices(vector<int>& slices) {
        int m = slices.size();
        int n = m / 3;                     // number of slices we can take

        // Two linear arrays to break the circular constraint:
        // 1) exclude the last slice
        vector<int> case1(slices.begin(), slices.end() - 1);
        // 2) exclude the first slice
        vector<int> case2(slices.begin() + 1, slices.end());

        return max(linearMax(case1, n), linearMax(case2, n));
    }

private:
    int linearMax(const vector<int>& arr, int k) {
        int sz = arr.size();
        const int NEG = -1e9;               // represents impossible state
        // dp[i][j] = maximum sum using first i elements, picking exactly j slices
        vector<vector<int>> dp(sz + 1, vector<int>(k + 1, NEG));
        dp[0][0] = 0;

        for (int i = 1; i <= sz; ++i) {
            for (int j = 0; j <= k; ++j) {
                // Option 1: do not pick current slice
                dp[i][j] = dp[i - 1][j];

                // Option 2: pick current slice (if possible)
                if (j >= 1) {
                    if (i == 1) {
                        // only one element – can pick it only when j == 1
                        if (j == 1)
                            dp[i][j] = max(dp[i][j], arr[i - 1]);
                    } else {
                        // need to skip the previous element
                        dp[i][j] = max(dp[i][j], dp[i - 2][j - 1] + arr[i - 1]);
                    }
                }
            }
        }
        return dp[sz][k];
    }
};