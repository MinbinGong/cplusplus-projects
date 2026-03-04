/*
 * 1499. Max Value of Equation
 *
 * Given an array points containing the coordinates of points on a 2D plane, sorted by the x-values, where points[i] = [xi, yi] such that xi < xj for all 1 <= i < j <= points.length. You are also given an integer k.
 *
 * Find the maximum value of the equation yi + yj + |xi - xj| where |xi - xj| <= k and 1 <= i < j <= points.length. It is guaranteed that there exists at least one pair of points that satisfy the constraint |xi - xj| <= k.
 *
 * Example 1:
 * Input: points = [[1,3],[2,0],[5,10],[6,-10]], k = 1
 * Output: 4
 * Explanation: The pair (5,10) and (6,-10) has the maximum value of 10 + (-10) + |5 - 6| = 4.
 *
 * Example 2:
 * Input: points = [[0,0],[3,0],[9,2]], k = 3
 * Output: 3
 * Explanation: The pair (0,0) and (3,0) has the maximum value of 0 + 0 + |0 - 3| = 3.
 *
 * Constraints:
 * 2 <= points.length <= 10^5
 * points[i].length == 2
 * -10^8 <= points[i][0], points[i][1] <= 10^8
 * 0 <= k <= 2 * 10^8
 * points[i][0] < points[j][0] for all 1 <= i < j <= points.length
 * xi form a strictly increasing sequence.
 * 
 */
#include <vector>
#include <deque>
#include <climits>
using namespace std;

class Solution {
public:
    int findMaxValueOfEquation(vector<vector<int>>& points, int k) {
        deque<int> dq;                     // stores indices of points, in decreasing order of (y_i - x_i)
        int ans = INT_MIN;

        for (int j = 0; j < points.size(); ++j) {
            int xj = points[j][0];
            int yj = points[j][1];

            // remove points that are too far left (x_i < x_j - k)
            while (!dq.empty() && points[dq.front()][0] < xj - k) {
                dq.pop_front();
            }

            // the front of the deque gives the best (y_i - x_i) among valid i < j
            if (!dq.empty()) {
                int i = dq.front();
                int candidate = (points[i][1] - points[i][0]) + (yj + xj);
                if (candidate > ans) ans = candidate;
            }

            // insert current point j, maintaining decreasing order of (y_i - x_i)
            int curVal = yj - xj;
            while (!dq.empty() && (points[dq.back()][1] - points[dq.back()][0]) <= curVal) {
                dq.pop_back();
            }
            dq.push_back(j);
        }

        return ans;
    }
};