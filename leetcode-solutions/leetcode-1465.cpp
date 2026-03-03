/**
 * 1465. Maximum Area of a Piece of Cake After Horizontal and Vertical Cuts
 * 
 * Given a rectangular cake with height h and width w, and two arrays of integers horizontalCuts and verticalCuts where horizontalCuts[i] is the distance from the top of the rectangular cake to the ith horizontal cut and similarly, verticalCuts[j] is the distance from the left of the rectangular cake to the jth vertical cut.
 * 
 * Return the maximum area of a piece of cake after you cut at each horizontal and vertical position provided in the arrays horizontalCuts and verticalCuts. Since the answer can be a huge number, return this modulo 10^9 + 7.
 * 
 * Example 1:
 * 
 * Input: h = 5, w = 4, horizontalCuts = [1,2,4], verticalCuts = [1,3]
 * Output: 4 
 * Explanation: The figure above represents the given rectangular cake. Red lines are the horizontal and vertical cuts. After you cut the cake, the green piece of cake has the maximum area.
 * 
 * Example 2:
 * 
 * Input: h = 5, w = 4, horizontalCuts = [3,1], verticalCuts = [1]
 * Output: 6
 * Explanation: The figure above represents the given rectangular cake. Red lines are the horizontal and vertical cuts. After you cut the cake, the green and yellow pieces of cake have the maximum area.
 * 
 * Example 3:
 * 
 * Input: h = 5, w = 4, horizontalCuts = [3], verticalCuts = [3]
 * Output: 9
 * 
 * Note:
 * 2 <= h, w <= 10^9
 * 1 <= horizontalCuts.length < min(h, 10^5)
 * 1 <= verticalCuts.length < min(w, 10^5)
 * 1 <= horizontalCuts[i] < h
 * 1 <= verticalCuts[i] < w
 * It is guaranteed that all elements in horizontalCuts are distinct.
 * It is guaranteed that all elements in verticalCuts are distinct.
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxArea(int h, int w, vector<int>& horizontalCuts, vector<int>& verticalCuts) {
        const int MOD = 1e9 + 7;
        
        // Sort the cuts
        sort(horizontalCuts.begin(), horizontalCuts.end());
        sort(verticalCuts.begin(), verticalCuts.end());
        
        // Find maximum gap between consecutive horizontal cuts (including boundaries)
        int max_h = max(horizontalCuts[0] - 0, h - horizontalCuts.back());
        for (int i = 1; i < horizontalCuts.size(); ++i) {
            max_h = max(max_h, horizontalCuts[i] - horizontalCuts[i-1]);
        }
        
        // Find maximum gap between consecutive vertical cuts (including boundaries)
        int max_v = max(verticalCuts[0] - 0, w - verticalCuts.back());
        for (int i = 1; i < verticalCuts.size(); ++i) {
            max_v = max(max_v, verticalCuts[i] - verticalCuts[i-1]);
        }
        
        // Compute result modulo 1e9+7
        return (static_cast<long long>(max_h) * max_v) % MOD;
    }
};
