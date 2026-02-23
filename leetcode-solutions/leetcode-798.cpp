/*
 * 798. Smallest Rotation with Highest Score
 *
 * Given an array A, we may rotate it by a non-negative integer K so that the array becomes A[K], A[K+1], A{K+2], ... A[A.length - 1], A[0], A[1], ..., A[K-1].  Afterward, any entries that are less than or equal to their index are worth 1 point.
 * 
 * Note:
 * 1. 0 <= K <= A.length <= 20000
 * 2. 0 <= A[i] <= 10000
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    int bestRotation(vector<int>& A) {
        int n = A.size();
        vector<int> diff(n + 1, 0); // difference array for "bad" rotations
        
        for (int i = 0; i < n; ++i) {
            int v = A[i];
            if (v == 0) continue; // always contributes, no bad rotation
            
            // bad rotations are those where the element ends at an index < v
            // they form a cyclic interval [start, i] (inclusive) of length v
            int start = (i - (v - 1) + n) % n;
            int end = i;
            
            if (start <= end) {
                // interval does not wrap
                diff[start] += 1;
                diff[end + 1] -= 1;
            } else {
                // interval wraps around the end of the array
                diff[start] += 1;
                diff[n] -= 1;
                diff[0] += 1;
                diff[end + 1] -= 1;
            }
        }
        
        // prefix sum to get number of bad rotations for each k
        int cur = 0;
        int bestScore = -1;
        int bestK = 0;
        for (int k = 0; k < n; ++k) {
            cur += diff[k];
            int good = n - cur; // number of elements that contribute
            if (good > bestScore) {
                bestScore = good;
                bestK = k;
            }
        }
        return bestK;
    }
};