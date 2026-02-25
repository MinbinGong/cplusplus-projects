/**
 * 986. Interval List Intersections
 *
 * Given two lists of closed intervals, each list of intervals is pairwise disjoint and in sorted order.
 *
 * Return the intersection of these two interval lists.
 *
 * (Formally, a closed interval [a, b] (with a <= b) denotes the set of real numbers x with a <= x <= b.  The intersection of two closed intervals is a set of real numbers that is either empty, or can be represented as a closed interval.  For example, the intersection of [1, 3] and [2, 4] is [2, 3].)
 *
 * Example 1:
 *
 * Input: A = [[0,2],[5,10],[13,23],[24,25]], B = [[1,5],[8,12],[15,24],[25,26]]
 * Output: [[1,2],[5,5],[8,10],[15,23],[24,24],[25,25]]
 * Explanation: The figure above shows the given intervals: red and blue.
 * The intersection of the intervals is the blue interval.
 * 
 * Example 2:
 *
 * Input: A = [[1,3],[5,9]], B = []
 * Output: []
 * 
 * Note:
 *
 * 0 <= A.length < 1000
 * 0 <= B.length < 1000
 * 0 <= A[i].start, A[i].end, B[i].start, B[i].end < 10^9
 * 
 */
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> intervalIntersection(vector<vector<int>>& A, vector<vector<int>>& B) {
        vector<vector<int>> result;
        int i = 0, j = 0;
        while (i < A.size() && j < B.size()) {
            // potential intersection start and end
            int start = max(A[i][0], B[j][0]);
            int end = min(A[i][1], B[j][1]);
            if (start <= end) {
                result.push_back({start, end});
            }
            // advance the interval that ends first
            if (A[i][1] < B[j][1]) {
                ++i;
            } else {
                ++j;
            }
        }
        return result;
    }
};