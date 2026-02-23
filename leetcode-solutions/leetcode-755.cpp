/*
 * 755. Pour Water
 *
 * We are given an elevation map, heights[i] representing the height of the terrain at that index. The width at each index is 1. After V units of water fall at index K, how much water is at each index?
 * 
 * Water first drops at index K and rests on top of the highest terrain or water at that index. Then, it flows according to the following rules:
 * 
 * If the droplet would eventually fall by moving left, then move left.
 * Otherwise, if the droplet would eventually fall by moving right, then move right.
 * Otherwise, rise at it's current position.
 * Here, "eventually fall" means that the droplet will eventually be at a lower level if it moves in that direction. Also, "level" means the height of the terrain plus any water in that column.
 * 
 * We can assume there's infinitely high terrain on the two sides out of bounds of the array. Also, there could not be partial water being spread out evenly on more than 1 grid block - each unit of water has to be in exactly one block.
 * 
 * Example 1:
 * 
 * Input: heights = [2,1,1,2,1,2,2], V = 4, K = 3
 * Output: [2,2,2,3,2,2,2]
 * Explanation:
 * #       #
 * #       #
 * ##  # ###
 * #########
 *  0123456    <- index
 * 
 * Example 2:
 * 
 * Input: heights = [1,2,3,4], V = 2, K = 2
 * Output: [2,3,3,4]
 * Explanation:
 * The last droplet settles at index 1, since moving further left would not cause it to eventually fall to a lower height.
 * 
 * Example 3:
 * 
 * Input: heights = [3,1,3], V = 5, K = 1
 * Output: [4,4,4]
 * 
 * Note:
 * 1. heights will have length in [1, 100] and contain integers in [0, 99].
 * 2. V will be in range [0, 2000].
 * 3. K will be in range [0, heights.length - 1].
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> pourWater(vector<int>& heights, int volume, int k) {
        int n = heights.size();
        for (int drop = 0; drop < volume; ++drop) {
            int best = k;                     // start at the pour position

            // try to flow left
            for (int i = k - 1; i >= 0; --i) {
                if (heights[i] > heights[best]) break; // cannot go uphill
                if (heights[i] < heights[best]) best = i; // found lower spot
                // if equal, continue searching leftwards
            }

            if (best != k) {
                ++heights[best];
                continue;
            }

            // if cannot flow left, try right
            for (int i = k + 1; i < n; ++i) {
                if (heights[i] > heights[best]) break;
                if (heights[i] < heights[best]) best = i;
            }

            // either we found a right spot or stay at k
            ++heights[best];
        }
        return heights;
    }
};
