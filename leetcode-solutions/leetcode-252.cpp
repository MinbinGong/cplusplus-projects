/*
 * Meeting Rooms
 * 
 * Given an array of meeting time intervals where intervals[i] = [starti, endi], determine if a person could attend all meetings.
 * 
 * Constraints:
 * 1. 0 <= intervals.length <= 104
 * 2. intervals[i].length == 2
 * 3. 0 <= starti < endi <= 106
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    bool canAttendMeetings(vector<vector<int>>& intervals) {
        if (intervals.empty()) return true;
        
        // Sort by start time
        sort(intervals.begin(), intervals.end());
        
        for (int i = 0; i < intervals.size() - 1; ++i) {
            // If current meeting ends after next meeting starts → overlap
            if (intervals[i][1] > intervals[i+1][0]) {
                return false;
            }
        }
        return true;
    }
};