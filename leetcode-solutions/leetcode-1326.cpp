/*
 * 1326. Minimum Number of Taps to Open to Water a Garden
 *
 * There is a one-dimensional garden on the x-axis. The garden starts at the point 0 and ends at the point n. (i.e The length of the garden is n).
 * 
 * There are n + 1 taps located at points [0, 1, ..., n] in the garden.
 * 
 * Given an integer n and an integer array ranges of length n + 1 where ranges[i] (0-indexed) means the i-th tap can water the area [i - ranges[i], i + ranges[i]] if it was open.
 * 
 * Return the minimum number of taps that should be open to water the whole garden, If the garden cannot be watered return -1.
 * 
 * Example 1:
 * Input: n = 5, ranges = [3,4,1,1,0,0]
 * Output: 1
 * Explanation: The tap at point 0 can cover the interval [-3,3]
 * The tap at point 1 can cover the interval [-3,5]
 * The tap at point 2 can cover the interval [1,3]
 * The tap at point 3 can cover the interval [2,4]
 * The tap at point 4 can cover the interval [4,4]
 * The tap at point 5 can cover the interval [5,5]
 * Opening Only the second tap will water the whole garden [0,5]
 * 
 * Example 2:
 * Input: n = 3, ranges = [0,0,0,0]
 * Output: -1
 * Explanation: Even if you activate all the four taps you cannot water the whole garden.
 * 
 * Note:
 * 1 <= n <= 10^4
 * ranges.length == n + 1
 * 0 <= ranges[i] <= 100
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    int minTaps(int n, vector<int>& ranges) {
        // Create an array that for each leftmost position stores
        // the furthest right point reachable by any tap starting there.
        vector<int> maxReach(n + 1, 0);
        for (int i = 0; i <= n; ++i) {
            int left = max(0, i - ranges[i]);
            int right = min(n, i + ranges[i]);
            maxReach[left] = max(maxReach[left], right);
        }

        int curEnd = 0;      // current covered rightmost position
        int nextEnd = 0;     // furthest position we can reach from the current segment
        int steps = 0;

        for (int i = 0; i <= n; ++i) {
            // When we move past the current coverage, we must take a new tap
            if (i > curEnd) {
                // If we cannot extend coverage any further, it's impossible
                if (nextEnd <= curEnd) return -1;
                curEnd = nextEnd;
                ++steps;
            }
            // Update the furthest point we can reach from all taps seen so far
            nextEnd = max(nextEnd, maxReach[i]);
        }

        // At the end, if curEnd < n it means we never managed to cover the garden,
        // but the loop logic would have already returned -1 in that case.
        // So steps is the answer.
        return steps;
    }
};