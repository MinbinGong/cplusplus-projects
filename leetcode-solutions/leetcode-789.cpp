/*
 * 789. Escape The Ghosts
 *
 * You are playing a simplified Pacman game. You start at the point (0, 0), and your destination is (target[0], target[1]). There are several ghosts on the map, the i-th ghost starts at (ghosts[i][0], ghosts[i][1]).
 * 
 * Each turn, you and all ghosts simultaneously *may* move in one of 4 cardinal directions: north, east, west, or south, going from the previous point to a new point 1 unit of distance away.
 * 
 * You escape if and only if you can reach the target before any ghost reaches you (for any given moves the ghosts may take.)  If you reach any square (including the target) at the same time as a ghost, it doesn't count as an escape.
 * 
 * Return True if and only if it is possible to escape.
 * 
 * Example 1:
 * Input: 
 * ghosts = [[1, 0], [0, 3]]
 * target = [0, 1]
 * Output: true
 * Explanation: 
 * You can directly reach the destination (0, 1) at time 1, while the ghosts located at (1, 0) or (0, 3) have no way to catch up with you.
 * 
 * Example 2:
 * Input: 
 * ghosts = [[1, 0]]
 * target = [2, 0]
 * Output: false
 * Explanation: 
 * You need to reach the destination (2, 0), but the ghost at (1, 0) lies between you and the destination.
 * 
 * Note:
 * 1. N will be in range [1, 1000].
 * 2. ghosts[i] will have length 2.
 * 3. target will have length 2.
 * 4. All points have coordinates with absolute value <= 10000.
 * 5. The ghosts and the target will not be at the same location.
 * 
 */
#include <vector>
#include <cstdlib>

class Solution {
public:
    bool escapeGhosts(std::vector<std::vector<int>>& ghosts, std::vector<int>& target) {
        int myDist = std::abs(target[0]) + std::abs(target[1]);
        for (const auto& g : ghosts) {
            int ghostDist = std::abs(g[0] - target[0]) + std::abs(g[1] - target[1]);
            if (ghostDist <= myDist) {
                return false;   // a ghost can reach the target at least as fast as you
            }
        }
        return true;
    }
};