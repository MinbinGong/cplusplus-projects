/*
 * Smallest Good Base
 *
 * For an integer n, we call k>=2 a good base of n, if all digits of n base k are 1.
 *
 * Now given a string representing n, you should return the smallest good base of n in string format.
 *
 * Constraints:
 * The string representing n is always valid and will not have leading zeros.
 * 1 <= n <= 1018
 * 
 */
#include <string>
#include <cmath>
#include <algorithm>
using namespace std;

class Solution {
public:
    string smallestGoodBase(string n) {
        long long N = stoll(n);
        // maximum possible m: 2^(m-1) <= N  => m <= log2(N) + 1
        int max_m = log2(N) + 1;
        for (int m = max_m; m >= 2; --m) {
            // binary search for base b in [2, N^(1/(m-1)) + 1]
            long long low = 2;
            long long high = pow(N, 1.0 / (m - 1)) + 1;
            while (low <= high) {
                long long mid = low + (high - low) / 2;
                __int128 sum = 0, cur = 1;
                bool tooBig = false;
                // compute geometric series: 1 + b + b^2 + ... + b^(m-1)
                for (int i = 0; i < m; ++i) {
                    sum += cur;
                    if (sum > N) {        // already exceeds N, no need to continue
                        tooBig = true;
                        break;
                    }
                    if (i < m - 1) {
                        // avoid overflow: if cur * mid would exceed N, set cur large
                        if (cur > (__int128)N / mid) {
                            cur = N + 1;   // ensures next sum > N
                        } else {
                            cur *= mid;
                        }
                    }
                }
                if (tooBig) {
                    high = mid - 1;
                } else if (sum == N) {
                    return to_string(mid);
                } else { // sum < N
                    low = mid + 1;
                }
            }
        }
        // If no base found, then base = N-1 (m=2 case)
        return to_string(N - 1);
    }
};