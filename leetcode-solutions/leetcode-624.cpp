/*
 * Maximum Distance in Arrays
 *
 * You are given m arrays, where each array is sorted in ascending order.
 * 
 * You can pick up two integers from two different arrays (each array picks one) and calculate the distance. We define
 * the distance between two integers a and b to be their absolute difference |a - b|.
 * 
 * Return the maximum distance.
 * 
 * Example 1:
 * Input: arrays = [[1,2,3],[4,5],[1,2,3]]
 * Output: 4
 * Explanation: One way to reach the maximum distance 4 is to pick 1 in the first or third array and pick 5 in the
 * second array.
 * 
 * Example 2:
 * Input: arrays = [[1],[1]]
 * Output: 0
 * 
 * Example 3:
 * Input: arrays = [[1],[2]]
 * Output: 1
 * 
 * Example 4:
 * Input: arrays = [[1,4],[0,5]]
 * Output: 4
 * 
 * Constraints:
 * m == arrays.length
 * 2 <= m <= 105
 * 1 <= arrays[i].length <= 500
 * -104 <= arrays[i][j] <= 104
 * arrays[i] is sorted in ascending order.
 * There will be at most 105 integers in all the arrays.
 *  
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxDistance(vector<vector<int>>& arrays) {
        // Initialize with the first array's min and max
        int globalMin = arrays[0][0];
        int globalMax = arrays[0].back();
        int result = 0;
        
        for (int i = 1; i < arrays.size(); ++i) {
            int curMin = arrays[i][0];
            int curMax = arrays[i].back();
            
            // Compute distances with previous global extremes
            result = max(result, abs(curMax - globalMin));
            result = max(result, abs(globalMax - curMin));
            
            // Update global extremes
            globalMin = min(globalMin, curMin);
            globalMax = max(globalMax, curMax);
        }
        
        return result;
    }
};