/*
 * 757. Set Intersection Size At Least Two
 *
 * An integer interval [a, b] (for integers a < b) is a set of all consecutive integers from a to b, including a and b.
 * 
 * Find the minimum size of a set S such that for every integer interval A in intervals, the intersection of S with A has size at least 2.
 * 
 * Example 1:
 * 
 * Input: intervals = [[1, 3], [1, 4], [2, 5], [3, 5]]
 * Output: 3
 * Explanation:
 * Consider the set S = {2, 3, 4}.  For each interval, there are at least 2 elements from S in the interval.
 * Also, there isn't a smaller size set that fulfills the above condition.
 * Thus, we output the size of this set, which is 3.
 * 
 * Example 2:
 * 
 * Input: intervals = [[1, 2], [2, 3], [2, 4], [4, 5]]
 * Output: 5
 * Explanation:
 * An example of a minimum sized set is {1, 2, 3, 4, 5}.
 * 
 * Note:
 * 1. intervals will have length in range [1, 3000].
 * 2. intervals[i] will have length 2, representing some integer interval.
 * 3. intervals[i][j] will be an integer in [0, 10^8].
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int intersectionSizeTwo(vector<vector<int>>& intervals) {
        // Sort intervals by their right endpoint
        sort(intervals.begin(), intervals.end(),
             [](const vector<int>& a, const vector<int>& b) {
                 return a[1] < b[1];
             });

        // last1 and last2 store the two largest chosen points
        // Initialize with a value smaller than any possible interval start
        const int INF_NEG = -2e9;
        int last1 = INF_NEG, last2 = INF_NEG;
        int ans = 0;

        for (const auto& inv : intervals) {
            int l = inv[0], r = inv[1];

            if (last2 >= l) {
                // We already have two points inside this interval
                continue;
            } else if (last1 >= l) {
                // Exactly one point inside (last1)
                if (last1 != r) {
                    // Add the rightmost point r (new and distinct)
                    last2 = last1;
                    last1 = r;
                } else {
                    // last1 equals r, so we must add r-1 instead
                    last2 = r - 1;
                    // last1 remains r
                }
                ++ans;
            } else {
                // No point inside this interval → add two points: r-1 and r
                last2 = r - 1;
                last1 = r;
                ans += 2;
            }
        }

        return ans;
    }
};