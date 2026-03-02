/**
 * 1343. Number of Sub-arrays of Size K and Average Greater than or Equal to Threshold
 * 
 * Given an array of integers arr and two integers k and threshold, return the number of sub-arrays of size k and average greater than or equal to threshold.
 * 
 * Example 1:
 * Input: arr = [2,2,2,2,5,5,5,8], k = 3, threshold = 4
 * Output: 3
 * Explanation: Sub-arrays [2,5,5],[5,5,5] and [5,5,8] have averages 4, 5 and 6 respectively. All other sub-arrays of size 3 have averages less than 4 (the threshold).
 * 
 * Example 2:
 * Input: arr = [11,13,17,23,29,31,7,5,2,3], k = 3, threshold = 5
 * Output: 6
 * Explanation: Sub-arrays [11,13,17],[13,17,23],[17,23,29],[23,29,31],[29,31,7] and [31,7,5] have averages 11, 12.5, 14, 18, 15.5 and 16 respectively.
 * 
 * Example 3:
 * Input: arr = [4,4,4,4], k = 4, threshold = 1
 * Output: 1
 * Explanation: Sub-arrays [4,4,4,4] have average 4 which is greater than or equal to threshold = 1.
 * 
 * Note:
 * 1 <= arr.length <= 10^5
 * 1 <= arr[i] <= 10^4
 * 1 <= k <= arr.length
 * 0 <= threshold <= 10^4
 * 
 */
#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    int numOfSubarrays(vector<int>& arr, int k, int threshold) {
        int n = arr.size();
        int sum = 0;
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            sum += arr[i];
            if (i >= k) {
                sum -= arr[i - k];
            }
            if (i >= k - 1) {
                if (sum >= k * threshold) {
                    ans++;
                }
            }
        }
        return ans;
    }
};
