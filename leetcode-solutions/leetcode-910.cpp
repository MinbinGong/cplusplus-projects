/*
 * Smallest Range II
 *
 * Given an array A of integers, for each integer A[i] we may choose any x with -K <= x <= K, and add x to A[i].
 * 
 * After this process, we have some array B.
 * 
 * Return the smallest possible difference between the maximum value of B and the minimum value of B.
 * 
 * Example 1:
 * Input: A = [1], K = 0
 * Output: 0
 * Explanation: B = [1]
 * 
 * Example 2:
 * Input: A = [0,10], K = 2
 * Output: 6
 * Explanation: B = [2,8]
 * 
 * Example 3:
 * Input: A = [1,3,6], K = 3
 * Output: 0
 * Explanation: B = [3,3,3] or B = [4,4,4]
 * 
 * Note:
 * 1 <= A.length <= 10000
 * 0 <= A[i] <= 10000
 * 0 <= K <= 10000
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int smallestRangeII(vector<int>& A, int K) {
        sort(A.begin(), A.end());
        int n = A.size();
        int ans = A[n-1] - A[0]; // initial range (all +K or all -K)
        for (int i = 0; i < n - 1; ++i) {
            int left_max = A[i] + K;
            int right_max = A[n-1] - K;
            int left_min = A[0] + K;
            int right_min = A[i+1] - K;
            int cur_max = max(left_max, right_max);
            int cur_min = min(left_min, right_min);
            ans = min(ans, cur_max - cur_min);
        }
        return ans;
    }
};