/*
 * 1497. Check If Array Pairs Are Divisible by k
 *
 * Given an array of integers arr of even length n and an integer k.
 *
 * We want to divide the array into exactly n / 2 pairs such that the sum of each pair is divisible by k.
 *
 * Return true If you can find a way to do that or false otherwise.
 *
 * Example 1:
 * Input: arr = [1,2,3,4,5,10,6,7,8,9], k = 5
 * Output: true
 * Explanation: Pairs are (1,9),(2,8),(3,7),(4,6) and (5,10).
 *
 * Example 2:
 * Input: arr = [1,2,3,4,5,6], k = 7
 * Output: true
 * Explanation: Pairs are (1,6),(2,5) and(3,4).
 *
 * Example 3:
 * Input: arr = [1,2,3,4,5,6], k = 10
 * Output: false
 * Explanation: You can try all possible pairs to see that there is no way to divide arr into 3 pairs each with sum divisible by 10.
 *
 * constraints:
 * arr.length == n
 * 1 <= n <= 10^5
 * n is even.
 * -10^9 <= arr[i] <= 10^9
 * 1 <= k <= 10^5
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    bool canArrange(vector<int>& arr, int k) {
        // freq[r] = count of numbers with remainder r (0 <= r < k)
        vector<int> freq(k, 0);

        for (int num : arr) {
            // Compute non-negative remainder
            int rem = num % k;
            if (rem < 0) rem += k;   // handle negative numbers
            freq[rem]++;
        }

        // Numbers with remainder 0 must pair among themselves → even count
        if (freq[0] % 2 != 0) return false;

        // For remainders i and k-i (i from 1 to k/2) the counts must match
        for (int i = 1; i <= k / 2; i++) {
            if (i == k - i) {
                // Special case when k is even and i = k/2
                // These numbers pair with themselves → even count
                if (freq[i] % 2 != 0) return false;
            } else {
                // Normal pairing: remainder i with remainder k-i
                if (freq[i] != freq[k - i]) return false;
            }
        }

        return true;
    }
};