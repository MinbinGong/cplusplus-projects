/*
 * Rectangle Area
 * 
 * Given the coordinates of two rectilinear rectangles in a 2D plane, return the total area covered by the two rectangles.
 * 
 * The first rectangle is defined by its bottom-left corner (ax1, ay1) and its top-right corner (ax2, ay2).
 * 
 * The second rectangle is defined by its bottom-left corner (bx1, by1) and its top-right corner (bx2, by2).
 * 
 * Constraints:
 * 1. -104 <= ax1, ay1, ax2, ay2, bx1, by1, bx2, by2 <= 104
 * 2. ax1 <= ax2
 * 3. ay1 <= ay2
 * 4. bx1 <= bx2
 * 5. by1 <= by2
 */
#include <algorithm>
using namespace std;

class Solution {
public:
    int computeArea(int ax1, int ay1, int ax2, int ay2,
                    int bx1, int by1, int bx2, int by2) {
        int area1 = (ax2 - ax1) * (ay2 - ay1);
        int area2 = (bx2 - bx1) * (by2 - by1);
        
        int overlapWidth = max(0, min(ax2, bx2) - max(ax1, bx1));
        int overlapHeight = max(0, min(ay2, by2) - max(ay1, by1));
        int overlap = overlapWidth * overlapHeight;
        
        return area1 + area2 - overlap;
    }
};