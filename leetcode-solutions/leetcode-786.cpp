/*
 * 786. K-th Smallest Prime Fraction
 *
 * A sorted list A contains 1, plus some number of primes. Then, for every p < q in the list, we consider the fraction p/q.
 * 
 * What is the K-th smallest fraction considered? Return your answer as an array of ints, where answer[0] = p and answer[1] = q.
 * 
 * Examples:
 * Input: A = [1, 2, 3, 5], K = 3
 * Output: [2, 5]
 * Explanation:
 * The fractions to be considered in sorted order are:
 * 1/5, 1/3, 2/5, 1/2, 3/5, 2/3.
 * The third fraction is 2/5.
 * 
 * Input: A = [1, 7], K = 1
 * Output: [1, 7]
 * 
 * Note:
 * 1. A will have length between 2 and 2000.
 * 2. Each A[i] will be between 1 and 30000.
 * 3. K will be between 1 and A.length * (A.length - 1) / 2.
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<int> kthSmallestPrimeFraction(vector<int>& arr, int k) {
        int n = arr.size();
        double left = 0.0, right = 1.0;
        vector<int> ans(2, 0);

        // Binary search for the k-th smallest fraction
        for (int iter = 0; iter < 50; ++iter) {  // 50 iterations are enough for high precision
            double mid = (left + right) / 2.0;
            int cnt = 0;
            int best_num = 0, best_den = 1;  // to track the largest fraction <= mid

            for (int j = 1; j < n; ++j) {
                // Find the largest i < j such that arr[i] <= mid * arr[j]
                double target = mid * arr[j];
                int i = upper_bound(arr.begin(), arr.begin() + j, target) - arr.begin();
                cnt += i;  // all indices 0..i-1 satisfy the condition

                if (i > 0) {
                    int num = arr[i - 1];
                    int den = arr[j];
                    // compare num/den > best_num/best_den using cross multiplication
                    if ((long long)num * best_den > (long long)best_num * den) {
                        best_num = num;
                        best_den = den;
                    }
                }
            }

            if (cnt < k) {
                left = mid;           // need a larger value
            } else {
                right = mid;           // candidate value is sufficient
                ans[0] = best_num;
                ans[1] = best_den;
            }
        }
        return ans;
    }
};