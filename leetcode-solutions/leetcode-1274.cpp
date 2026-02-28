/**
 * 1274. Number of Ships in a Rectangle
 * 
 * (This problem is an interactive problem.)
 * 
 * On the sea represented by a cartesian plane, each ship is located at an integer point, and each integer point may contain at most 1 ship.
 * 
 * You have a function Sea.hasShips(topRight, bottomLeft) which takes two points as arguments and returns true if and only if there is at least one ship in the rectangle represented by the two points, including on the boundary.
 * 
 * Given two points: the top right and bottom left corners of a rectangle, return the number of ships present in that rectangle.  It is guaranteed that there are at most 10 ships in that rectangle.
 * 
 * Submissions making more than 400 calls to hasShips will be judged Wrong Answer.  Also, any solutions that attempt to circumvent the judge will result in disqualification.
 * 
 * Example 1:
 * Input: 
 * ships = [[1,1],[2,2],[3,3],[5,5]], topRight = [4,4], bottomLeft = [0,0]
 * Output: 3
 * Explanation: There are three ships in the rectangle from (0,0) to (4,4).
 * 
 * Example 2:
 * Input: 
 * ships = [[1,1],[2,2],[3,3],[5,5]], topRight = [4,4], bottomLeft = [3,3]
 * Output: 1
 * Explanation: The ship (3,3) is not in the rectangle from (0,0) to (4,4).
 * 
 * Note:
 * 1 <= ships.length <= 10^4
 * ships[i].length == 2
 * topRight.length == 2
 * bottomLeft.length == 2
 * 0 <= ships[i][j], topRight[j], bottomLeft[j] <= 10^4
 * topRight != bottomLeft
 * 
 */
/**
 * // This is the Sea's API interface.
 * // You should not implement it, or speculate about its implementation
 * class Sea {
 *   public:
 *     bool hasShips(vector<int> topRight, vector<int> bottomLeft);
 * };
 */

class Solution {
public:
    int countShips(Sea sea, vector<int> topRight, vector<int> bottomLeft) {
        // Recursive divide and conquer
        return countInRectangle(sea, topRight, bottomLeft);
    }

private:
    int countInRectangle(Sea& sea, vector<int>& topRight, vector<int>& bottomLeft) {
        int x1 = bottomLeft[0], y1 = bottomLeft[1];
        int x2 = topRight[0], y2 = topRight[1];
        
        // Invalid rectangle or no ships in this region
        if (x1 > x2 || y1 > y2) return 0;
        if (!sea.hasShips(topRight, bottomLeft)) return 0;
        
        // Single point: exactly one ship (guaranteed by problem statement)
        if (x1 == x2 && y1 == y2) return 1;
        
        // Split into 4 quadrants
        int midX = x1 + (x2 - x1) / 2;
        int midY = y1 + (y2 - y1) / 2;
        
        int count = 0;
        
        // Bottom-left quadrant: [x1, midX] × [y1, midY]
        vector<int> q1TR = {midX, midY};
        vector<int> q1BL = {x1, y1};
        count += countInRectangle(sea, q1TR, q1BL);
        
        // Bottom-right quadrant: [midX+1, x2] × [y1, midY]
        if (midX + 1 <= x2) {
            vector<int> q2TR = {x2, midY};
            vector<int> q2BL = {midX + 1, y1};
            count += countInRectangle(sea, q2TR, q2BL);
        }
        
        // Top-left quadrant: [x1, midX] × [midY+1, y2]
        if (midY + 1 <= y2) {
            vector<int> q3TR = {midX, y2};
            vector<int> q3BL = {x1, midY + 1};
            count += countInRectangle(sea, q3TR, q3BL);
        }
        
        // Top-right quadrant: [midX+1, x2] × [midY+1, y2]
        if (midX + 1 <= x2 && midY + 1 <= y2) {
            vector<int> q4TR = {x2, y2};
            vector<int> q4BL = {midX + 1, midY + 1};
            count += countInRectangle(sea, q4TR, q4BL);
        }
        
        return count;
    }
};