/*
 * 3Sum With Multiplicity
 *
 * Given an integer array A, and an integer target, return the number of tuples i, j, k  such that i < j < k and A[i] + A[j] + A[k] == target.
 *
 * As the answer can be very large, return it modulo 10^9 + 7.
 *
 * Example 1:
 * Input: A = [1,1,2,2,3,3,4,4,5,5], target = 8
 * Output: 20
 * Explanation:
 * Enumerating by the values (A[i], A[j], A[k]):
 * (1, 2, 5) occurs 8 times;
 * (1, 3, 4) occurs 8 times;
 * (2, 2, 4) occurs 2 times;
 * (2, 3, 3) occurs 2 times.
 *
 * Example 2:
 * Input: A = [1,1,2,2,2,2], target = 5
 * Output: 12
 * Explanation:
 * A[i] = 1, A[j] = A[k] = 2 occurs 12 times:
 * We choose one 1 from [1,1] in 2 ways,
 * and two 2s from [2,2,2,2] in 6 ways.
 *
 * Note:
 * 3 <= A.length <= 3000
 * 0 <= A[i] <= 100
 * 0 <= target <= 300
 *
 */
#include <vector>
using namespace std;

class Solution {
public:
    int threeSumMulti(vector<int>& arr, int target) {
        const int MOD = 1e9 + 7;
        long long freq[101] = {0};
        for (int x : arr) {
            freq[x]++;
        }

        long long ans = 0;
        for (int a = 0; a <= 100; ++a) {
            for (int b = a; b <= 100; ++b) {
                int c = target - a - b;
                if (c < 0 || c > 100) continue;          // c out of range
                if (c < b) continue;                      // avoid counting same triplet multiple times

                if (a == b && b == c) {
                    // all three equal
                    long long n = freq[a];
                    ans += n * (n - 1) * (n - 2) / 6;
                } else if (a == b) {
                    // a == b != c
                    long long n = freq[a];
                    ans += (n * (n - 1) / 2) * freq[c];
                } else if (b == c) {
                    // a != b == c
                    long long n = freq[b];
                    ans += freq[a] * (n * (n - 1) / 2);
                } else {
                    // all distinct
                    ans += freq[a] * freq[b] * freq[c];
                }
                ans %= MOD;
            }
        }
        return ans;
    }
};