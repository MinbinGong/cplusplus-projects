/*
 * Valid Square
 *
 * Given the coordinates of four points in 2D space, return whether the four points could construct a square.
 * 
 * The coordinate (x,y) of a point is represented by an integer array with two integers.
 * 
 * Example:
 * Input: p1 = [0,0], p2 = [1,1], p3 = [1,0], p4 = [0,1]
 * Output: True
 * 
 * Note:
 * All the input integers are in the range [-10000, 10000].
 * A valid square has four equal sides with positive length and four equal angles (90-degree angles).
 * Input points have no order.
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    bool validSquare(vector<int>& p1, vector<int>& p2, vector<int>& p3, vector<int>& p4) {
        // Collect all points
        vector<vector<int>> points = {p1, p2, p3, p4};
        vector<long long> dists;
        
        // Compute all six squared distances
        for (int i = 0; i < 4; ++i) {
            for (int j = i + 1; j < 4; ++j) {
                long long dx = points[i][0] - points[j][0];
                long long dy = points[i][1] - points[j][1];
                dists.push_back(dx * dx + dy * dy);
            }
        }
        
        sort(dists.begin(), dists.end());
        
        // Four smallest must be equal and non-zero (the sides)
        if (dists[0] == 0) return false;
        if (dists[0] != dists[1] || dists[1] != dists[2] || dists[2] != dists[3])
            return false;
        
        // Two largest must be equal (the diagonals)
        if (dists[4] != dists[5]) return false;
        
        // Diagonals must be longer than sides (not strictly necessary but good sanity check)
        if (dists[3] == dists[4]) return false;
        
        return true;
    }
};