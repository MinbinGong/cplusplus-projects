/**
 * 1272. Remove Interval
 * 
 * Given a sorted list of disjoint intervals, each interval intervals[i] = [a, b] represents the set of real numbers x such that a <= x < b.
 * 
 * We remove the intersections between any interval in intervals and the interval toBeRemoved.
 * 
 * Return a sorted list of intervals after all such removals.
 * 
 * Example 1:
 * Input: intervals = [[0,2],[3,4],[5,7]], toBeRemoved = [1,6]
 * Output: [[0,1],[6,7]]
 * 
 * Example 2:
 * Input: intervals = [[0,5]], toBeRemoved = [2,3]
 * Output: [[0,2],[3,5]]
 * 
 * Note:
 * 1 <= intervals.length <= 10^4
 * -10^9 <= intervals[i][0] < intervals[i][1] <= 10^9
 * 
 */
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> removeInterval(vector<vector<int>>& intervals, vector<int>& toBeRemoved) {
        vector<vector<int>> result;
        int removeStart = toBeRemoved[0];
        int removeEnd = toBeRemoved[1];
        
        for (const auto& interval : intervals) {
            int start = interval[0];
            int end = interval[1];
            
            // Case 1: No overlap - interval completely outside removal range
            if (end <= removeStart || start >= removeEnd) {
                result.push_back(interval);
            }
            // Case 2: Overlap exists - need to handle partial removal
            else {
                // Left part: [start, removeStart) if there's a non-empty left segment
                if (start < removeStart) {
                    result.push_back({start, removeStart});
                }
                // Right part: [removeEnd, end) if there's a non-empty right segment
                if (end > removeEnd) {
                    result.push_back({removeEnd, end});
                }
            }
        }
        
        return result;
    }
};