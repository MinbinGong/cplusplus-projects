/*
 * 1496. Path Crossing
 *
 * Given a string path, where path[i] = 'N', 'S', 'E' or 'W', each representing moving one unit north, south, east, or west, respectively. You start at the origin (0, 0) on a 2D plane and walk on the path specified by path.
 *
 * Return true if the path crosses itself at any point, that is, if at any time you are on a location you have previously visited. Return false otherwise.
 * 
 * Example 1:
 * Input: path = "NES"
 * Output: false 
 * Explanation: Notice that the path doesn't cross any point more than once.
 * 
 * Example 2:
 * Input: path = "NESWW"
 * Output: true
 * Explanation: Notice that the path visits the origin twice.
 * 
 * constraints:
 * 1 <= path.length <= 10^4
 * path[i] is either 'N', 'S', 'E', or 'W'.
 * 
 */
#include <string>
#include <set>

class Solution {
public:
    bool isPathCrossing(std::string path) {
        // Use a set to store visited points
        std::set<std::pair<int, int>> visited;
        int x = 0, y = 0;
        visited.insert({x, y});

        for (char dir : path) {
            // Update position according to direction
            switch (dir) {
                case 'N': y++; break;
                case 'S': y--; break;
                case 'E': x++; break;
                case 'W': x--; break;
            }
            // If we've been here before, path crosses
            if (visited.count({x, y})) {
                return true;
            }
            visited.insert({x, y});
        }
        return false;
    }
};