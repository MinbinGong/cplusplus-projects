/*
 * 1005. Maximize Sum Of Array After K Negations
 *
 * Given an array A of integers, we must modify the array in the following way: we choose an i and replace A[i] with -A[i], and we repeat this process K times in total.  (We may choose the same index i multiple times.)
 *
 * Return the largest possible sum of the array after modifying it in this way.
 *
 * Example 1:
 *
 * Input: A = [4,2,3], K = 1
 * Output: 5
 * Explanation: Choose indices (1,) and A becomes [4,-2,3].
 * 
 * Example 2:
 *
 * Input: A = [3,-1,0,2], K = 3
 * Output: 6
 * Explanation: Choose indices (1, 2, 2) and A becomes [3,1,0,2].
 * 
 * Example 3:
 *
 * Input: A = [2,-3,-1,5,-4], K = 2
 * Output: 13
 * Explanation: Choose indices (1, 4) and A becomes [2,3,-1,5,4].
 * 
 * Note:
 *
 * 1 <= A.length <= 10000
 * 1 <= K <= 10000
 * -100 <= A[i] <= 100
 * 
 */
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

class Solution {
public:
    int largestSumAfterKNegations(vector<int>& A, int K) {
        // Step 1: Sort the array so that we can flip the smallest (most negative) first
        sort(A.begin(), A.end());

        // Step 2: Flip as many negative numbers as possible
        for (int i = 0; i < A.size() && K > 0 && A[i] < 0; ++i) {
            A[i] = -A[i];
            --K;
        }

        // Step 3: If K is odd, we need to flip the smallest element one more time
        if (K % 2 == 1) {
            // Find the element with smallest absolute value
            auto minIt = min_element(A.begin(), A.end(), [](int a, int b) {
                return abs(a) < abs(b);
            });
            *minIt = -*minIt;
        }

        // Step 4: Return the sum
        return accumulate(A.begin(), A.end(), 0);
    }
};