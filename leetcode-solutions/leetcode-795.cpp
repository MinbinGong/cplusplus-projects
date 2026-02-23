/*
 * 795. Number of Subarrays with Bounded Maximum
 *
 * We are given an array A of positive integers, and two positive integers L and R (L <= R).
 * 
 * Return the number of (contiguous, non-empty) subarrays such that the value of the maximum array element in that subarray is at least L and at most R.
 * 
 * Example :
 * Input: 
 * A = [2, 1, 4, 3]
 * L = 2
 * R = 3
 * Output: 3
 * Explanation: There are three subarrays that meet the requirements: [2], [2, 1], [3].
 * 
 * Note:
 * 1. L, R  will be integers in the range [0, 10^9].
 * 2. A.length will be in the range of [1, 50000].
 * 3. A[i] will be integers in the range of [0, 10^9].
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    int numSubarrayBoundedMax(vector<int>& A, int L, int R) {
        // subarrays with max ≤ R minus subarrays with max ≤ L-1
        return count(A, R) - count(A, L - 1);
    }

private:
    // count subarrays where all elements ≤ bound
    int count(vector<int>& A, int bound) {
        int ans = 0;
        int cur = 0;  // length of current valid segment ending at i
        for (int x : A) {
            if (x <= bound) {
                cur++;
                ans += cur;   // subarrays ending at i
            } else {
                cur = 0;      // reset at element > bound
            }
        }
        return ans;
    }
};