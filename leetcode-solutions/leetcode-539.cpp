/*
 * 539. Minimum Time Difference
 * 
 * Given a list of 24-hour clock time points in "HH:MM" format, return the minimum minutes difference between any two time-points in the list.
 * 
 * Example 1:
 * Input: timePoints = ["23:59","00:00"]
 * Output: 1
 * 
 * Example 2:
 * Input: timePoints = ["00:00","23:59","00:00"]
 * Output: 0
 * 
 * Constraints:
 * 1. 2 <= timePoints.length <= 2 * 104
 * 2. timePoints[i] is in the format "HH:MM".
 * 3. All the values in the tree are unique.
 * 4. root is guaranteed to be a valid binary search tree.
 * 
 */
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Solution {
public:
    int findMinDifference(vector<string>& timePoints) {
        vector<int> minutes;
        // Convert each time to minutes since 00:00
        for (const string& t : timePoints) {
            int h = stoi(t.substr(0, 2));
            int m = stoi(t.substr(3, 2));
            minutes.push_back(h * 60 + m);
        }
        // Sort the times
        sort(minutes.begin(), minutes.end());
        
        int minDiff = 1440; // maximum possible difference (24*60)
        int n = minutes.size();
        // Compare consecutive times
        for (int i = 1; i < n; ++i) {
            minDiff = min(minDiff, minutes[i] - minutes[i - 1]);
        }
        // Circular difference between last and first (wrap around midnight)
        minDiff = min(minDiff, minutes[0] + 1440 - minutes[n - 1]);
        
        return minDiff;
    }
};