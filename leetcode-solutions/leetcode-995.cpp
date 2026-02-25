/**
 * 995. Minimum Number of K Consecutive Bit Flips
 *
 * In an array A containing only 0s and 1s, a K-bit flip consists of choosing a (contiguous) subarray of length K and simultaneously changing every 0 in the subarray to 1, and every 1 in the subarray to 0.
 *
 * Return the minimum number of K-bit flips required so that there is no 0 in the array.  If it is not possible, return -1.
 *
 * Example 1:
 *
 * Input: A = [0,1,0], K = 1
 * Output: 2
 * Explanation: Flip A[0], then flip A[2].
 *
 * Example 2:
 *
 * Input: A = [1,1,0], K = 2
 * Output: -1
 * Explanation: No matter how we flip subarrays of size 2, we can't make the array become [1,1,1].
 *
 * Example 3:
 *
 * Input: A = [0,0,0,1,0,1,1,0], K = 3
 * Output: 3
 * Explanation:
 * Flip A[0],A[1],A[2]: A becomes [1,1,1,1,0,1,1,0]
 * Flip A[4],A[5],A[6]: A becomes [1,1,1,1,1,0,0,0]
 * Flip A[5],A[6],A[7]: A becomes [1,1,1,1,1,1,1,1]
 *
 * Note:
 *
 * 1 <= A.length <= 30000
 * 1 <= K <= A.length
 */
#include <vector>
using namespace std;

class Solution {
public:
    int minKBitFlips(vector<int>& A, int K) {
        int n = A.size();
        int flips = 0;
        int flipEffect = 0;               // current cumulative flip status (0 or 1)
        vector<int> isFlipped(n, 0);       // marks where a flip started

        for (int i = 0; i < n; ++i) {
            if (i >= K) {
                if (isFlipped[i - K]) {    // a flip that started K steps ago ends here
                    flipEffect ^= 1;
                }
            }
            // actual value after previous flips
            int current = A[i] ^ flipEffect;
            if (current == 0) {             // need to flip at i
                if (i + K > n) return -1;   // cannot flip because it would go out of bounds
                flips++;
                flipEffect ^= 1;             // start a new flip
                isFlipped[i] = 1;             // record that we flipped starting at i
            }
        }
        return flips;
    }
};