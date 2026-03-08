/*
 * 1642. Furthest Building You Can Reach
 *
 * You are given an integer array heights representing the heights of buildings, some bricks, and some ladders.
 * You start your journey from building 0 and move to the next building by possibly using bricks or ladders.
 * While moving from building i to building i+1 (0-indexed),
 * If the current building's height is greater than or equal to the next building's height, you do not need a ladder or bricks.
 * If the current building's height is less than the next building's height, you can either use one ladder or (h[i+1] - h[i]) bricks.
 * Return the furthest building index (0-indexed) you can reach if you use the given ladders and bricks optimally.
 * 
 * Example 1:
 * Input: heights = [4,2,7,6,9,14,12], bricks = 5, ladders = 1
 * Output: 4
 * Explanation: Starting at building 0, you can follow these steps:
 * 
 * Example 2:
 * Input: heights = [4,12,2,7,3,18,20,3,19], bricks = 10, ladders = 2
 * Output: 7
 * Explanation: Starting at building 0, you can follow these steps:
 * 
 * Constraints:
 * 1 <= heights.length <= 10^5
 * 1 <= heights[i] <= 10^6
 * 0 <= bricks <= 10^9
 * 0 <= ladders <= heights.length
 * 
 */
#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    int furthestBuilding(vector<int>& heights, int bricks, int ladders) {
        // Min-heap to store the climbs where we used ladders
        priority_queue<int, vector<int>, greater<int>> minHeap;
        int n = heights.size();
        
        for (int i = 0; i < n - 1; ++i) {
            int diff = heights[i + 1] - heights[i];
            if (diff > 0) { // only need to climb up
                minHeap.push(diff);
                
                // If we've used more ladders than available,
                // replace the smallest ladder climb with bricks
                if (minHeap.size() > ladders) {
                    bricks -= minHeap.top();
                    minHeap.pop();
                }
                
                // If bricks become negative, we can't reach the next building
                if (bricks < 0) {
                    return i;
                }
            }
        }
        return n - 1; // reached the last building
    }
};